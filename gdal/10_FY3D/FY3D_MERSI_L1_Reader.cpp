#include <iostream>
#include "FY3D_MERSI_L1_Reader.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::array;

/// @brief 从GEO文件读取经纬度数组
/// @param lonlats 存放经纬度数组的vector容器
void FY3D_MERSI_L1_Reader::readLonLat(std::vector<std::vector<float>> &lonlats)
{
    vector<string> lonlatDS = {"Geolocation/Longitude", "Geolocation/Latitude"};
    for (const string &ds : lonlatDS)
    {
        vector<float> lonlat = readFY3DatasetFull2D(this->fileNameGEO, ds);
        lonlats.push_back(lonlat);
    }
}

vector<float> FY3D_MERSI_L1_Reader::readBandDataDN()
{
    return readFY3BandData(this->fileNameData, this->bandN, false); 
}

vector<float> FY3D_MERSI_L1_Reader::readBandDataScale()
{
    return readFY3BandData(this->fileNameData, this->bandN, true); 
}

void FY3D_MERSI_L1_Reader::caliRef(vector<float> &bandArr)
{
    if (this->isRefBand())
    {
        vector<float> visCalCoeff = readFY3DatasetFull2D(fileNameData, "Calibration/VIS_Cal_Coeff");
        
        // 定标反射率，覆盖掉DN值
        unsigned idxBandX = (this->bandN - 1) * 3;
        float cal0 = visCalCoeff[idxBandX];
        float cal1 = visCalCoeff[idxBandX + 1];
        float cal2 = visCalCoeff[idxBandX + 2];
        for (auto iter = bandArr.begin(); iter != bandArr.end(); ++iter)
        {
            float v = *iter;
            if (v == 0) continue;
            // 覆盖掉
            *iter = cal2 * v * v + cal1 * v + cal0;
        }
    } else {
        cout << "Not reflectance band, do nothing!" << endl;
    }
    
}

void FY3D_MERSI_L1_Reader::caliRefTOA(const vector<float> &caliRef, vector<double> &refTOA)
{
    if (this->isRefBand())
    {
        // 太阳天顶角
        const vector<float> sunz = readFY3DatasetFull2D(this->fileNameGEO, "Geolocation/SolarZenith");

        // 地日距离比
        H5::H5File file(this->fileNameData, H5F_ACC_RDONLY);
        array<double, 25> earthSunDisR;
        readAttrArr<double>(file, "EarthSun Distance Ratio", earthSunDisR);
        file.close();

        double eaDis = earthSunDisR[0];
        for (auto iBand = caliRef.begin(), iSunz = sunz.begin(); 
            iBand != caliRef.end() && iSunz != sunz.end();
            ++iBand, ++iSunz)
        {
            double rad = *iSunz * (PI/180);
            double ref = eaDis * eaDis * (*iBand)/cos(rad);
            if (ref > 100 || ref < 0)
                ref = 0;
            refTOA.push_back(ref);
        }
    } else {
        cout << "Not reflectance band, do nothing!" << endl;
    }
}

void FY3D_MERSI_L1_Reader::calTBB(std::vector<double> &tbbArr)
{
    if (this->isEmissiveBand())
    {
        // 各波段中心波长
        H5::H5File file(this->fileNameData, H5F_ACC_RDONLY);
        array<float, 25> attrs;
        readAttrArr<float>(file, "Effect_Center_WaveLength", attrs);
        const double centerVL = attrs[this->bandN - 1];
        cout << "centerVL:" << centerVL << endl;

        // 亮温修正系数
        auto tbbTrans = vector<string>{"TBB_Trans_Coefficient_A", "TBB_Trans_Coefficient_B"};
        std::vector<array<float, 25>> TBBTransAB;
        for (const string &attrName : tbbTrans)
        {
            readAttrArr<float>(file, attrName, attrs);
            TBBTransAB.push_back(attrs);
        }
        file.close();
        const double tbbCorrA = TBBTransAB[0][this->bandN - 20];
        const double tbbCorrB = TBBTransAB[1][this->bandN - 20];

        for(auto iter = tbbArr.begin(); iter != tbbArr.end(); ++iter)
        {
            if (*iter == 0) continue;
            double m = *iter * PI * 10;  // mW/m2cm-1sr to W/m2um-1
            double te = C2 / log(C1 / m / pow(centerVL, 5) + 1) / centerVL;
            *iter = tbbCorrA * te + tbbCorrB;
        }
    } else {
        cout << "Not emissive band, do nothing!" << endl;
    }
}