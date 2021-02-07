#include <iostream>
#include <string>
#include "gdal_priv.h"
#include "cpl_string.h"

using namespace std;
int main()
{
    GDALAllRegister();
    // determine if a particular format supports Create or CreateCopy
    const char *pszFormat = "GTiff";
    GDALDriver *poDriver;
    char **papszMetadata;
    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
    if( poDriver == NULL )
        exit( 1 );
    papszMetadata = poDriver->GetMetadata();
    if( CSLFetchBoolean( papszMetadata, GDAL_DCAP_CREATE, FALSE ) )
        printf( "Driver %s supports Create() method.\n", pszFormat );
    if( CSLFetchBoolean( papszMetadata, GDAL_DCAP_CREATECOPY, FALSE ) )
        printf( "Driver %s supports CreateCopy() method.\n", pszFormat );
    
    // Using CreateCopy()
    const char *pszSrcFilename = "/data/影像样例/610124/6101241_part.tif";
    const char *pszDstFilename = "/data/temp/6101241_part.tif";
    GDALDataset *poSrcDS =
    (GDALDataset *) GDALOpen( pszSrcFilename, GA_ReadOnly );
    GDALDataset *poDstDS;
    poDstDS = poDriver->CreateCopy( pszDstFilename, poSrcDS, FALSE,
                                    NULL, NULL, NULL );
    /* Once we're done, close properly the dataset */
    if( poDstDS != NULL )
        GDALClose( (GDALDatasetH) poDstDS );
    GDALClose( (GDALDatasetH) poSrcDS );

}