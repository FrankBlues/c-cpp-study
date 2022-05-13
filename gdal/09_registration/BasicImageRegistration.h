 /*
 *  BasicImageRegistration.h
 *  _LIB
 *
 *  Created by Pete Bunting on 31/08/2010.
 *  Copyright 2010 Lib. All rights reserved.
 *
 * This file is part of Lib.
 *
 * Lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lib.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef BasicImageRegistration_H
#define BasicImageRegistration_H

#include <iostream>
#include <string>
#include <cmath>
#include <list>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "common/rsgis-tqdm.h"
#include "exception/RegistrationException.h"

#include "ImageRegistration.h"

#include "boost/math/special_functions/fpclassify.hpp"

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

class DllExport BasicImageRegistration : public ImageRegistration
{
public:
	BasicImageRegistration(GDALDataset *reference, GDALDataset *floating, unsigned int gap, float metricThreshold, unsigned int windowSize, unsigned int searchArea, ImageSimilarityMetric *metric, float stdDevRefThreshold, float stdDevFloatThreshold, unsigned int subPixelResolution);
	void initRegistration();
	void executeRegistration();
	void finaliseRegistration();
	void exportTiePointsENVIImage2Map(std::string filepath);
	void exportTiePointsENVIImage2Image(std::string filepath);
	void exportTiePointsImage2Map(std::string filepath);
	void exportTiePointsMapOffs(std::string filepath);
	~BasicImageRegistration();
private:
	std::list<TiePoint*> *tiePoints;
	unsigned int gap;
	float metricThreshold;
	bool initExecuted;
	unsigned int windowSize;
	unsigned int searchArea;
	ImageSimilarityMetric *metric;
	float stdDevRefThreshold;
	float stdDevFloatThreshold;
	unsigned int subPixelResolution;
};

#endif



