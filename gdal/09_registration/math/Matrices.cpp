/*
 *  Matrices.cpp
 *  _LIB
 *
 *  Created by Pete Bunting on 02/06/2008.
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

#include "Matrices.h"


Matrices::Matrices()
{
	
}

Matrix* Matrices::createMatrix(int n, int m)
{
	/// Create matrix n rows by m colums
	if(n < 1 | m < 1)
	{
		throw MatricesException("Sizes of m and n must be at least 1.");
	}
	Matrix *matrix = new Matrix();
	matrix->n = n;
	matrix->m = m;
	matrix->matrix = new double[n*m];
	
	int length = n * m;
	
	for(int i = 0; i < length; i++)
	{
		matrix->matrix[i] = 0;
	}
	return matrix;
}

Matrix* Matrices::createMatrix(Matrix *matrix)
{
	if(matrix == nullptr)
	{
		throw MatricesException("The matrix to be copied is NULL.");
	}
	
	Matrix *newMatrix = new Matrix();
	newMatrix->n = matrix->n;
	newMatrix->m = matrix->m;
	newMatrix->matrix = new double[matrix->n*matrix->m];
	
	int length = newMatrix->n * newMatrix->m;
	
	for(int i = 0; i < length; i++)
	{
		newMatrix->matrix[i] = 0;
	}
	
	return newMatrix;
}

Matrix* Matrices::copyMatrix(Matrix *matrix)
{
	if(matrix == nullptr)
	{
		throw MatricesException("The matrix to be copied is NULL.");
	}
	
	Matrix *newMatrix = new Matrix();
	newMatrix->n = matrix->n;
	newMatrix->m = matrix->m;
	newMatrix->matrix = new double[matrix->n*matrix->m];
	
	int numPTS = matrix->m * matrix->n;
	
	for(int i = 0; i < numPTS; i++)
	{
		newMatrix->matrix[i] = matrix->matrix[i];
	}
	return newMatrix;
}

void Matrices::freeMatrix(Matrix *matrix)
{
	if(matrix != nullptr)
	{
		if(matrix->matrix != nullptr)
		{
			delete matrix->matrix;
		}
		delete matrix;
	}
}

void Matrices::setValues(Matrix *matrix, double val)
{
	int totalElements = matrix->n * matrix->m;
	for(int i = 0; i < totalElements; i++)
	{
		matrix->matrix[i] = val;
	}
}

double Matrices::determinant(Matrix *matrix)
{
	double sum = 0;
	if(matrix->n != matrix->m)
	{
		throw MatricesException("To calculate a determinant the matrix needs to be symatical");
	}
	
	if(matrix->n == 2)
	{
		sum = (matrix->matrix[0] * matrix->matrix[3]) - (matrix->matrix[1] * matrix->matrix[2]);
	}
	else
	{
		Matrix *tmpMatrix = nullptr;
		double value = 0;
		int index = 0;
		for(int i = 0; i < matrix->n; i++)
		{

			index = 0;
			tmpMatrix = this->createMatrix((matrix->n-1), (matrix->m-1));
			
			// Populate new matrix
			for(int n = 1; n < matrix->n; n++)
			{
				for(int m = 0; m < matrix->m; m++)
				{
					if(i == m)
					{
						continue;
					}
					
					tmpMatrix->matrix[index] = matrix->matrix[(n*matrix->n)+m];
					index++;
				}
			}
			// Calculate the determinant of the new matrix
			value = this->determinant(tmpMatrix);
			
			// add to sum
			sum = sum + (pow(-1.0,i) * value * matrix->matrix[i]);
			
			this->freeMatrix(tmpMatrix);
		}
	}
	return sum;
}

Matrix* Matrices::cofactors(Matrix *matrix)
{
	if(matrix->n != matrix->m)
	{
		throw MatricesException("To calculate cofactors the matrix needs to be symatical");
	}
	Matrix *newMatrix = nullptr;
	newMatrix = this->createMatrix(matrix->n, matrix->m);
	
	int index = 0;
	Matrix *tmpMatrix = this->createMatrix((matrix->n-1), (matrix->m-1));
	for(int i = 0; i < matrix->n; i++)
	{
		for(int j = 0; j < matrix->m; j++)
		{
			index = 0;
			for(int n = 0; n < matrix->n; n++)
			{
				if(i == n)
				{
					continue;
				}
				for(int m = 0; m < matrix->m; m++)
				{
					if(j == m)
					{
						continue;
					}
					tmpMatrix->matrix[index] = matrix->matrix[(n*matrix->n)+m];
					index++;
				}
			}
			newMatrix->matrix[(i*matrix->n)+j] = (pow(-1.0,((i*matrix->n)+j))) * this->determinant(tmpMatrix);
		}
	}
	this->freeMatrix(tmpMatrix);
	return newMatrix;
}

Matrix* Matrices::transpose(Matrix *matrix)
{
	Matrix *newMatrix = nullptr;
	newMatrix = this->createMatrix(matrix->m, matrix->n);
	for(int i = 0; i < matrix->n; i++)
	{
		for(int j = 0; j < matrix->m; j++)
		{
			newMatrix->matrix[i+(j*matrix->n)] = matrix->matrix[(i*matrix->n)+j];
		}
	}
	return newMatrix;
}

void Matrices::transposeGSL(gsl_matrix *inMatrix, gsl_matrix *outMatrix)
{
	/// Returns the transpose of a gsl_matrix, the origional matrix is unmodified.
	/** Uses the GSL function for a square matrix or calls 'transposeNonSquareGSL' for a
		 * non-square matrix
		 */
	if(inMatrix->size1 == inMatrix->size2)
	{
		gsl_matrix_memcpy(outMatrix, inMatrix);
		gsl_matrix_transpose(outMatrix);
	}
	else 
	{
		this->transposeNonSquareGSL(inMatrix, outMatrix);
	}

}

