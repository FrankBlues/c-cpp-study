#include <iostream>
#include "FY3D_MERSI_L1_Reader.h"

using namespace std;
int main(int argc, char const *argv[])
{
    const string fileNameGEO("/mnt/FY3D_MERSI_GBAL_L1_20230101_0435_GEO1K_MS.HDF");
    const string fileNameData("/mnt/FY3D_MERSI_GBAL_L1_20230101_0435_1000M_MS.HDF");

    // 读波段数据
    unsigned int band = 21;
    bool scaleData = true;
    bool isRefBand = false, isEmissiveBand = false;
    FY3D_MERSI_L1_Reader fy3_reader(fileNameGEO, fileNameData, band, scaleData);

    // 经纬度
    vector<vector<float>> lonlats;
    fy3_reader.readLonLat(lonlats);
    
    // 波段
    vector<float> bandArr = fy3_reader.readBandDataScale();

    cout << bandArr[5] << endl;
    if (fy3_reader.isRefBand())
    {
        fy3_reader.caliRef(bandArr);
        cout << bandArr[5] << endl;
        vector<double> refTOA;
        fy3_reader.caliRefTOA(bandArr, refTOA);
        cout << refTOA[5] << endl;
    }
    
    if (fy3_reader.isEmissiveBand())
    {
        vector<double> tbbArr{bandArr.begin(), bandArr.end()};
        fy3_reader.calTBB(tbbArr);
        cout << tbbArr[5] << endl;
    }

    return 0;
}
