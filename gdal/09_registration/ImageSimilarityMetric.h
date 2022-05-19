 /*
 *  ImageSimilarityMetric.h
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

#ifndef ImageSimilarityMetric_H
#define ImageSimilarityMetric_H

#include <cmath>

#include "exception/MathException.h"
#include "img/CalcImageValue.h"

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
    		
class DllExport ImageSimilarityMetric
{
public:
    virtual float calcValue(float **reference, float **floating, unsigned int numVals, unsigned int numDims)=0;
    virtual bool findMin()=0;
    virtual ~ImageSimilarityMetric(){};
};

class DllExport ImageCalcSimilarityMetric : public CalcImageValue
{
public:
    ImageCalcSimilarityMetric(std::vector<unsigned int> imgABands, std::vector<unsigned int> imgBBands, float imgANoData, bool useImgANoData, float imgBNoData, bool useImgBNoData):CalcImageValue(0)
    {
        this->imgABands = imgABands;
        this->imgBBands = imgBBands;
        this->imgANoData = imgANoData;
        this->useImgANoData = useImgANoData;
        this->imgBNoData = imgBNoData;
        this->useImgBNoData = useImgBNoData;

        if(imgABands.size() != imgBBands.size())
        {
            throw BasicException("There are a different number of bands for the two images.");
            exit(1);
        }

        this->nBands = imgABands.size();
    };
    virtual bool findMin()=0;
    virtual void reset()=0;
    virtual double metricVal()=0;
protected:
    std::vector<unsigned int> imgABands;
    std::vector<unsigned int> imgBBands;
    float imgANoData;
    bool useImgANoData;
    float imgBNoData;
    bool useImgBNoData;
    unsigned int nBands;
};
									  
#endif