void Matrices::transposeNonSquareGSL(gsl_matrix *inMatrix, gsl_matrix *outMatrix)
{
	/// Returns the transpose of a gsl_matrix, the origional matrix is unmodified.
	
	for(unsigned int i = 0; i < inMatrix->size1; i++) // Loop through matirx rows
	{
		for(unsigned int j = 0; j < inMatrix->size2; j++) // Loop through colums
		{
			double melement = gsl_matrix_get(inMatrix, i, j);
			gsl_matrix_set(outMatrix, j, i, melement);
		}
	}

}

void Matrices::inv2x2GSLMatrix(gsl_matrix *inMatrix, gsl_matrix *outMatrix)
{
	
	/// Calculates the inverse of a 2 x 2 gsl_matrix
	
	// Check for diagonal matrix
	if(gsl_matrix_get(inMatrix, 0, 1) == 0 & gsl_matrix_get(inMatrix, 1, 0) == 0)
	{
		for(unsigned int i = 0; i < inMatrix->size1; i++) // Loop through matirx rows
		{
			for(unsigned int j = 0; j < inMatrix->size2; j++) // Loop through colums
			{
				double melement = gsl_matrix_get(inMatrix, i, j);
				double invMelement = 0;
				if(melement != 0)
				{
					invMelement = 1 / melement;
				}
				
				gsl_matrix_set(outMatrix, i, j, invMelement);
			}
		}
	}
	else 
	{
		gsl_matrix_set(outMatrix, 0, 0, gsl_matrix_get(inMatrix, 1, 1));
		gsl_matrix_set(outMatrix, 1, 1, gsl_matrix_get(inMatrix, 0, 0));
		gsl_matrix_set(outMatrix, 0, 1, gsl_matrix_get(inMatrix, 0, 1) * -1);
		gsl_matrix_set(outMatrix, 1, 0, gsl_matrix_get(inMatrix, 1, 0) * -1);
	}

}

void Matrices::multipleSingle(Matrix *matrix, double multiple)
{
	int numElements = matrix->n * matrix->m;
	for(int i = 0; i < numElements; i++)
	{
		matrix->matrix[i] = matrix->matrix[i] * multiple;
	}
}

