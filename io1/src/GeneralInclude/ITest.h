#pragma once

#define DLL_INTERFACE __declspec( dllexport )   
typedef unsigned char       BYTE;

struct CMatrix 
{
	double** data; //two-dimensional array
	int rows; //number of rows
	int columns; //number of columns
};


struct ITest
{
	virtual void HistogramStretching(BYTE** pImage, int nW, int nH) = 0;
	virtual void ImageFiltering(BYTE* pInImg, int nW, int nH, BYTE* pOutImg) = 0;
	virtual void MatrixMultiplication(CMatrix& first, CMatrix& second, CMatrix& res) = 0;


};
