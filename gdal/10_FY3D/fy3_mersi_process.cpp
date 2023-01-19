#include <iostream>
#include "FY3D_MERSI_L1_Reader.h"
#include "grid_data.h"

using namespace std;
int main(int argc, char const *argv[])
{
    const string fileNameGEO("/mnt/FY3D_MERSI_GBAL_L1_20230101_0435_GEO1K_MS.HDF");
    const string fileNameData("/mnt/FY3D_MERSI_GBAL_L1_20230101_0435_1000M_MS.HDF");

    // 读波段数据
    unsigned int band = 3;
    const char *outfile = "/mnt/band3.tif";
    bool scaleData = true;
    FY3D_MERSI_L1_Reader fy3_reader(fileNameGEO, fileNameData, band, scaleData);

    // 经纬度
    vector<vector<float>> lonlats;
    fy3_reader.readLonLat(lonlats);
    auto lons = lonlats[0];
    auto lats = lonlats[1];

    // 波段
    vector<float> bandArr = fy3_reader.readBandDataScale();
    
    // 定标反射率
    if (fy3_reader.isRefBand())
    {
        fy3_reader.caliRef(bandArr);
        // cout << bandArr[5] << endl;
        // 表观反射率
        // vector<double> refTOA;
        // fy3_reader.caliRefTOA(bandArr, refTOA);
    }
    vector<double> lonsd{lons.begin(), lons.end()};
    vector<double> latsd{lats.begin(), lats.end()};
    vector<double> bandArrd{bandArr.begin(), bandArr.end()};

    const char* pszAlgorithm = "invdistnn:radius=0.04:nodata=0:max_points=4:min_points=1";
    grid_data_to_raster(lonsd, latsd, bandArrd, outfile, 0.01, GDT_Float32, pszAlgorithm);
    
    // 定标亮温
    if (fy3_reader.isEmissiveBand())
    {
        vector<double> tbbArr{bandArr.begin(), bandArr.end()};
        fy3_reader.calTBB(tbbArr);
        cout << tbbArr[5] << endl;
    }

    return 0;
}