Matrix* Matrices::multiplication(Matrix *matrixA, Matrix *matrixB)
{
	Matrix *matrix1 = NULL;
	Matrix *matrix2 = NULL;
	if(matrixA->n == matrixB->m)
	{
		matrix1 = matrixA;
		matrix2 = matrixB;
	}
	else if(matrixA->m == matrixB->n)
	{
		matrix1 = matrixB;
		matrix2 = matrixA;
	}
	else
	{
		throw MatricesException("Multipication required the number of columns to match the number of rows.");
	}
	
	Matrix *newMatrix = this->createMatrix(matrix2->n, matrix1->m);
	
	double value = 0;
	int row = 0;
	int col = 0;
	int index = 0;
	for(int i = 0; i < matrix1->m; i++)
	{
		for(int j = 0; j < matrix2->n; j++)
		{
			value = 0;
			for(int n = 0; n < matrix1->n; n++)
			{
				row = (i * matrix1->n) + n;
				col = (n * matrix2->n) + j;

				value += matrix1->matrix[row] * matrix2->matrix[col];
			}
			newMatrix->matrix[index] = value;
			index++;
		}
	}
	
	return newMatrix;
}


void Matrices::productMatrixVectorGSL(gsl_matrix *inMatrix, gsl_vector *inVector, gsl_vector *outVector)
{
	/// Calculates the product of a gsl_matrix and a gsl_vector, returns a gsl_vector
	
	if(inMatrix->size2 != inVector->size) // Check sizes
	{
		std::cout << "Input vector has less elements than number of matrix colums" << std::endl;
		throw MatricesException("Input vector has less elements than number of matrix colums");
	}
	
	for(unsigned int i = 0; i < inMatrix->size1; i++) // Loop through matirx rows
	{
		double mvsum = 0.0;
		for(unsigned int j = 0; j < inMatrix->size2; j++) // Loop through colums
		{
			double melement = gsl_matrix_get(inMatrix, i, j);
			double velement = gsl_vector_get(inVector, j);
			mvsum = mvsum + (melement * velement);
		}

		gsl_vector_set(outVector, i, mvsum);
	
	}
}

void Matrices::printMatrix(Matrix *matrix)
{		
	int index = 0;
	for(int i = 0; i < matrix->n; i++)
	{
		for(int j = 0; j < matrix->m; j++)
		{
			std::cout << matrix->matrix[index++] << " ";
		}
		std::cout << std::endl;
	}
}

void Matrices::printGSLMatrix(gsl_matrix *matrix)
{
	for(unsigned int i = 0; i < matrix->size1; i++)
	{
		for(unsigned int j = 0; j < matrix->size2; j++)
		{
			double outm = gsl_matrix_get(matrix, i, j); 
			std::cout << outm << " ";
		}
		std::cout << std::endl;
	}
}

void Matrices::saveMatrix2GridTxt(Matrix *matrix, std::string filepath)
{
	std::string outputFilename = filepath;
	std::string ext = getFileExt(filepath);
	if(ext != ".gmtxt")
	{
		outputFilename = filepath + std::string(".gmtxt");
	}
	
	std::ofstream outTxtFile;
	outTxtFile.open(outputFilename.c_str(), std::ios::out | std::ios::trunc);
	
	if(outTxtFile.is_open())
	{
		outTxtFile << "m=" << matrix->m << std::endl;
		outTxtFile << "n=" << matrix->n << std::endl;
		
		int totalElements = matrix->n * matrix->m;
		int lastElement = totalElements-1;
		for(int i = 0; i < totalElements; i++)
		{
			if((i+1) %  matrix->m == 0)
			{
				outTxtFile << matrix->matrix[i] << std::endl;
			}
			else if(i == lastElement)
			{
				outTxtFile << matrix->matrix[i];
			}
			else
			{
				outTxtFile << matrix->matrix[i] << ",";
			}
		}
		outTxtFile.flush();
		outTxtFile.close();
	}
	else
	{
		throw OutputStreamException("Could not open text file.");
	}
	
}

