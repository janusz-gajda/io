#include "pch.h"
#include "framework.h"

#include "ImageFiltering.h"


#define GetIndex(x, y, nW) (((y)*(nW)) + (x))

void CImageFiltering::ImageFiltering(BYTE* pInImg, int nW, int nH, BYTE* pOutImg)
{
			
	if (nW && nH) {
		const unsigned width = nW;
		const unsigned height = nH;
		unsigned fSum;
		unsigned index;
		for (unsigned int j = 1; j < height - 1; j++)
			for (unsigned int i = 1; i < width - 1; i++)
			{	
				index = j * width + i;
				
				fSum = pInImg[index - width - 1];
				fSum += pInImg[index - width] << 1;
				fSum += pInImg[index - width + 1];

				fSum += pInImg[index - 1] << 1;
				fSum += pInImg[index] << 2;
				fSum += pInImg[index + 1] << 1;

				fSum += pInImg[index + width - 1];
				fSum += pInImg[index + width] << 1;
				fSum += pInImg[index + width + 1];

				pOutImg[index] = static_cast<BYTE>(fSum >> 4);
			}
	}
}