/*
 *  PolyFit.h
 *  _LIB
 *
 *  Created by Daniel Clewley on 25/01/2009.
 *  Copyright 2009 Lib.
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

#ifndef PolyFit_H
#define PolyFit_H

#include <iostream>
#include <cmath>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multifit.h>

#include "math/SingularValueDecomposition.h"
#include "math/Vectors.h"
#include "math/Matrices.h"

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_maths_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif

    
/// Class to perform polynomaial fitting	
class DllExport PolyFit
	{
	public:
		PolyFit();
		gsl_vector* PolyfitOneDimensionQuiet(int order, gsl_matrix *inData);
		gsl_vector* PolyfitOneDimension(int order, gsl_matrix *inData);
		gsl_vector* PolyfitOneDimensionSVD(int order, gsl_matrix *inData);
		gsl_matrix* PolyTestOneDimension(int order, gsl_matrix *inData, gsl_vector *coefficients);
		gsl_matrix* PolyfitTwoDimension(int numX, int numY, int orderX, int orderY, gsl_matrix *inData);
		gsl_matrix* PolyTestTwoDimension(int orderX, int orderY, gsl_matrix *inData, gsl_matrix *coefficeints);
		gsl_matrix* PolyfitThreeDimension(int numX, int numY, int numZ, int orderX, int orderY, int orderZ, gsl_matrix *inData);
		gsl_matrix* PolyTestThreeDimension(int orderX, int orderY, int orderZ, gsl_matrix *inData, gsl_matrix *coefficients);
		void calcRSquaredGSLMatrix(gsl_matrix *dataXY);
		void calcRMSErrorGSLMatrix(gsl_matrix *dataXY);
		void calcMeanErrorGSLMatrix(gsl_matrix *dataXY);
		double calcRSquaredGSLMatrixQuiet(gsl_matrix *dataXY);
		double calcRMSErrorGSLMatrixQuiet(gsl_matrix *dataXY);
		double calcMeanErrorGSLMatrixQuiet(gsl_matrix *dataXY);
		~PolyFit();
	private:
	};

#endif

