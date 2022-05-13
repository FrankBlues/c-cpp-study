/*
 *  ImageRegistration.h
 *  _LIB
 *
 *  Created by Pete Bunting on 31/08/2010.
 *  Copyright 2010 Lib. All rights reserved.
 *  This file is part of Lib.
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

#ifndef ImageRegistration_H
#define ImageRegistration_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "exception/RegistrationException.h"

#include "ImageSimilarityMetric.h"

#include "exception/ImageBandException.h"
#include "img/ImageUtils.h"

#include "math/PolyFit.h"

#include "boost/math/special_functions/fpclassify.hpp"

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_registration_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif

class DllExport ImageRegistration
{
public:
	
	struct DllExport TiePoint
	{
		double eastings;
		double northings;
		unsigned int xRef;
		unsigned int yRef;
		double xFloat;
		double yFloat;
		double metricVal;
		double xShift;
		double yShift;
		
		friend bool operator==(const TiePoint &pt1, const TiePoint &pt2)
		{
			bool returnVal = false;
			if((pt1.xRef == pt2.xRef) & (pt1.yRef == pt2.yRef))
			{
				returnVal = true;
			}
			return returnVal;
		}
		
		bool operator==(const TiePoint *pt) const
		{
			bool returnVal = false;
			if((this->xRef == pt->xRef) & (this->yRef == pt->yRef))
			{
				returnVal = true;
			}
			return returnVal;
		}
		
		float refDistance(TiePoint *pt)
		{
			double sqSum = ((this->xRef - pt->xRef)*(this->xRef - pt->xRef)) + ((this->yRef - pt->yRef)*(this->yRef - pt->yRef));
			
			return sqrt(sqSum/2);
		}
		
		float floatDistance(TiePoint *pt)
		{
			double sqSum = (((this->xFloat-this->xShift) - (pt->xFloat-pt->xShift))*((this->xFloat-this->xShift) - (pt->xFloat-pt->xShift))) + (((this->yFloat-this->yShift) - (pt->yFloat-pt->yShift))*((this->yFloat-this->yShift) - (pt->yFloat-pt->yShift)));
			
			return sqrt(sqSum/2);
		}
	};
	
	struct DllExport OverlapRegion
	{
		double tlX;
		double tlY;
		double brX;
		double brY;
		double xRes;
		double yRes;
		double xRot;
		double yRot;
		float refXStart;
		float refYStart;
		float floatXStart;
		float floatYStart;
		unsigned long xSize;
		unsigned long ySize;
		unsigned int numRefBands;
		unsigned int numFloatBands;
	};
	
	ImageRegistration(GDALDataset *reference, GDALDataset *floating);
	void runCompleteRegistration();
	virtual void initRegistration()=0;
	virtual void executeRegistration()=0;
	virtual void finaliseRegistration()=0;
	virtual void exportTiePointsENVIImage2Map(std::string filepath)=0;
	virtual void exportTiePointsENVIImage2Image(std::string filepath)=0;
	virtual void exportTiePointsImage2Map(std::string filepath)=0;
	virtual void exportTiePointsMapOffs(std::string filepath)=0;
	virtual ~ImageRegistration();
protected:
	void findOverlap();
	void defineFirstTiePoint(unsigned int *startXOff, unsigned int *startYOff, unsigned int numXPts, unsigned int numYPts, unsigned int gap);
	float findTiePointLocation(TiePoint *tiePt, unsigned int windowSize, unsigned int searchArea, ImageSimilarityMetric *metric, float metricThreshold, unsigned int subPixelResolution, float *moveInX, float *moveInY);
	float findTiePointLocation(TiePoint *tiePt, unsigned int windowSize, unsigned int searchArea, ImageSimilarityMetric *metric, unsigned int subPixelResolution, float *moveInX, float *moveInY);
	float findExtreme(bool findMin, gsl_vector *coefficients, unsigned int order, float minRange, float maxRange, unsigned int resolution, float *extremeVal);
	void getImageOverlapFloat(GDALDataset **datasets, int numDS,  float **dsOffsets, int *width, int *height, double *gdalTransform);
	void getImageOverlapWithFloatShift(float xShift, float yShift, int **dsOffsets, int *width, int *height, double *gdalTransform, OGREnvelope *env, float *remainderX, float *remainderY);
	void removeTiePointsWithLowStdDev(std::list<TiePoint*> *tiePts, unsigned int windowSize, float stdDevRefThreshold, float stdDevFloatThreshold);
	double calcStdDev(float **data, unsigned int numVals, unsigned int numDims);
	void exportTiePointsENVIImage2MapImpl(std::string filepath, std::list<TiePoint*> *tiePts);
	void exportTiePointsENVIImage2ImageImpl(std::string filepath, std::list<TiePoint*> *tiePts);
	void exportTiePointsImage2MapImpl(std::string filepath, std::list<TiePoint*> *tiePts);
	void exportTiePointsMapOffsImpl(std::string filepath, std::list<TiePoint*> *tiePts);
	GDALDataset *referenceIMG;
	GDALDataset *floatingIMG;
	OverlapRegion* overlap;
	bool overlapDefined;
};

#endif


