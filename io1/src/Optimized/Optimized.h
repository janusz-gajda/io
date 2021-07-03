// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the BASELINE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// BASELINE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include "ITest.h"
#include "OptimizedAccessor.h"


#ifdef BASELINE_EXPORTS
#define BASELINE_API __declspec(dllexport)
#else
#define BASELINE_API __declspec(dllimport)
#endif

//// This class is exported from the dll
//class BASELINE_API COptimized {
//public:
//	COptimized(void);
//	// TODO: add your methods here.
//};
//
//extern BASELINE_API int nOptimized;
//
//BASELINE_API int fnOptimized(void);



//#define DLL_INTERFACE __declspec( dllexport )   

struct image
{
	BYTE* pImg;
};

class COptimized : public ITest
{
public:
	COptimized() {}
	~COptimized() {}


	void HistogramStretching(BYTE** pImage, int nW, int nH);
	void ImageFiltering(BYTE* pInImg, int nW, int nH, BYTE* pOutImg);
	void MatrixMultiplication(CMatrix& first, CMatrix& second, CMatrix& res);

};