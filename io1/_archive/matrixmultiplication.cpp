#include "pch.h"
#include "framework.h"

#include "MatrixMultiplication.h"


void CMatrixMultiplication::MatrixMultiplication(CMatrix& first, CMatrix& second, CMatrix& res)
{
	//alokacja
	double** temp_matrix = new double* [second.columns];
	for (unsigned i = 0; i < second.columns; i++) {
		temp_matrix[i] = new double[second.rows];
	}

	//transponowanie
	for (unsigned i = 0; i < second.rows; i++) {
		for (unsigned j = 0; j < second.columns; j++) {
			temp_matrix[j][i] = second.data[i][j];
		}
	}
	double fRes;
	//mnozenie
	for(int i = 0; i < first.rows; i++)
		for(int j = 0; j < second.columns; j++)
		{
			fRes = 0;
			for(int q = 0; q < first.columns; q++)			
				fRes += first.data[i][q] * temp_matrix[j][q];			
			res.data[i][j] = fRes;
		}

	//dealokacja
	for (unsigned i = 0; i < second.columns; i++) {
		delete[] temp_matrix[i];
	}
	delete[] temp_matrix;
}