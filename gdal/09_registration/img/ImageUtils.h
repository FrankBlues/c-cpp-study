/*
 *  ImageUtils.h
 *  _LIB
 *
 *  Created by Pete Bunting on 23/04/2008.
 *  Copyright 2008 Lib.
 * 
 *  Lib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Lib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Lib.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ImageUtils_H
#define ImageUtils_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <list>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "common/rsgis-tqdm.h"

#include "exception/ImageBandException.h"

#include "math/MathsUtils.h"

#include "exception/ImageException.h"
#include "exception/OutputStreamException.h"

#include "utils/TextUtils.h"

#include <boost/cstdint.hpp>
#include <boost/algorithm/string.hpp>

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_img_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif


enum RasterConnectivity
{
    rsgis_4connect,
    rsgis_8connect
};

struct DllExport ImagePixelValuePt
{
    OGRPoint *pt;
    uint_fast32_t imgX;
    uint_fast32_t imgY;
    float value;
};

struct DllExport PxlLoc
{
    PxlLoc(){};
    PxlLoc( unsigned int xPos,  unsigned int yPos)
    {
        this->xPos = xPos;
        this->yPos = yPos;
    };
    unsigned int xPos;
    unsigned int yPos;
};

struct DllExport ImgClump
{
    ImgClump(unsigned long clumpID)
    {
        this->clumpID = clumpID;
        this->active = true;
    };
    unsigned long clumpID;
    std::vector<PxlLoc> *pxls;
    float *sumVals;
    float *meanVals;
    bool active;
};

struct DllExport ImgClumpSum
{
    ImgClumpSum(unsigned int clumpID)
    {
        this->clumpID = clumpID;
        this->active = true;
    };
    unsigned int clumpID;
    std::vector<PxlLoc> *pxls;
    float *sumVals;
    bool active;
};

struct DllExport ImgClumpMean
{
    ImgClumpMean(unsigned long clumpID)
    {
        this->clumpID = clumpID;
        this->numPxls = 0;
    };
    unsigned long clumpID;
    unsigned int numPxls;
    float *sumVals;
    float *meanVals;
};

struct DllExport ImgClumpRG
{
    ImgClumpRG(unsigned long clumpID)
    {
        this->clumpID = clumpID;
        this->active = true;
        this->seedVal = 0;
    };
    unsigned long clumpID;
    std::vector<PxlLoc> *pxls;
    float *sumVals;
    float *meanVals;
    bool active;
    std::list<unsigned long> neighbours;
    unsigned long seedVal;
};

class DllExport ImageUtils
    {
    public:
        ImageUtils(double resDiffThresh = 0.0001);
        void snap2ImageGrid(GDALDataset *dataset, OGREnvelope *env);
        void getImageOverlap(GDALDataset **datasets, int numDS, int **dsOffsets, int *width, int *height, double *gdalTransform);
        void getImageOverlap(std::vector<GDALDataset*> *datasets, int **dsOffsets, int *width, int *height, double *gdalTransform);
        void getImageOverlap(GDALDataset **datasets, int numDS, int **dsOffsets, int *width, int *height, double *gdalTransform, int *maxBlockX, int *maxBlockY);
        void getImageOverlap(std::vector<GDALDataset*> *datasets, int **dsOffsets, int *width, int *height, double *gdalTransform, int *maxBlockX, int *maxBlockY);
        void getImageOverlap(GDALDataset **datasets, int numDS, int **dsOffsets, int *width, int *height, double *gdalTransform, OGREnvelope *env);
        void getImageOverlapCut2Env(GDALDataset **datasets, int numDS,  int **dsOffsets, int *width, int *height, double *gdalTransform, OGREnvelope *env);
        void getImageOverlapCut2Env(GDALDataset **datasets, int numDS,  int **dsOffsets, int *width, int *height, double *gdalTransform, OGREnvelope *env, int *maxBlockX, int *maxBlockY);
        void getImageOverlap(GDALDataset **datasets, int numDS, int *width, int *height, OGREnvelope *env);
        void getImageOverlap(GDALDataset **datasets, int numDS, OGREnvelope *env);
        void getImagesExtent(GDALDataset **datasets, int numDS, int *width, int *height, double *gdalTransform);
        void getImagesExtent(std::string *inputImages, int numDS, int *width, int *height, double *gdalTransform);
        void getImagesExtent(std::vector<std::string> inputImages, int *width, int *height, double *gdalTransform);
        void getImagePixelOverlaps(GDALDataset **datasets, int numDS, int **dsOffsets, unsigned int *width, unsigned int *height);
        OGREnvelope* getSpatialExtent(GDALDataset *dataset);
        bool doImageSpatAndExtMatch(GDALDataset **datasets, int numDS);
        void exportImageToTextCol(GDALDataset *image, int band, std::string outputText);
        GDALDataset* createBlankImage(std::string imageFile, double *transformation, int xSize, int ySize, int numBands, std::string projection, float value, std::string gdalFormat="ENVI", GDALDataType imgDataType=GDT_Float32);
        GDALDataset* createBlankImage(std::string imageFile, double *transformation, int xSize, int ySize, int numBands, std::string projection, float value, std::vector<std::string> bandNames, std::string gdalFormat="ENVI", GDALDataType imgDataType=GDT_Float32);
        GDALDataset* createBlankImage(std::string imageFile, OGREnvelope extent, double resolution, int numBands, std::string projection, float value, std::string gdalFormat="ENVI", GDALDataType imgDataType=GDT_Float32);
        void exportImageBands(std::string imageFile, std::string outputFilebase, std::string format);
        void exportImageStack(std::string *inputImages, std::string *outputImages, std::string outputFormat, int numImages) ;
        void exportImageStackWithMask(std::string *inputImages, std::string *outputImages, std::string imageMask, std::string outputFormat, int numImages, float maskValue) ;
        void convertImageFileFormat(std::string inputImage, std::string outputImage, std::string outputImageFormat, bool projFromImage=false, std::string wktProjStr="");
        float** getImageDataBlock(GDALDataset *dataset, int *dsOffsets, unsigned int width, unsigned int height, unsigned int *numVals);
        std::vector<double>* getImageBandValues(GDALDataset *dataset, unsigned int band, bool noDataValDefined, float noDataVal);
        void copyImageRemoveSpatialReference(std::string inputImage, std::string outputImage);
        void copyImageDefiningSpatialReference(std::string inputImage, std::string outputImage, std::string proj, double tlX, double tlY, float xRes, float yRes);
        void createImageSlices(GDALDataset *dataset, std::string outputImageBase);
        void copyFloatGDALDataset(GDALDataset *inData, GDALDataset *outData);
        void copyIntGDALDataset(GDALDataset *inData, GDALDataset *outData);
        void copyUIntGDALDataset(GDALDataset *inData, GDALDataset *outData);
        void copyFloat32GDALDataset(GDALDataset *inData, GDALDataset *outData);
        void copyByteGDALDataset(GDALDataset *inData, GDALDataset *outData);
        void zerosUIntGDALDataset(GDALDataset *data);
        void zerosFloatGDALDataset(GDALDataset *data);
        void zerosByteGDALDataset(GDALDataset *data);
        void defineImageEdge(GDALDataset *data, unsigned int nEdgePxls, unsigned int outEdgeVal=1,  unsigned int outInnerVal=0);
        void assignValGDALDataset(GDALDataset *data, float value);
        GDALDataset* createCopy(GDALDataset *inData, std::string outputFilePath, std::string outputFormat, GDALDataType eType, bool useImgProj=true, std::string proj="");
        GDALDataset* createCopy(GDALDataset *inData, unsigned int numBands, std::string outputFilePath, std::string outputFormat, GDALDataType eType, bool useImgProj=true, std::string proj="");
        GDALDataset* createCopy(GDALDataset *inData, unsigned int numBands, std::string outputFilePath, std::string outputFormat, GDALDataType eType, OGREnvelope extent, bool useImgProj=true, std::string proj="");
        GDALDataset* createCopy(GDALDataset *inData, unsigned int numBands, std::string outputFilePath, std::string outputFormat, GDALDataType eType, double xMin, double xMax, double yMin, double yMax, double xRes, double yRes, bool useImgProj=true, std::string proj="");
        GDALDataset* createCopy(GDALDataset **datasets, int numDS, unsigned int numBands, std::string outputFilePath, std::string outputFormat, GDALDataType eType, bool useImgProj=true, std::string proj="");
        void createKMLText(std::string inputImage, std::string outKMLFile);
        bool closeResTest(double baseRes, double targetRes);
        double getPixelValue(GDALDataset *image, unsigned int imgBand, double xLoc, double yLoc);
        double getPixelValue(GDALDataset *image, unsigned int imgBand, unsigned int xPxl, unsigned int yPxl);
        void setPixelValue(GDALDataset *image, unsigned int imgBand, unsigned int xPxl, unsigned int yPxl, double val);
        void createImageGrid(GDALDataset *inData, unsigned int numXPxls, unsigned int numYPxls, bool offset);
        void populateImagePixelsInRange(GDALDataset *image, int minVal, int maxVal, bool singleLine);
        void setImageBandNames(GDALDataset *dataset, std::vector<std::string> bandNames, bool quiet=false);
        std::map<std::string, std::string> getCreateGDALImgEnvVars(std::string gdalFormat);
        char** getGDALCreationOptions(std::map<std::string, std::string> gdal_creation_options);
        char** getGDALCreationOptionsForFormat(std::string gdalFormat);
        ~ImageUtils();
    private:
        double resDiffThresh; // Maximum difference between image resolutions (as a fraction).
    };

#endif

