#ifndef H5_READ_H
#define H5_READ_H

#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "H5Cpp.h"

#define PI 3.14159265358979323846
#define H 6.62607015e-34
#define K 1.380649e-23
#define C 299792458
#define C1 2 * PI *H *C *C * 1e24
#define C2 C *H / K * 1e6

/// @brief 风云3一级数据真实波段编号与L1产品数据集及数组索引之间的对应关系
/// 比如波段1-4分别对应Data/EV_250_Aggr.1KM_RefSB数据集中数组0-3
struct FY3L1Band2DS
{
    const char *dsName = "";  // 数据集
    const unsigned int dataIdx = 0;  // 数组索引,三维数组中的第一维
};

H5::DataType deduceDataType(H5::AbstractDs &dataset);
std::vector<float> readFY3DatasetFull2D(const std::string &filename, const std::string &ds);
std::vector<float> readFY3BandData(const std::string &filename,
                                   const unsigned int &bandN,
                                   bool scaleData);

template<typename T>
void readAttrArr(const H5::H5Object &h5FileObj, const std::string &attrName, std::array<T, 25> &arr);

#endif

template<typename T>
void readAttrArr(const H5::H5Object &h5FileObj, const std::string &attrName, std::array<T, 25> &arr)
{
    H5::Attribute attrObj = h5FileObj.openAttribute(attrName);
    H5::DataType dt = deduceDataType(attrObj);
    attrObj.read(dt, arr.begin());
}