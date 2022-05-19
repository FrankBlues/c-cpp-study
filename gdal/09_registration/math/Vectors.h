/*
 *  Vectors.h
 *  _LIB
 *
 *  Created by Daniel Clewley on 21/01/2009.
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

#ifndef Vectors_H
#define Vectors_H

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_vector.h>

#include "exception/VectorsException.h"
#include "exception/InputStreamException.h"
#include "exception/OutputStreamException.h"

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

/// Utilities for  and GSL vectors

/** 
 * n - size
 */

struct DllExport Vector
{
	double *vector;
	int n;
};

class DllExport Vectors
	{
	public:
		Vectors();
		Vector* createVector(int n);
		void freeVector(Vector *vector);
		void printVector(Vector *vector);
		void printGSLVector(gsl_vector *vector);
		void saveVector2GridTxt(Vector *vector, std::string filepath);
		void saveVector2txt(Vector *vector, std::string filepath);
		void saveGSLVector2Txt(gsl_vector *gslVector, std::string filepath);
		void saveGSLVector2GridTxt(gsl_vector *gslVector, std::string filepath);
		Vector* readVectorFromTxt(std::string filepath);
		Vector* readVectorFromGridTxt(std::string filepath);
		gsl_vector* readGSLVectorFromTxt(std::string filepath);
		gsl_vector* readGSLVectorFromGridTxt(std::string filepath);
		gsl_vector* convert2GSLVector(Vector *vector);
		Vector* convertGSL2Vector(gsl_vector *inVector);
		double dotProductVectorVectorGSL(gsl_vector *inVectorA, gsl_vector *inVectorB);
		gsl_vector* crossProductVectorVectorGSL(gsl_vector *inVectorA, gsl_vector *inVectorB);
		double euclideanDistance(Vector *vecA, Vector *vecB);
		~Vectors();
	};

#endif

