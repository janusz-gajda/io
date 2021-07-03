#include "pch.h"
#include "framework.h"

#include "HistogramStretching.h"



void CHistogramStretching::HistogramStretching(BYTE** pImage, int nW, int nH)
{
	if (nW && nH) {
		//find minimal and maximal value
		int nMin, nMax;
		nMin = nMax = pImage[0][0];
		for (unsigned i = 0; i < nH; i++){
			for (unsigned j = 0; j < nW; j++) {
				if (nMin == 0 && nMax == 255)
					break;
				if (pImage[i][j] < nMin)
					nMin = pImage[i][j];
				else if (pImage[i][j] > nMax)
					nMax = pImage[i][j];
			}
		}


		//normalize the image values
		if (nMax != nMin) {
			const float fScale = 100.0 / (nMax - nMin);
			if (nW * nH >= 256) {
				int refrence_table[256];
				for (unsigned i = 0; i < 256; i++) {
					refrence_table[i] = (int)(((i - nMin) * fScale) + 0.5);
				}
				for (unsigned i = 0; i < nH; i++) {
					for (unsigned j = 0; j < nW; j++) {

						pImage[i][j] = refrence_table[pImage[i][j]];
					}
				}
			}
			else {
				for (unsigned i = 0; i < nH; i++) {
					for (unsigned j = 0; j < nW; j++) {
						pImage[i][j] = (int)(((pImage[i][j] - nMin) * fScale) + 0.5);
					}
				}
			}
		}
		else {
			for (unsigned i = 0; i < nH; i++) {
				for (unsigned j = 0; j < nW; j++) {
					pImage[i][j] = 0;//if all pixel values are the same, the image is changed to black
				}
			}
		}
	}
}
