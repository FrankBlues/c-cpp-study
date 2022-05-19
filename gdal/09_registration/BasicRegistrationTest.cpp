#include <string>
#include "gdal_priv.h"
#include "StandardImageSimilarityMetrics.h"
// #include "exception/BasicException.h"
#include "BasicImageRegistration.h"

int main()
{
    std::string inputReferenceImage = "/data/DOM/2J_DOM.tif";
    std::string inputFloatingmage = "/data/DATA/GF2_PMS1_E110.0_N34.0_20200727_L1A0004953380/GF2_PMS1_E110.0_N34.0_20200727_L1A0004953380-PAN1.tiff";
    int gcpGap = 600;
    float metricThreshold = 0.4;
    int windowSize = 50;
    int searchArea = 70;
    float stdDevRefThreshold = 2;
    float stdDevFloatThreshold = 2;
    int subPixelResolution = 4;
    unsigned int metricTypeInt = 4;
    unsigned int outputType = 3;
    std::string outputGCPFile = "/data/gcp.txt";

    GDALAllRegister();
    GDALDataset *inRefDataset = nullptr;
    GDALDataset *inFloatDataset = nullptr;

    inRefDataset = (GDALDataset *) GDALOpenShared(inputReferenceImage.c_str(), GA_ReadOnly);
    if(inRefDataset == nullptr)
    {
        std::string message = std::string("Could not open image ") + inputReferenceImage;
        throw BasicException(message.c_str());
    }

    inFloatDataset = (GDALDataset *) GDALOpenShared(inputFloatingmage.c_str(), GA_ReadOnly);
    if(inFloatDataset == nullptr)
    {
        std::string message = std::string("Could not open image ") + inputFloatingmage;
        throw BasicException(message.c_str());
    }

    ImageSimilarityMetric *similarityMetric = nullptr;
    if(metricTypeInt == 1) // euclidean
    {
        similarityMetric = new EuclideanSimilarityMetric();
    }
    else if(metricTypeInt == 2) // sqdiff
    {
        similarityMetric = new SquaredDifferenceSimilarityMetric();
    }
    else if(metricTypeInt == 3) // manhatten
    {
        similarityMetric = new ManhattanSimilarityMetric();
    }
    else if(metricTypeInt == 4) // correlation
    {
        similarityMetric = new CorrelationSimilarityMetric();
    }
    else
    {
        throw BasicException("Metric not recognised!");
    }

    
    
    ImageRegistration *regImgs = new BasicImageRegistration(inRefDataset, inFloatDataset, gcpGap, metricThreshold,
                                                                            windowSize, searchArea, similarityMetric, stdDevRefThreshold,
                                                                            stdDevFloatThreshold, subPixelResolution);
    
    regImgs->runCompleteRegistration();
    
    if(outputType == 1) // envi_img2img
    {
        regImgs->exportTiePointsENVIImage2Image(outputGCPFile);
    }
    else if(outputType == 2) // envi_img2map
    {
        regImgs->exportTiePointsENVIImage2Map(outputGCPFile);
    }
    else if(outputType == 3) // rsgis_img2map
    {
        regImgs->exportTiePointsImage2Map(outputGCPFile);
    }
    else if(outputType == 4) // rsgis_mapoffs
    {
        regImgs->exportTiePointsMapOffs(outputGCPFile);
    }
    
    delete similarityMetric;
    // delete regImgs;
    
    GDALClose(inRefDataset);
    GDALClose(inFloatDataset);

}