void Matrices::saveMatrix2CSV(Matrix *matrix, std::string filepath)
{
	std::string outputFilename = filepath;
	std::string ext = getFileExt(filepath);
	if(ext != ".csv")
	{
		outputFilename = filepath + std::string(".csv");
	}
	std::ofstream outTxtFile;
	outTxtFile.open(outputFilename.c_str(), std::ios::out | std::ios::trunc);
	
	if(outTxtFile.is_open())
	{			
		int totalElements = matrix->n * matrix->m;
		for(int i = 0; i < totalElements; i++)
		{
			if(i == 0) // Don't start firstline with comma or newline
			{
				outTxtFile  << matrix->matrix[i];
			}
			else if((i %  matrix->m == 0)) // If start of line, begin with a new line.
			{
				//outTxtFile << std::endl;
				outTxtFile  << std::endl << matrix->matrix[i];
			}
			else // Otherwise, begin with a comma
			{
				outTxtFile  << "," << matrix->matrix[i];
			}
		}
		outTxtFile.flush();
		outTxtFile.close();
	}
	else
	{
		throw OutputStreamException("Could not open text file.");
	}
	
}

void Matrices::saveGSLMatrix2CSV(gsl_matrix *gslMatrix, std::string filepath)
{
	Matrix *rsgisMatrix;
	rsgisMatrix = this->convertGSL2Matrix(gslMatrix);
	this->saveMatrix2CSV(rsgisMatrix, filepath);
	this->freeMatrix(rsgisMatrix);
}

void Matrices::saveMatrix2txt(Matrix *matrix, std::string filepath)
{
	std::string outputFilename = filepath;
	std::string ext = getFileExt(filepath);
	if(ext != ".mtxt")
	{
		outputFilename = filepath + std::string(".mtxt");
	}
	std::ofstream outTxtFile;
	outTxtFile.open(outputFilename.c_str(), std::ios::out | std::ios::trunc);
	
	if(outTxtFile.is_open())
	{
		outTxtFile << "m=" << matrix->m << std::endl;
		outTxtFile << "n=" << matrix->n << std::endl;
		
		int totalElements = matrix->n * matrix->m;
		int lastElement = totalElements-1;
		for(int i = 0; i < totalElements; i++)
		{
			if(i == lastElement)
			{
				outTxtFile << matrix->matrix[i];
			}
			else
			{
				outTxtFile << matrix->matrix[i] << ",";
			}
		}
		outTxtFile.flush();
		outTxtFile.close();
	}
	else
	{
		throw OutputStreamException("Could not open text file.");
	}
}

void Matrices::saveMatrix2txtOptions(Matrix *matrix, std::string filepath, outTXTform outtxt)
{		
	if(outtxt == mtxt)
	{
		this->saveMatrix2txt(matrix, filepath);
	}
	else if(outtxt == gtxt)
	{
		this->saveMatrix2GridTxt(matrix, filepath);
	}
	else if(outtxt == csv)
	{
		this->saveMatrix2CSV(matrix, filepath);
	}
	else 
	{
		throw MatricesException("Txt format not recognised!");
	}

}

void Matrices::saveGSLMatrix2GridTxt(gsl_matrix *gslMatrix, std::string filepath)
{
	Matrix *rsgisMatrix;
	rsgisMatrix = this->convertGSL2Matrix(gslMatrix);
	this->saveMatrix2GridTxt(rsgisMatrix, filepath);
	this->freeMatrix(rsgisMatrix);
}

void Matrices::saveGSLMatrix2Txt(gsl_matrix *gslMatrix, std::string filepath)
{
	Matrix *rsgisMatrix;
	rsgisMatrix = this->convertGSL2Matrix(gslMatrix);
	this->saveMatrix2txt(rsgisMatrix, filepath);
	this->freeMatrix(rsgisMatrix);
}

