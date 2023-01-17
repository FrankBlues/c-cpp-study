#include <iostream>
#include <algorithm>

#include "h5_read.h"
using namespace H5;
using std::array;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/// @brief 由数据集类型推断输出数据类型
/// @param dataset h5 文件中数据集
/// @return H5::DataType PredType
DataType deduceDataType(AbstractDs &dataset)
{
    H5T_class_t type_class = dataset.getTypeClass();
    DataType dt = PredType::NATIVE_FLOAT;
    if (type_class == H5T_INTEGER)
    {
        IntType intype = dataset.getIntType();
        H5T_sign_t sign = intype.getSign();
        // Get size of the data element stored in file
        size_t size = intype.getSize();
        if (size == 2 && sign == 0) // unsigned short int
            dt = PredType::NATIVE_UINT16;
        if (size == 2 && sign == 1) // short int
            dt = PredType::NATIVE_INT16;
        if (size == 1 && sign == 0) // unsigned char
            dt = PredType::NATIVE_UINT8;
        if (size == 1 && sign == 1) // char
            dt = PredType::NATIVE_INT8;
        if (size == 4 && sign == 0) // unsigned int
            dt = PredType::NATIVE_UINT32;
        if (size == 4 && sign == 1) // int
            dt = PredType::NATIVE_INT32;
        if (size == 8 && sign == 0) // unsigned int
            dt = PredType::NATIVE_UINT64;
        if (size == 8 && sign == 1) // int
            dt = PredType::NATIVE_INT64;
    }
    else if (type_class == H5T_FLOAT)
    {
        FloatType intype = dataset.getFloatType();
        size_t size = intype.getSize();
        if (size == 4)
            dt = PredType::NATIVE_FLOAT;
        if (size == 8)
            dt = PredType::NATIVE_DOUBLE;
    }
    return dt;
}

