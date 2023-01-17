#ifndef FY3D_MERSI_L1_READER_H
#define FY3D_MERSI_L1_READER_H
#include <string>
#include <vector>
#include <array>

#include "h5_read.h"

class FY3D_MERSI_L1_Reader
{
public:
    FY3D_MERSI_L1_Reader() = default;
    FY3D_MERSI_L1_Reader(const std::string &fg, const std::string &fd,
                         const unsigned &bandN, bool scaleData) : 
                         fileNameGEO(fg), fileNameData(fd), bandN(bandN), scaleData(scaleData) {}

    bool isEmissiveBand() { return bandN > 19; }
    bool isRefBand() { return bandN <= 19; }

    void readLonLat(std::vector<std::vector<float>> &lonlats);
    std::vector<float> readBandDataDN();
    std::vector<float> readBandDataScale();

    void caliRef(std::vector<float> &bandArr);
    void caliRefTOA(const std::vector<float> &caliRef, std::vector<double> &refTOA);
    void calTBB(std::vector<double> &tbbArr);

    ~FY3D_MERSI_L1_Reader(){};

private:
    const std::string fileNameGEO;
    const std::string fileNameData;

    const unsigned bandN;
    bool scaleData = true;
    
};

#endif