/*
 *  SingularValueDecomposition.cpp
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

#include "SingularValueDecomposition.h"

	
SingularValueDecomposition::SingularValueDecomposition()
{
	
}

void SingularValueDecomposition::ComputeSVDgsl(gsl_matrix *inA)
{
	this->inA = inA;
	/// Calculates SVD for matrix in GSL format using GSL libarary
	Vectors vectorUtils;
	Matrices matrixUtils;
	
	matrixUtils.printGSLMatrix(inA);
	gsl_matrix *outV;
	gsl_vector *outS;
	outV = gsl_matrix_alloc (inA->size2, inA->size2);
	outS = gsl_vector_alloc (inA->size2);
	gsl_vector *out_work = gsl_vector_alloc (inA->size2);
	
	svdCompute = gsl_linalg_SV_decomp(inA, outV, outS, out_work);
	
	gsl_matrix_free(outV);
	gsl_vector_free(outS);
}

void SingularValueDecomposition::ComputeSVDrsgis(Matrix *matrix)
{
	/// Calculates SVD for matrix in  format using GSL libarary
	
	Matrices matrixUtils;
	inA = matrixUtils.convert2GSLMatrix(matrix); // Convert to gsl_matrix
	
	gsl_matrix *outV;
	gsl_vector *outS;
	outV = gsl_matrix_alloc (matrix->m, matrix->m);
	outS = gsl_vector_alloc (matrix->m);
	gsl_vector *out_work = gsl_vector_alloc (matrix->m);
	
	svdCompute = gsl_linalg_SV_decomp(inA, outV, outS, out_work);
	
	gsl_matrix_free(outV);
	gsl_vector_free(outS);
	
}

void SingularValueDecomposition::SVDLinSolve(gsl_vector *outX, gsl_vector *inB)
{
	// Solves linear equation using SVD
	/** This uses the gsl_linalg_SV_solve function to calculate the coefficients 
	 for a linear equation. The number of coefficients are determined by the output
		gsl_vector outX.
		*/ 
	gsl_matrix *outV;
	gsl_vector *outS;
	outV = gsl_matrix_alloc (inA->size2, inA->size2);
	outS = gsl_vector_alloc (inA->size2);
	svdSolve = gsl_linalg_SV_solve (inA, outV, outS, inB, outX);
	std::cout << "solved!" << std::endl;
	std::cout << "coefficients are: ";
	gsl_matrix_free(outV);
	gsl_vector_free(outS);
}

SingularValueDecomposition::~SingularValueDecomposition()
{
	
}