/// @brief 读数据集中二维数组
/// @param filename h5文件名称
/// @param ds 数据集名称
/// @return 经过拉伸处理后的float类型二维数组
vector<float> readFY3DatasetFull2D(const string &filename, const string &ds)
{
    H5File file(filename, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet(ds);
    // 读Slope及Intercept属性
    vector<string> attrs{"Slope", "Intercept"};
    vector<array<float, 1>> scales;
    for (const string &s : attrs)
    {
        if (dataset.attrExists(s))
        {
            Attribute scaleAttr = dataset.openAttribute(s);
            array<float, 1> scale;
            scaleAttr.read(PredType::NATIVE_FLOAT, scale.begin());
            scales.push_back(scale);
            scaleAttr.close();
        }
    }

    // dataset space
    DataSpace dataspace = dataset.getSpace();
    // Get the number of dimensions in the dataspace.
    int rank = dataspace.getSimpleExtentNdims();
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims_out[2];
    int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);

    DataSpace memspace(rank, dims_out);

    vector<float> outArr;
    DataType dt = deduceDataType(dataset);
    if (dt == PredType::NATIVE_INT16)
    {
        vector<short> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_UINT16)
    {
        vector<unsigned short> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_INT32)
    {
        vector<int> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_UINT32)
    {
        vector<unsigned int> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_UINT8)
    {
        vector<unsigned char> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_INT8)
    {
        vector<char> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_INT64)
    {
        vector<long> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_UINT64)
    {
        vector<unsigned long> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_FLOAT)
    {
        vector<float> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else if (dt == PredType::NATIVE_DOUBLE)
    {
        vector<double> data_out(dims_out[0] * dims_out[1]);
        dataset.read(&data_out[0], dt, memspace, dataspace);
        outArr = vector<float>{data_out.begin(), data_out.end()};
    }
    else
    {
        cout << "No matching datatype, exit.";
        exit(1);
    }

    if (scales.size() == 2)
    {
        // cout << "Apply slope and intercept to data." << endl;
        float slope = scales[0][0], intercept = scales[1][0];
        if (!(slope == 1.0 && intercept == 0.0))
        {
            // cout << "slope:" << slope << "; intercept:" << intercept << endl;
            for (auto iter = outArr.begin(); iter != outArr.end(); ++iter)
                *iter = (*iter) * slope + intercept;
        }
    }

    return outArr;
}

/// @brief 由波段编号得到对应的FY3L1Band2DS结构体
/// @param bandN 波段编号 1-25
/// @return FY3L1Band2DS结构体
FY3L1Band2DS getFY3BandInfo(const unsigned int &bandN)
{
    if (bandN < 1 || bandN > 25)
    {
        cout << "Wrong band number, exit!" << endl;
        exit(1);
    }
    if (bandN <= 4)
        return FY3L1Band2DS{"Data/EV_250_Aggr.1KM_RefSB", bandN - 1};
    else if (bandN > 4 && bandN <= 19)
        return FY3L1Band2DS{"Data/EV_1KM_RefSB", bandN - 5};
    else if (bandN > 19 && bandN <= 23)
        return FY3L1Band2DS{"Data/EV_1KM_Emissive", bandN - 20};
    else
        return FY3L1Band2DS{"Data/EV_250_Aggr.1KM_Emissive", bandN - 24};
}

/// @brief 由三维数组读取指定波段数据
/// @param filename FY3D L1数据文件名称
/// @param bandN 波段编号
/// @param scaleData 是否对数组变换 *slope + intercept
/// @return 指定波段float类型数组(vector类型)
vector<float> readFY3BandData(const string &filename,
                              const unsigned int &bandN = 1,
                              bool scaleData = true)
{
    H5File file(filename, H5F_ACC_RDONLY);
    FY3L1Band2DS fyband = getFY3BandInfo(bandN);
    cout << "Open dataset: " << fyband.dsName << "; data index: "
         << fyband.dataIdx << endl;

    DataSet dataset = file.openDataSet(fyband.dsName);

    // dataset space
    DataSpace dataspace = dataset.getSpace();

    // Get the number of dimensions in the dataspace.
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims_out[3];
    int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);

    // read one band
    hsize_t offset[3] = {fyband.dataIdx, 0, 0};
    hsize_t count[3] = {1, dims_out[1], dims_out[2]};
    dataspace.selectHyperslab(H5S_SELECT_SET, count, offset);

    // data buffer
    vector<unsigned short int> data_out(dims_out[1] * dims_out[2]);
    // memery space for one band
    DataSpace memspace(3, count);
    // read data
    dataset.read(&data_out[0], PredType::NATIVE_UINT16, memspace, dataspace);
    vector<float> scaledOut{data_out.begin(), data_out.end()};
    if (scaleData)
    {
        // 读Slope及Intercept属性
        vector<string> attrs{"Slope", "Intercept"};
        // 4 15 4 2 取最大array
        typedef array<float, 15> scaleArr;
        // slope and intercept
        vector<scaleArr> scales;
        for (const string &s : attrs)
        {
            if (dataset.attrExists(s))
            {
                Attribute scaleAttr = dataset.openAttribute(s);
                scaleArr scale;
                scaleAttr.read(PredType::NATIVE_FLOAT, scale.begin());
                scales.push_back(scale);
                scaleAttr.close();
            }
        }

        float slope = 1.0, intercept = 0.0;
        if (scales.size() == 2)
        {
            slope = scales[0][fyband.dataIdx];
            intercept = scales[1][fyband.dataIdx];
            // cout << "slope and intercept:" << slope << ";" << intercept << endl;
        }

        if (!(slope == 1.0 && intercept == 0.0))
        {
            for (auto iter = scaledOut.begin(); iter != scaledOut.end(); ++iter)
            {
                *iter = (*iter) * slope + intercept;
            }
        }
    }
    return scaledOut;
}

/// 求均值
template <typename T>
T meanVec(const vector<T> &vec, double invalid = 0)
{
    double sum = 0;
    size_t invalid_count = 0;
    for (auto &v : vec)
    {
        if (v == invalid)
        {
            ++invalid_count;
            continue;
        }
        sum += v;
    }

    return sum / (vec.size() - invalid_count);
}
