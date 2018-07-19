#pragma once
// ------------------------------------------------------------------------------------------------
// Image class Header file
// ------------------------------------------------------------------------------------------------


#ifndef __IMAGEPROC_H
#define __IMAGEPROC_H

#include "Image.h"

// ------------------------------------------------------------------------------------------------
// ImageProc class
// ------------------------------------------------------------------------------------------------

class ImageProc : public Image
{
private:
	byte xClip(double x) {
		if (x < 0) return 0;
		if (x > 255) return 255;
		return (byte)x;
	}


public:
	// pixel processing
	void convertToGray();
	void convertToSepia();
	void samplingBy2();
	void quantization(int step);
	void Kuwahara();
	void upscaling(int n);
	void downscaling(int n);
	void mirroring();
	void rotation(int tha);
	void gamma(float g);
	void histogram();
	void embossing();
	void noise();
	void contrast();
	void Blurring();
	void Gaussian();
	void sharpening();
	void smoothing();
	void HSI();
	void kmean();
	void compensation();

};

#endif