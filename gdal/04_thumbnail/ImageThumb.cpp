#include <iostream>
#include "gdal_pam.h"

#include "ImageThumb.h"

bool CreateThumbnail(const char* input, const char* output, int bandID, float scale)
{
    GDALAllRegister();
    CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );   //设置支持中文路径
    GDALDataset *pDataset = (GDALDataset *) GDALOpen( input, GA_ReadOnly );

    if( pDataset == NULL )
    {
        return false;
    }

    int nSamples = pDataset -> GetRasterXSize();
    int nLines = pDataset -> GetRasterYSize();
    int nBands = pDataset -> GetRasterCount();

    if(bandID > nBands)
    {
        GDALClose((GDALDatasetH) pDataset);
        return false;
    }

    int i, j;
    float *pBuffer = new float[nSamples];

    // 查找该波段的最值
    GDALRasterBand *pBandRead = pDataset -> GetRasterBand(bandID);
    int bGotMin, bGotMax;
    double minV, maxV;
    double adfMinMax[2];
    adfMinMax[0] = pBandRead->GetMinimum( &bGotMin );
    adfMinMax[1] = pBandRead->GetMaximum( &bGotMax );

    if( ! (bGotMin && bGotMax) )
        GDALComputeRasterMinMax((GDALRasterBandH)pBandRead, TRUE, adfMinMax);
    minV = adfMinMax[0];
    maxV = adfMinMax[1];

    // std::cout << "minV:" << minV << std::endl;
    // std::cout << "maxV:" << maxV << std::endl;

    // 打开写入图像
    GDALDriver * pDriver = (GDALDriver*)GDALGetDriverByName( "BMP" );
    if(pDriver == NULL)
    {
        std::cout<<"Fail to create bmp fiel driver!"<<std::endl;
        delete[] pBuffer;
        GDALClose( (GDALDatasetH) pDataset );
        return false;
    }

    int stepSize = int( 1.0f / scale );
    int outSample = int(nSamples / stepSize);
    int outLine = int(nLines / stepSize);

    char tmpFile[ 512 ];
    strcpy( tmpFile , output );
    strcat( tmpFile , ".bmp" );

    GDALDataset* pDSOut = pDriver->Create( tmpFile,outSample,outLine,1,GDT_Byte,NULL);
    if( pDSOut == NULL )
    {
        delete[] pBuffer;
        GDALClose( (GDALDatasetH) pDataset );
        return false;
    }

    unsigned char* pBufferOut = new unsigned char[ outSample ];//输出缓存
    GDALRasterBand *pBandWrite = ((GDALDataset *)pDSOut)->GetRasterBand( 1 );

    int offset;
	int offsetY = 0;

    //写入图像
    for ( i = 0 ; i < nLines ; i+= stepSize )
    {
        if( pBandRead->RasterIO(GF_Read,0,i,nSamples,1,pBuffer,nSamples,1,GDT_Float32,0,0 ) != CE_None )
        {
            std::cout<<"error read image!"<<std::endl;
			delete[] pBuffer;
			delete[] pBufferOut;
			GDALClose( (GDALDatasetH) pDataset );
			GDALClose( (GDALDatasetH) pDSOut );
			return false;
        }
        offset = 0;
        for( j = 0 ; j < nSamples ; j+= stepSize )
        {
            pBufferOut[ offset ] = (unsigned char)(( pBuffer[ j ] - minV ) * 256 / ( maxV - minV + 1 ));
            offset++;
        }
        pBandWrite->WriteBlock( 0 , offsetY , pBufferOut );
        offsetY++;
    }

    delete[] pBuffer;
	delete[] pBufferOut;

    GDALDriver * poDriver = GetGDALDriverManager()->GetDriverByName("JPEG");
    if( poDriver == NULL )
    {
        GDALClose( (GDALDatasetH) pDataset );
        GDALClose( (GDALDatasetH) pDSOut );
        return false;
    }
    GDALDataset * poDataset3=poDriver->CreateCopy(output,pDSOut,false,NULL,NULL,NULL);

    //reject to save ".aux.xml" file
	GDALPamDataset *pamDs=dynamic_cast<GDALPamDataset*>(poDataset3);
	if(pamDs)
	{
		int pamFlags=pamDs->GetPamFlags();
		pamFlags|=GPF_NOSAVE;
		pamDs->SetPamFlags(pamFlags);	
	}
	
	if( pDSOut != NULL )
		GDALClose( (GDALDatasetH) pDSOut );
	pDriver->Delete( tmpFile );
	if( pDataset != NULL )
		GDALClose( (GDALDatasetH) pDataset );
	if( poDataset3 != NULL )
		GDALClose( (GDALDatasetH) poDataset3 );
	return true;
}