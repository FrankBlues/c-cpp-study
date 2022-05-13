#include <iostream>
#include "gdal_priv.h"
#include "gdal_alg.h"
#include "gdal.h"
#include <iomanip>

int main()
{
    GDALAllRegister();

    const char* tif_file = "/data/GF2_PMS1_E108.9_N34.2_20181026_L1A0003549596/GF2_PMS1_E108.9_N34.2_20181026_L1A0003549596-MSS1.tiff";
    GDALDataset *poDataset = (GDALDataset *) GDALOpen( tif_file, GA_ReadOnly );
    double width = double(poDataset -> GetRasterXSize());
    double height = double(poDataset -> GetRasterYSize());

    if( poDataset == NULL )
    {
        return 1;
    }

    char** papszRPC = poDataset -> GetMetadata("RPC");
    // GDALClose((GDALDatasetH)poDataset);

    GDALRPCInfoV2 oInfo;
    GDALExtractRPCInfoV2(papszRPC, &oInfo);

    void *pRPCTransform = GDALCreateRPCTransformerV2(&oInfo, FALSE, 0, NULL);

    double dX[4] = {0, 0, width, width};
    double dY[4] = {0, height, height, 0};
    double dZ[4] = {0, 0, 0, 0};
    int nSuccess[4] = {FALSE};

    GDALRPCTransform(pRPCTransform, FALSE, 4, dX, dY, dZ, nSuccess);

    std::cout << std::fixed 
              << std::setprecision(6);
    for (int i=0; i<4; i++) {
        std::cout<< i << ":" << dX[i] << "," << dY[i] << std::endl;
    }


    GDALClose((GDALDatasetH)poDataset);

    GDALDestroyRPCTransformer(pRPCTransform);
}
