/*
 *  StandardImageSimilarityMetrics.h
 *  _LIB
 *
 *  Created by Pete Bunting on 01/09/2010.
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

#ifndef StandardImageSimilarityMetrics_H
#define StandardImageSimilarityMetrics_H

#include <cmath>

#include "exception/ImageCalcException.h"

#include "ImageSimilarityMetric.h"

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

class DllExport EuclideanSimilarityMetric : public ImageSimilarityMetric
{
public:
    EuclideanSimilarityMetric(){};
    float calcValue(float **reference, float **floating, unsigned int numVals, unsigned int numDims);
    bool findMin(){return true;};
    ~EuclideanSimilarityMetric(){};
};

class DllExport ManhattanSimilarityMetric : public ImageSimilarityMetric // Also referred to as the taxicab distance
{
public:
    ManhattanSimilarityMetric(){};
    float calcValue(float **reference, float **floating, unsigned int numVals, unsigned int numDims);
    bool findMin(){return true;};
    ~ManhattanSimilarityMetric(){};
};

class DllExport SquaredDifferenceSimilarityMetric : public ImageSimilarityMetric
{
public:
    SquaredDifferenceSimilarityMetric(){};
    float calcValue(float **reference, float **floating, unsigned int numVals, unsigned int numDims);
    bool findMin(){return true;};
    ~SquaredDifferenceSimilarityMetric(){};
};

class DllExport CorrelationSimilarityMetric : public ImageSimilarityMetric
{
public:
    CorrelationSimilarityMetric(){};
    float calcValue(float **reference, float **floating, unsigned int numVals, unsigned int numDims);
    bool findMin(){return false;};
    ~CorrelationSimilarityMetric(){};
};







class DllExport ImgCalcEuclideanSimilarityMetric : public ImageCalcSimilarityMetric
{
public:
    ImgCalcEuclideanSimilarityMetric(std::vector<unsigned int> imgABands, std::vector<unsigned int> imgBBands, float imgANoData, bool useImgANoData, float imgBNoData, bool useImgBNoData);
    void calcImageValue(float *bandValues, int numBands);
    bool findMin(){return true;};
    void reset();
    double metricVal();
    ~ImgCalcEuclideanSimilarityMetric(){};
protected:
    unsigned int n;
    double sum;
};

class DllExport ImgCalcManhattanSimilarityMetric : public ImageCalcSimilarityMetric // Also referred to as the taxicab distance
{
public:
    ImgCalcManhattanSimilarityMetric(std::vector<unsigned int> imgABands, std::vector<unsigned int> imgBBands, float imgANoData, bool useImgANoData, float imgBNoData, bool useImgBNoData);
    void calcImageValue(float *bandValues, int numBands);
    bool findMin(){return true;};
    void reset();
    double metricVal();
    ~ImgCalcManhattanSimilarityMetric(){};
protected:
    unsigned int n;
    double sum;
};

class DllExport ImgCalcSquaredDifferenceSimilarityMetric : public ImageCalcSimilarityMetric
{
public:
    ImgCalcSquaredDifferenceSimilarityMetric(std::vector<unsigned int> imgABands, std::vector<unsigned int> imgBBands, float imgANoData, bool useImgANoData, float imgBNoData, bool useImgBNoData);
    void calcImageValue(float *bandValues, int numBands);
    bool findMin(){return true;};
    void reset();
    double metricVal();
    ~ImgCalcSquaredDifferenceSimilarityMetric(){};
protected:
    unsigned int n;
    double sum;
};

class DllExport ImgCalcCorrelationSimilarityMetric : public ImageCalcSimilarityMetric
{
public:
    ImgCalcCorrelationSimilarityMetric(std::vector<unsigned int> imgABands, std::vector<unsigned int> imgBBands, float imgANoData, bool useImgANoData, float imgBNoData, bool useImgBNoData);
    void calcImageValue(float *bandValues, int numBands);
    bool findMin(){return false;};
    void reset();
    double metricVal();
    ~ImgCalcCorrelationSimilarityMetric(){};
protected:
    unsigned int n;
    double sumRF;
    double sumR;
    double sumF;
    double sumRSq;
    double sumFSq;
};

#endif