void Matrices::saveMatrix2Binary(Matrix *matrix, std::string filepath)
{
	std::ofstream matrixOutput;
	std::string matrixFilepath = filepath;
	std::string ext = getFileExt(filepath);
	if(ext != ".mtx")
	{
		matrixFilepath = filepath + std::string(".mtx");
	}
	matrixOutput.open(matrixFilepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	if(!matrixOutput.is_open())
	{
		throw OutputStreamException("Could not open output stream for Matrix output.");
	}
	
	matrixOutput.write((char *) matrix->m, 4);
	matrixOutput.write((char *) matrix->n, 4);
	
	int matrixLength = matrix->m * matrix->n;
	for(int i = 0; i < matrixLength; i++)
	{
		matrixOutput.write((char *) &matrix->matrix[i], 4);
	}
	
	matrixOutput.flush();
	matrixOutput.close();
}

Matrix* Matrices::readMatrixFromTxt(std::string filepath)
{
	Matrix *matrix = new Matrix();
	std::ifstream inputMatrix;
	inputMatrix.open(filepath.c_str());
	if(!inputMatrix.is_open())
	{
		throw InputStreamException("Could not open input text file.");
	}
	else
	{
		std::string strLine;
		std::string word;
		int number;
		float value;
		int lineCounter = 0;
		inputMatrix.seekg(std::ios_base::beg);
		while(!inputMatrix.eof())
		{
			getline(inputMatrix, strLine, '\n');
			if(strLine.length() > 0)
			{
				if(lineCounter == 0)
				{
					// m
					word = strLine.substr(2);
					number = strtol(word.c_str(), NULL, 10);
					matrix->m = number;
				}
				else if(lineCounter == 1)
				{
					// n
					word = strLine.substr(2);
					number = strtol(word.c_str(), NULL, 10);
					matrix->n = number;
				}
				else if(lineCounter == 2)
				{
					// data
					int dataCounter = 0;
					int start = 0;
					int lineLength = strLine.length();
					int numDataPoints = matrix->n*matrix->m;
					matrix->matrix = new double[numDataPoints];
					for(int i = 0; i < lineLength; i++)
					{
						if(strLine.at(i) == ',')
						{
							word = strLine.substr(start, i-start);								
							value = strtod(word.c_str(), NULL);
							if(boost::math::isnan(value))
							{
								value = 0;
							}
							matrix->matrix[dataCounter] = value;
							dataCounter++;
							
							start = start + i-start+1;
						}
						
						if(dataCounter >= numDataPoints)
						{
							throw MatricesException("Too many data values, compared to header.");
						}
					}
					word = strLine.substr(start);
					value = strtod(word.c_str(), NULL);
					matrix->matrix[dataCounter] = value;
					dataCounter++;
											
					if(dataCounter != (matrix->n*matrix->m))
					{
						throw MatricesException("An incorrect number of data points were read in.");
					}
					
				}
				else
				{
					break;
				}
			}
			lineCounter++;
		}
		
		if(lineCounter < 3)
		{
			throw MatricesException("A complete matrix has not been reconstructed.");
		}
		inputMatrix.close();
	}
	return matrix;
}

Matrix* Matrices::readMatrixFromGridTxt(std::string filepath)
{
	Matrix *matrix = new Matrix();
	std::ifstream inputMatrix;
	inputMatrix.open(filepath.c_str());
	if(!inputMatrix.is_open())
	{
		throw InputStreamException("Could not open input text file.");
	}
	else
	{
		std::string strLine;
		std::string wholeline;
		std::string word;
		int number;
		float value;
		int lineCounter = 0;
		bool first = true;
		inputMatrix.seekg(std::ios_base::beg);
		while(!inputMatrix.eof())
		{
			getline(inputMatrix, strLine, '\n');
			if(strLine.length() > 0)
			{
				if(lineCounter == 0)
				{
					// m
					word = strLine.substr(2);
					number = strtol(word.c_str(), NULL, 10);
					matrix->m = number;
				}
				else if(lineCounter == 1)
				{
					// n
					word = strLine.substr(2);
					number = strtol(word.c_str(), NULL, 10);
					matrix->n = number;
				}
				else 
				{
					if(first)
					{
						wholeline = strLine;
						first = false;
					}
					else 
					{
						wholeline = wholeline + std::string(",") + strLine;
					}
				}
				lineCounter++;
			}
		}
		inputMatrix.close();
		
		// data
		int dataCounter = 0;
		int start = 0;
		int lineLength = wholeline.length();;
		int numDataPoints = matrix->n*matrix->m;
		matrix->matrix = new double[numDataPoints];
		
		for(int i = 0; i < lineLength; i++)
		{
			if(wholeline.at(i) == ',')
			{
				word = wholeline.substr(start, i-start);								
				value = strtod(word.c_str(), NULL);
				matrix->matrix[dataCounter] = value;
				dataCounter++;
				
				start = start + i-start+1;
			}
			
			if(dataCounter >= numDataPoints)
			{
				throw MatricesException("Too many data values, compared to header.");
			}
		}
		
		word = wholeline.substr(start);
		value = strtod(word.c_str(), NULL);
		matrix->matrix[dataCounter] = value;
		dataCounter++;
		
		if(dataCounter != (matrix->n*matrix->m))
		{
			throw MatricesException("An incorrect number of data points were read in.");
		}
	}
	return matrix;
}


Matrix* Matrices::readMatrixFromBinary(std::string filepath)
{
	Matrix *matrix = new Matrix();
	std::string matrixFilepath = filepath + std::string(".mtx");
	std::ifstream matrixInput;
	matrixInput.open(matrixFilepath.c_str(), std::ios::in | std::ios::binary);
	if(!matrixInput.is_open())
	{
		throw InputStreamException("Could not open matrix binary file.");
	}
	
	matrixInput.seekg (0, std::ios::end);
	long end = matrixInput.tellg();
	matrixInput.seekg (0, std::ios::beg);
	int matrixSizeFile = (end/16) - 2;
	
	matrixInput.read((char *) &matrix->m, 4);
	matrixInput.read((char *) &matrix->n, 4);
	
	int matrixSize = matrix->m * matrix->n;
	if(matrixSizeFile != matrixSize)
	{
		throw MatricesException("The file size and header differ on the number of points.");
	}
	
	matrix->matrix = new double[matrixSize];
	
	for(int i = 0; i < matrixSize; i++)
	{
		matrixInput.read((char *) &matrix->matrix[i], 4);
	}
	
	matrixInput.close();
	return matrix;
}

gsl_matrix* Matrices::readGSLMatrixFromTxt(std::string filepath)
{
	Matrix *rsgisMatrix;
	gsl_matrix *gslMatrix;
	rsgisMatrix = this->readMatrixFromTxt(filepath);
	gslMatrix = this->convert2GSLMatrix(rsgisMatrix);
	this->freeMatrix(rsgisMatrix);
	return gslMatrix;
}

gsl_matrix* Matrices::readGSLMatrixFromGridTxt(std::string filepath)
{
	Matrix *rsgisMatrix;
	gsl_matrix *gslMatrix;
	rsgisMatrix = this->readMatrixFromGridTxt(filepath);
	gslMatrix = this->convert2GSLMatrix(rsgisMatrix);
	this->freeMatrix(rsgisMatrix);
	return gslMatrix;
}

gsl_matrix* Matrices::readGSLMatrixFromBinary(std::string filepath)
{
	Matrix *rsgisMatrix;
	gsl_matrix *gslMatrix;
	rsgisMatrix = this->readMatrixFromBinary(filepath);
	gslMatrix = this->convert2GSLMatrix(rsgisMatrix);
	this->freeMatrix(rsgisMatrix);
	return gslMatrix;
}

void Matrices::calcEigenVectorValue(Matrix *matrix, Matrix *eigenvalues, Matrix *eigenvectors)
{
	
	if(eigenvalues->m != eigenvectors->m)
	{
		throw MatricesException("Eigenvalues and Eigenvectors matrix need to be the same length");
	}
	
	gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(matrix->n);
	gsl_matrix_view inputMatrix = gsl_matrix_view_array (matrix->matrix, matrix->n, matrix->m);
	gsl_vector *eigenValuesGSL = gsl_vector_alloc (matrix->n);
	gsl_matrix *eigenVectorsGSL = gsl_matrix_alloc (matrix->n, matrix->n);
	gsl_eigen_symmv(&inputMatrix.matrix, eigenValuesGSL, eigenVectorsGSL, workspace);
	gsl_eigen_symmv_free(workspace);
	gsl_eigen_symmv_sort (eigenValuesGSL, eigenVectorsGSL, GSL_EIGEN_SORT_ABS_DESC);
	
	gsl_vector_view evec_i;
	int index = 0;
	
	for (int i = 0; i < eigenvectors->m; i++)
	{
		eigenvalues->matrix[i] = gsl_vector_get(eigenValuesGSL, i);
		
		evec_i = gsl_matrix_column(eigenVectorsGSL, i);
		for(int j = 0; j < eigenvectors->n; j++)
		{
			index = (j*matrix->n)+i;
			eigenvectors->matrix[index] = gsl_vector_get(&evec_i.vector, j);
		}
	}
	
	gsl_vector_free (eigenValuesGSL);
	gsl_matrix_free (eigenVectorsGSL);
}

void Matrices::exportAsImage(Matrix *matrix, std::string filepath, std::string format)
{
	GDALAllRegister();
	GDALDataset *outputImageDS = NULL;
	GDALRasterBand *outputRasterBand = NULL;
	GDALDriver *gdalDriver = NULL;
	float *row;
	
	try
	{
		// Create new Image
		gdalDriver = GetGDALDriverManager()->GetDriverByName(format.c_str());
		if(gdalDriver == NULL)
		{
			throw MatricesException("Image output error: image driver does not exists..");
		}
		outputImageDS = gdalDriver->Create(filepath.c_str(), matrix->m, matrix->n, 1, GDT_Float32, gdalDriver->GetMetadata());
		outputRasterBand = outputImageDS->GetRasterBand(1);
		
		row = (float *) CPLMalloc(sizeof(float)*matrix->m);
		
		for(int i = 0; i < matrix->n; i++)
		{
			for(int j = 0; j < matrix->m; j++)
			{
				row[j] = (float) matrix->matrix[(i*matrix->m)+j];
			}
			
			outputRasterBand->RasterIO(GF_Write, 0, i, matrix->m, 1, row, matrix->m, 1, GDT_Float32, 0, 0);
		}
		
		
		delete row;
		GDALClose(outputImageDS);
	}
	catch(MatricesException &e)
	{
		throw e;
	}
	
}

Matrix* Matrices::normalisedMatrix(Matrix *matrix, double min, double max)
{
	double matrixMIN = 0;
	double matrixMAX = 0;
	double matrixDIFF = 0;
	double inDIFF = 0;
	bool first = true;
	int size = matrix->m * matrix->n;
	
	for(int i = 0; i < size; i++)
	{
		if(first)
		{
			matrixMIN = matrix->matrix[i];
			matrixMAX = matrix->matrix[i];
			first = false;
		}
		else
		{
			if( matrix->matrix[i] > matrixMAX)
			{
				matrixMAX = matrix->matrix[i];
			}
			else if( matrix->matrix[i] < matrixMIN)
			{
				matrixMIN = matrix->matrix[i];
			}
		}
	}
	
	inDIFF = max - min;
	matrixDIFF = matrixMAX - matrixMIN;
	
	Matrix *outMatrix = this->createMatrix(matrix->n, matrix->m);
	double norm = 0;
	
	for(int i = 0; i < size; i++)
	{
		norm = (matrix->matrix[i] - matrixMIN)/matrixDIFF;
		outMatrix->matrix[i] = (norm * inDIFF) + min;
	}
	
	return outMatrix;
}

Matrix* Matrices::normalisedColumnsMatrix(Matrix *matrix)
{
	Matrix *outMatrix = this->createMatrix(matrix);
	
	float *normalisingVals = new float[matrix->m];
	for(int i = 0; i < matrix->m; ++i)
	{
		normalisingVals[i] = 0;
		for(int j = 0; j < matrix->n; ++j)
		{
			normalisingVals[i] += (matrix->matrix[(j*matrix->m)+i]*matrix->matrix[(j*matrix->m)+i]);
		}
		
		normalisingVals[i] = sqrt(normalisingVals[i]);
	}
	
	for(int i = 0; i < matrix->m; ++i)
	{
		for(int j = 0; j < matrix->n; ++j)
		{
			outMatrix->matrix[(j*matrix->m)+i] = matrix->matrix[(j*matrix->m)+i]/normalisingVals[i];
		}            
	}
	
	delete[] normalisingVals;
	
	return outMatrix;
}

gsl_matrix* Matrices::normalisedColumnsMatrix(gsl_matrix *matrix)
{
	gsl_matrix *outMatrix = gsl_matrix_alloc (matrix->size1, matrix->size2);
	
	float *normalisingVals = new float[matrix->size2];
	for(unsigned int i = 0; i < matrix->size2; ++i)
	{
		normalisingVals[i] = 0;
		for(unsigned int j = 0; j < matrix->size1; ++j)
		{
			double melement = gsl_matrix_get(matrix, j, i);
			normalisingVals[i] += melement*melement;
		}
		
		normalisingVals[i] = sqrt(normalisingVals[i]);
	}
	
	for(unsigned int i = 0; i < matrix->size2; ++i)
	{
		for(unsigned int j = 0; j < matrix->size1; ++j)
		{
			double melement = gsl_matrix_get(matrix, j,i)/normalisingVals[i];
			gsl_matrix_set(outMatrix,j,i,melement);
		}            
	}
	
	delete[] normalisingVals;
	
	return outMatrix;
}


Matrix* Matrices::duplicateMatrix(Matrix *matrix, int xDuplications, int yDuplications)
{
	int newM = matrix->m * xDuplications;
	int newN = matrix->n * yDuplications;
	
	Matrix *outMatrix = this->createMatrix(newN, newM);
	
	int column = 0;
	int row = 0;
	int width = matrix->m;
	int height = matrix->n;
	int length = (width * xDuplications) * height;
			
	int inCounter = 0;
	int outCounter = 0;
	int xDupCount = 0;
	
	for(int n = 0; n < yDuplications; n++)
	{
		inCounter = 0;
		xDupCount = 0;
		outCounter = n * length;
		
		for(int i = 0; i < length; i++)
		{
			outMatrix->matrix[outCounter++] = matrix->matrix[inCounter++];
			
			column++;
			if(column == width)
			{
				xDupCount++;
				
				if(xDupCount < xDuplications)
				{
					inCounter = inCounter - width;
				}
				else
				{
					row++;
					xDupCount = 0;
				}
				column = 0;
			}
		}
	}		
	
	return outMatrix;
}

gsl_matrix* Matrices::convert2GSLMatrix(Matrix *matrix)
{
	/// Converts  matrix to a GSL matrix
	gsl_matrix *convertedMatrix = gsl_matrix_alloc (matrix->n, matrix->m);
	
	int index = 0;
	for(int i = 0; i < matrix->n; i++)  // Loop through rows
	{
		for(int j = 0; j < matrix->m; j++) // Loop through columns
		{
			double melement = matrix->matrix[index++];
			gsl_matrix_set(convertedMatrix,i,j,melement);
		}
	}
	
	return convertedMatrix;
}

Matrix* Matrices::convertGSL2Matrix(gsl_matrix *matrix)
{
	/// Converts  matrix to a GSL matrix
	Matrix *convertedMatrix = this->createMatrix(matrix->size1, matrix->size2);		
	int index = 0;
	
	for(unsigned int i = 0; i < matrix->size1; i++) // Loop through rows
	{
		for(unsigned int j = 0; j < matrix->size2; j++) // Loop through columns
		{
			double melement = gsl_matrix_get(matrix, i, j);
			convertedMatrix->matrix[index++] = melement;
		}
	}
	
	return convertedMatrix;
}


void Matrices::makeCircularBinaryMatrix(Matrix *matrix)
{
	if(matrix->n != matrix->m)
	{
		throw MatricesException("Matrix must be square.");
	}
	if(matrix->n % 2 == 0)
	{
		throw MatricesException("Matrix size must be odd.");
	}
	
	int index = 0;
	int xCoord = ((matrix->n-1)/2)*(-1);
	int yCoord = ((matrix->n-1)/2);
	int radius = (matrix->n-1)/2;
	float radiusSq = (radius+0.25) * (radius+0.25);
	int distSq = 0;
	
	for(int i = 0; i < matrix->n; i++)  // Loop through rows
	{
		xCoord = ((matrix->n-1)/2)*(-1);
		for(int j = 0; j < matrix->m; j++) // Loop through columns
		{
			distSq = (xCoord*xCoord) + (yCoord*yCoord);
			if(distSq <= radiusSq)
			{
				matrix->matrix[index++] = 1.0;
			}
			else
			{
				matrix->matrix[index++] = 0.0;
			}
			++xCoord;
		}

		--yCoord;
	}
}

Matrices::~Matrices()
{
	
}

