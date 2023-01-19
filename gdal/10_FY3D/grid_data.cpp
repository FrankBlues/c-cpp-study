#include <iostream>
#include "grid_data.h"

using std::cout;
using std::endl;
using std::vector;

void grid_data_to_raster(const std::vector<double> &x, const std::vector<double> &y,
                      const std::vector<double> &z, const char* pszDest,
                      const double res, GDALDataType eType,
                      const char* pszAlgorithm)
{
    GDALAllRegister();
    CPLErr eErr;

    // 目标栅格规格
    auto minmaxIterX = std::minmax_element(x.begin(), x.end());
    auto minmaxIterY = std::minmax_element(y.begin(), y.end());
    const double dfXMin = *minmaxIterX.first, dfXMax = *minmaxIterX.second;
    const double dfYMin = *minmaxIterY.first, dfYMax = *minmaxIterY.second;

    double dfXSize = (std::fabs(dfXMax - dfXMin) + (res / 2.0)) / res;
    double dfYSize = (std::fabs(dfYMax - dfYMin) + (res / 2.0)) / res;
    int sizeX = static_cast<int>(dfXSize);
    int sizeY = static_cast<int>(dfYSize);

    
    // 栅格数据集
    const char *oformat = getDriverName(pszDest);
    if (oformat == nullptr)
    {
        cout << "Cannot infer output format.";
        exit(-1);
    }
    GDALDriverH hDriver = GDALGetDriverByName(oformat);
    int nBands = 1;

    std::cout << "debug" << std::endl;

    GDALDatasetH hDstDS =
        GDALCreate(hDriver, pszDest, sizeX, sizeY, nBands, eType, NULL);

    // nodata
    GDALRasterBandH hBand = GDALGetRasterBand(hDstDS, 1);
    GDALSetRasterNoDataValue(hBand, 0.0);

    // 插值参数
    void *pOptions;
    GDALGridAlgorithm eAlgorithm;
    // if (algParams[0] == "invdistnn")
    //     eAlgorithm = GGA_InverseDistanceToAPowerNearestNeighbor;
    // const char* pszAlgorithm = "invdistnn:radius=0.04:nodata=0:max_points=4:min_points=1";
    eErr = ParseAlgorithmAndOptions(pszAlgorithm, &eAlgorithm, &pOptions);
    cout << "algorithm: " << eAlgorithm << endl;

    const double dfDeltaX = (dfXMax - dfXMin) / sizeX;
    const double dfDeltaY = (dfYMax - dfYMin) / sizeY;

    int nBlockXSize = 0;
    int nBlockYSize = 0;
    const int nDataTypeSize = GDALGetDataTypeSizeBytes(eType);

    GDALGetBlockSize(hBand, &nBlockXSize, &nBlockYSize);
    if (sizeX == 0 || sizeY == 0 || nBlockXSize == 0 || nBlockYSize == 0)
        exit(-1);
    cout << "blockx:" << nBlockXSize << ";blocky: " << nBlockYSize << endl;

    // Try to grow the work buffer up to 16 MB if it is smaller
    const int nDesiredBufferSize = 16 * 1024 * 1024;
    if (nBlockXSize < sizeX && nBlockYSize < sizeY &&
        nBlockXSize < nDesiredBufferSize / (nBlockYSize * nDataTypeSize))
    {
        const int nNewBlockXSize =
            nDesiredBufferSize / (nBlockYSize * nDataTypeSize);
        nBlockXSize = (nNewBlockXSize / nBlockXSize) * nBlockXSize;
        if (nBlockXSize > sizeX)
            nBlockXSize = sizeX;
    }
    else if (nBlockXSize == sizeX && nBlockYSize < sizeY &&
             nBlockYSize < nDesiredBufferSize / (sizeX * nDataTypeSize))
    {
        const int nNewBlockYSize =
            nDesiredBufferSize / (sizeX * nDataTypeSize);
        nBlockYSize = (nNewBlockYSize / nBlockYSize) * nBlockYSize;
        if (nBlockYSize > sizeY)
            nBlockYSize = sizeY;
    }

    cout << "new blockx:" << nBlockXSize << ";new blocky: " << nBlockYSize << endl;

    // 数据空间 按block写入
    void *pData;
    pData = malloc(nBlockXSize * nBlockYSize * nDataTypeSize);

    int nBlock = 0;
    const int nBlockCount = ((sizeX + nBlockXSize - 1) / nBlockXSize) *
                            ((sizeY + nBlockYSize - 1) / nBlockYSize);

    // 执行griddata
    GDALGridContext *psContext = GDALGridContextCreate(
        eAlgorithm, pOptions, static_cast<int>(x.size()),
        &(x[0]), &(y[0]), &(z[0]), TRUE);
    
    if (psContext == nullptr)
    {
        free(pData);
        exit(-1);
    }
    // cout << psContext->poWorkerThreadPool->GetThreadCount() << endl;

    for (int nYOffset = 0; nYOffset < sizeY && eErr == CE_None;
         nYOffset += nBlockYSize)
    {
        for (int nXOffset = 0; nXOffset < sizeX && eErr == CE_None;
             nXOffset += nBlockXSize)
        {
            ++nBlock;
            cout << "Processing block: " << nBlock << endl;

            int nXRequest = nBlockXSize;
            if (nXOffset + nXRequest > sizeX)
                nXRequest = sizeX - nXOffset;

            int nYRequest = nBlockYSize;
            if (nYOffset + nYRequest > sizeY)
                nYRequest = sizeY - nYOffset;
            
            eErr = GDALGridContextProcess(
                psContext, dfXMin + dfDeltaX * nXOffset, 
                dfXMin + dfDeltaX * (nXOffset + nXRequest), 
                dfYMin + dfDeltaY * nYOffset,
                dfYMin + dfDeltaY * (nYOffset + nYRequest),
                nXRequest, nYRequest, eType, pData, NULL, NULL);
            if (eErr == CE_None)
                eErr = GDALRasterIO(hBand, GF_Write, nXOffset, nYOffset,
                                    nXRequest, nYRequest, pData, nXRequest,
                                    nYRequest, eType, 0, 0);
        }
    }
    
    GDALGridContextFree(psContext);

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
}