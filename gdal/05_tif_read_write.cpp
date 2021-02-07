#include <iostream>
// #include <string>

#include <typeinfo>

#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
using namespace std;

int main(int argc, char const *argv[])
{
    GDALAllRegister();

    const char* tif_file = "/data/cpp_test/示例数据_out.tif";
    GDALDataset  *poDataset;
    poDataset = (GDALDataset *) GDALOpen( tif_file, GA_ReadOnly );

    if( poDataset == NULL )
    {
        return 1;
    }

    // Getting Dataset Information
    // GeoTransform
    double        adfGeoTransform[6];
    poDataset->GetGeoTransform( adfGeoTransform );

    double x0 = adfGeoTransform[0];
    double y0 = adfGeoTransform[3];
    double xRes = adfGeoTransform[1];
    double yRes = adfGeoTransform[5];
    
    // Driver
    GDALDriver *driver = poDataset->GetDriver();
    const char* driverName = driver->GetDescription();

    // basic
    int cols = poDataset->GetRasterXSize();
    int rows = poDataset->GetRasterYSize();
    int bandCount = poDataset->GetRasterCount();

    // SpacialRef
    const char *projName = poDataset->GetProjectionRef();

    // OGRSpatialReference object
    const OGRSpatialReference *sr = poDataset->GetSpatialRef();
    const char *srName = sr->GetName();

    // Band
    GDALRasterBand *poBand = poDataset->GetRasterBand( 1 );

    // BlockSize
    int nBlockXSize, nBlockYSize;
    poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);

    // DataType
    GDALDataType bandType = poBand->GetRasterDataType();
    const char *dataType = GDALGetDataTypeName(bandType);

    // color interp
    const char *colorInterp = GDALGetColorInterpretationName(
                                    poBand->GetColorInterpretation());

    // Min|Max
    // int bGotMin, bGotMax;
    double adfMinMax[2];
    // adfMinMax[0] = poBand->GetMinimum( &bGotMin );
    // adfMinMax[1] = poBand->GetMaximum( &bGotMax );

    GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);

    // overviews
    int overviewCount = poBand->GetOverviewCount();

    // color table
    GDALColorTable *ct = poBand->GetColorTable();
    // if (ct == NULL)
    //     cout << "Colortable is null!" << endl;
    
    // Band data
    typedef unsigned char uint8;
    float **bandData = new float*[cols];
    //float bData[rows][cols];
    // get number of bytes per pixel in Geotiff
    int nbytes = GDALGetDataTypeSizeBytes(bandType);
    uint8 *pafScanline = (uint8 *) CPLMalloc(nbytes*cols);

    for(int row=0; row < rows; ++row)
    {
        CPLErr e = poBand->RasterIO(GF_Read, 0, row, cols, 1,
                        pafScanline, cols, 1, GDT_Byte,
                        0, 0);
        if (!(e == 0))
        {
            cout << "Warning: Unable to read scanline in Geotiff!" << endl;
            exit(1);
        }
        bandData[row] = new float[cols];
        for(int col=0; col<cols; ++col)  // iterate through columns
        {
            bandData[row][col] = (float)(pafScanline[col]);
        }
    }
    
    CPLFree(pafScanline);

    // Create a copy, write
    const char *dstFileName = "/data/cpp_test/示例数据_out1.tif";

    // Driver
    GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
    // Create copy
    GDALDataset *poDstDS;
    char **papszOptions = NULL;
    poDstDS = poDriver->Create(dstFileName, cols, rows, 3, GDT_Byte, papszOptions);
    poDstDS->SetGeoTransform(adfGeoTransform);
    poDstDS->SetProjection(projName);

    uint8 *pafScanline1 = (uint8 *) CPLMalloc(nbytes*cols);
    uint8 fillValue;
    for(int band=1; band<=3; ++band)
    {
        if (band == 1)
        {
            fillValue = 254;
        }else if (band == 2)
        {
            fillValue = 255;
        }else if (band == 3)
        {
            fillValue = 115;
        }
        
        GDALRasterBand *poBand = poDstDS->GetRasterBand(band);
        
        for(int row=0; row < rows; ++row)
        {
            for(int col=0; col<cols; ++col)
            {
                if (bandData[row][col] == 1.0)
                {
                    pafScanline1[col] = fillValue;
                }else{
                    pafScanline1[col] = 0;
                }
            }
            CPLErr e1 = poBand->RasterIO(GF_Write, 0, row, cols, 1,
                                         pafScanline1, cols, 1, GDT_Byte,
                                         0, 0);
        }
        poBand->SetNoDataValue(0);
    }

    CPLFree(pafScanline1);

    // Closing the Dataset
    GDALClose((GDALDatasetH)poDataset);

    if (poDstDS != NULL)
        GDALClose((GDALDatasetH)poDstDS);
    GDALDestroyDriverManager();

    return 0;
}