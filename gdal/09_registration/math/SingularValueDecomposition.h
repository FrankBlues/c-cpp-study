/*
 *  SingularValueDecomposition.h
 *  _LIB
 *
 *  Created by Daniel Clewley on 16/01/2009.
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


#ifndef SingularValueDecomposition_H
#define SingularValueDecomposition_H

#include <cmath>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include "math/Matrices.h"
#include "math/Vectors.h"

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
      
class DllExport SingularValueDecomposition
/// Class to preform singular value decomposition on a matrix using the GSL library
/**
 *Versions to comptute using the  standard of matrix and GSL standard are included.
	*/

	{
	public:
		SingularValueDecomposition();
		void ComputeSVDgsl(gsl_matrix *inA);
		void ComputeSVDrsgis(Matrix *inMatrix);
		void SVDLinSolve(gsl_vector *outX, gsl_vector *inB);
		~SingularValueDecomposition();
	private:
		int svdCompute;
		int svdSolve;
		gsl_matrix *inA;
	};


#endif
