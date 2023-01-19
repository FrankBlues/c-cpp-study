#include <iostream>
#include <vector>
#include <algorithm>

#include "gdal_priv.h"
#include "gdalgrid.h"
#include "gdal_alg.h"

int main(int argc, char const *argv[])
{
    GDALAllRegister();
    CPLErr eErr;
    const char* pszDest = "/mnt/out.tif";
    std::vector<double> adfX{120.82971,120.81061,120.79127,120.82433,120.80506,120.786446,120.7661,120.74824,120.83036,120.8233,120.80467,120.784775,120.81928,120.799736,120.78003,120.75977,120.741875,120.82962,120.8112,120.79268,120.773926,120.75514,120.805695,120.787544,120.766495,120.749084,120.76077,120.74308};
    std::vector<double> adfY{46.22907,46.22422,46.219315,46.241016,46.23614,46.231426,46.226276,46.22174,46.21851,46.230034,46.22522,46.220074,46.24234,46.237305,46.232224,46.22699,46.222366,46.25833,46.2536,46.24884,46.24402,46.239178,46.265526,46.26087,46.25547,46.251,46.26737,46.262833};
    std::vector<double> adfZ{21.519798,23.14092,21.647493,19.547625,21.878407,22.650394,22.288857,22.84824,20.093845,22.157337,23.282904,21.859865,19.619196,22.516426,22.579737,22.430468,22.635952,22.116417,20.266663,22.102638,22.308163,20.60158,20.632025,20.271225,20.334911,21.462559,20.132935,20.05605};

    const double res = 0.01;

    // 目标栅格规格
    auto minmaxIterX = std::minmax_element(adfX.begin(), adfX.end());
    auto minmaxIterY = std::minmax_element(adfY.begin(), adfY.end());
    const double dfXMin = *minmaxIterX.first, dfXMax = *minmaxIterX.second;
    const double dfYMin = *minmaxIterY.first, dfYMax = *minmaxIterY.second;

    double dfXSize = (std::fabs(dfXMax - dfXMin) + (res / 2.0)) / res;
    double dfYSize = (std::fabs(dfYMax - dfYMin) + (res / 2.0)) / res;
    int sizeX = static_cast<int>(dfXSize);
    int sizeY = static_cast<int>(dfYSize);

    GDALDataType eType = GDT_Float32;
    // 栅格数据集
    GDALDriverH hDriver = GDALGetDriverByName("GTiff");
    int nBands = 1;

    GDALDatasetH hDstDS =
        GDALCreate(hDriver, pszDest, sizeX, sizeY, nBands, eType, NULL);

    // nodata
    GDALRasterBandH hBand = GDALGetRasterBand(hDstDS, 1);
    GDALSetRasterNoDataValue(hBand, 0.0);

    // 插值参数
    void *pOptions;
    GDALGridAlgorithm eAlgorithm = GGA_InverseDistanceToAPowerNearestNeighbor;
    const char* pszAlgorithm = "invdistnn:radius=0.04:nodata=0:max_points=4:min_points=1";
    eErr = ParseAlgorithmAndOptions(pszAlgorithm, &eAlgorithm, &pOptions);
    
    // GDALGridInverseDistanceToAPowerNearestNeighborOptions *pOptions2 =
    //             static_cast<GDALGridInverseDistanceToAPowerNearestNeighborOptions *>(pOptions);
    // std::cout << pOptions2->dfRadius << ";" << pOptions2->nMaxPoints << std::endl;

    // 数据空间
    void *pData;
    const int nDataTypeSize = GDALGetDataTypeSizeBytes(eType);
    pData = malloc(sizeX * sizeY * nDataTypeSize);
    // pData = new float[sizeX * sizeY];

    // 执行griddata
    GDALGridContext *psContext = GDALGridContextCreate(
        eAlgorithm, pOptions, static_cast<int>(adfX.size()),
        &(adfX[0]), &(adfY[0]), &(adfZ[0]), TRUE);

    eErr = GDALGridContextProcess(psContext, dfXMin, dfXMax, dfYMin, dfYMax, 
        sizeX, sizeY, eType, pData, NULL, NULL);
    
    GDALGridContextFree(psContext);
    
    // 写入栅格
    if (eErr == CE_None)
        eErr = GDALRasterIO(hBand, GF_Write, 0, 0,
                            sizeX, sizeY, pData, sizeX,
                            sizeY, eType, 0, 0);
    // geotransform
    double adfGeoTransform[6] = {dfXMin, res,
                                 0.0,    dfYMin,
                                 0.0,    res};
    GDALSetGeoTransform(hDstDS, adfGeoTransform);

    // 投影
    GDALSetProjection(hDstDS, "EPSG:4326");

    // 释放内存
    if (pData != nullptr)
        free(pData);
    // delete [] pData;
    if (hDstDS != nullptr)
        GDALClose(hDstDS);
    return 0;
}
