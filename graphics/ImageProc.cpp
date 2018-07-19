// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------
#define PI 3.141592653589;
#include "ImageProc.h"
#include <glut.h>
#include "Image.h"
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
// ------------------------------------------------------------------------------------------------
// Convert to gray-scale
// ------------------------------------------------------------------------------------------------
void ImageProc::convertToGray()
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			Gray = xClip(0.299*R + 0.587*G + 0.114*B);

			setPixel(x, y, Gray, Gray, Gray);
		}
	}
}
void ImageProc::samplingBy2()
{
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[(m_iWidth*m_iHeight * 3) / 4];
	for (y = 0; y < m_iHeight / 2; y++)
	{
		for (x = 0; x < m_iWidth / 2; x++)
		{

			getPixel(x * 2, y * 2, R, G, B);
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 0] = R;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 1] = G;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
	m_iWidth /= 2;
	m_iHeight /= 2;
}
void ImageProc::convertToSepia()
{
	int  x, y;
	byte R, G, B;
	byte _R, _G, _B;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			_R = xClip(0.393*R + 0.769*G + 0.189*B);
			_G = xClip(0.349*R + 0.686*G + 0.168*B);
			_B = xClip(0.272*R + 0.534*G + 0.131*B);
			setPixel(x, y, _R, _G, _B);
		}
	}

}


void ImageProc::upscaling(int n)
{
	int  x, y;
	byte R1, G1, B1;
	byte R2, G2, B2;
	byte R3, G3, B3;
	byte R4, G4, B4;
	byte* rgb = new byte[(m_iWidth*n)*(m_iHeight*n) * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			if (x + 1 == m_iWidth || y + 1 == m_iHeight)
				continue;
			getPixel(x, y, R1, G1, B1);
			getPixel(x + 1, y, R2, G2, B2);
			getPixel(x, y + 1, R3, G3, B3);
			getPixel(x + 1, y + 1, R4, G4, B4);
			for (int i = 0; i< n + 1; i++) {
				for (int j = 0; j < n + 1; j++) {
					float a = (float)i / n, b = (float)j / n;

					rgb[((y*n + i) *((m_iWidth*n)) * 3 + (x*n + j) * 3) + 0] = (1 - a)*(1 - b)*R1 + b*(1 - a)*R2 + (1 - b)*a*R3 + a*b*R4;
					rgb[((y*n + i) *((m_iWidth*n)) * 3 + (x*n + j) * 3) + 1] = (1 - a)*(1 - b)*G1 + b*(1 - a)*G2 + (1 - b)*a*G3 + a*b*G4;
					rgb[((y*n + i) *((m_iWidth*n)) * 3 + (x*n + j) * 3) + 2] = (1 - a)*(1 - b)*B1 + b*(1 - a)*B2 + (1 - b)*a*B3 + a*b*B4;
				}
			}
		}
	}
	setRGB(rgb);
	m_iWidth = m_iWidth*n;
	m_iHeight = m_iHeight*n;
}
void ImageProc::downscaling(int n)
{
	int  x, y;
	byte R, G, B;
	int mean = n / 2;
	byte* rgb = new byte[(m_iWidth*m_iHeight * 3) / (n*n)];
	int dx = m_iWidth / n, dy = m_iHeight / n;
	for (y = 0; y < dy; y++)
	{
		for (x = 0; x <dx; x++)
		{
			getPixel((x * n) + mean, (y * n) + mean, R, G, B);
			rgb[(y * dx * 3 + x * 3) + 0] = R;
			rgb[(y * dx * 3 + x * 3) + 1] = G;
			rgb[(y * dx * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
	m_iWidth = dx;
	m_iHeight = dy;
}

void ImageProc::rotation(int theta)
{
	int  x, y;
	int dx, dy;
	byte R, G, B;
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	double radian = theta / 180.0*PI;
	double c = cos(radian), s = sin(-radian);
	double xc = (double)m_iWidth / 2.0, yc = (double)m_iHeight / 2.0;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			dx = (int)(xc + ((double)y - yc)*s + ((double)x - xc)*c);
			dy = (int)(yc + ((double)y - yc)*c - ((double)x - xc)*s);
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = 0;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = 0;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = 0;
			if ((dy >= 0 && dy<m_iHeight) && (dx >= 0 && dx<m_iWidth)) {
				getPixel(dx, dy, R, G, B);
				rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
				rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
				rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
			}
		}
	}
	setRGB(rgb);

}
void ImageProc::gamma(float g) {
	byte LUT[256];
	float inv = 1 / g;
	for (int i = 0; i < 256; i++) {
		double L = (pow(i, inv));
		LUT[i] = L;
		if (L > 255)
			LUT[i] = 255;
	}
	int  x, y;
	byte R, G, B;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);
			setPixel(x, y, LUT[R], LUT[G], LUT[B]);
		}
	}
}
void ImageProc::contrast() {
	byte LUT[256];
	for (int i = 0; i < 256; i++) {
		if (i<50)
			LUT[i] = 0;
		else if (i < 200) {
			float s = i - 50;
			s = s / 150 * 255;
			LUT[i] = s;
		}
		else
			LUT[i] = 255;
	}
	int  x, y;
	byte R, G, B;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);
			setPixel(x, y, LUT[R], LUT[G], LUT[B]);
		}
	}
}
void ImageProc::mirroring()
{
	int x, y;
	byte R, G, B, dR, dG, dB;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth / 2; x++)
		{
			getPixel(x, y, R, G, B);
			getPixel(m_iWidth - 1 - x, y, dR, dG, dB);
			setPixel(m_iWidth - 1 - x, y, R, G, B);
			setPixel(x, y, dR, dG, dB);
		}
	}
}
void ImageProc::histogram() {
	double* H = new double[m_iHeight*m_iWidth];
	double* S = new double[m_iHeight*m_iWidth];
	double* I = new double[m_iHeight*m_iWidth];
	byte R, G, B;


	double dR, dG, dB;
	double angle1, angle2;
	int histogram[256] = {};
	int x, y;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);
			double minRGB;
			minRGB = (double)R;
			double RGB[3] = { (double)R,(double)G,(double)B };
			for (int i = 0; i < 3; i++) {
				if (RGB[i] < minRGB)
					minRGB = RGB[i];
			}
		
			H[y*m_iWidth + x] = (double)acos(-(double)((0.5f*((R - G) + (R - B))) / sqrt((R - G)*(R - G) + (R - B)*(G - B)))) * 360 / 255;
			S[y*m_iWidth + x] = (double)(1 - (3 / (R, G, B))*minRGB) / 255;
			I[y*m_iWidth + x] = (double)((R, G, B) / 3) / 255;
			int i = (R + G + B) / 3;
			histogram[i]++;
		}
	}
	for (int i = 1; i < 256; i++) {
		histogram[i] += histogram[i - 1];
	}
	for (int i = 0; i < 256; i++) {
		histogram[i] = histogram[i] * 255 / (m_iHeight*m_iWidth);
	}
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			int i = I[y*m_iWidth + x] * 255;
			I[y*m_iWidth + x] = (double)histogram[i] / 255;
			if (I[y*m_iWidth + x] <= 0) {
				setPixel(x, y, 0, 0, 0);
				continue;
			}
			if (I[y*m_iWidth + x] >= 1) {
				setPixel(x, y, 255, 255, 255);
				continue;
			}
			if (H[y*m_iWidth + x] < 0)
				H[y*m_iWidth + x] += 360;
			if (H[y*m_iWidth + x] <= 120) {
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dB = (1 - S[y*m_iWidth + x]) / 3;
				dR = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dG = 1 - dR - dB;
			}
			else if (H[y*m_iWidth + x]>120 && H[y*m_iWidth + x] <= 240) {
				H[y*m_iWidth + x] = H[y*m_iWidth + x] - 120;
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dR = (1 - S[y*m_iWidth + x]) / 3;
				dG = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dB = 1 - dR - dG;
			}
			else {
				H[y*m_iWidth + x] = H[y*m_iWidth + x] - 240;
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dG = (1 - S[y*m_iWidth + x]) / 3;
				dB = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dR = 1 - dG - dB;
			}
			dR = dR * 255 * 3 * I[y*m_iWidth + x];
			dG = dG * 255 * 3 * I[y*m_iWidth + x];
			dB = dB * 255 * 3 * I[y*m_iWidth + x];
			if (dR > 255)dR = 255;
			if (dG > 255)dG = 255;
			if (dB > 255)dB = 255;
			if (dR < 0)dR = 0;
			if (dG < 0)dG = 0;
			if (dB < 0)dB = 0;
			R = (unsigned char)dR; G = (unsigned char)dG; B = (unsigned char)dB;
			setPixel(x, y, R, G, B);
		}
	}
}
void ImageProc::embossing() {
	int matrix[3][3] = { { 0,1,2 },{ -1,1,1 },{ -2,-1,0 } }, dR[3][3], dG[3][3], dB[3][3];
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[i + 1][j + 1] = 0;
						dG[i + 1][j + 1] = 0;
						dB[i + 1][j + 1] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[i + 1][j + 1] = R*matrix[i + 1][j + 1];
					dG[i + 1][j + 1] = G*matrix[i + 1][j + 1];
					dB[i + 1][j + 1] = B*matrix[i + 1][j + 1];
				}
			}
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					r += dR[i][j];
					g += dG[i][j];
					b += dB[i][j];
				}
			}
			if (r < 0)r = 0;
			if (r > 255)r = 255;
			if (g < 0)g = 0;
			if (g > 255)g = 255;
			if (b < 0)b = 0;
			if (b > 255)b = 255;
			R = r; G = g; B = b;
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
}
void ImageProc::Blurring() {
	int matrix[3][3] = { { 1,1,1 },{ 1,1,1 },{ 1,1,1 } }, dR[3][3], dG[3][3], dB[3][3];
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[i + 1][j + 1] = 0;
						dG[i + 1][j + 1] = 0;
						dB[i + 1][j + 1] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[i + 1][j + 1] = R*matrix[i + 1][j + 1];
					dG[i + 1][j + 1] = G*matrix[i + 1][j + 1];
					dB[i + 1][j + 1] = B*matrix[i + 1][j + 1];
				}
			}
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					r += dR[i][j];
					g += dG[i][j];
					b += dB[i][j];
				}
			}
			R = r / 9; G = g / 9; B = b / 9;
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
}
void ImageProc::kmean() {
	int K = 8;
	int loop = 1;
	int* cluster = new int[m_iHeight*m_iWidth];
	int precluster;
	double sum[8][3];
	double center[8][3];
	double min = 9999999999.9;
	int minIndex;
	int number[8];
	double dist;
	byte R, G, B;
	for (int k = 0; k < K; k++) {
		int x, y;
		x = rand() % m_iWidth;
		y = rand() % m_iHeight;
		getPixel(x, y, R, G, B);
		center[k][0] = R;
		center[k][1] = G;
		center[k][2] = B;
	}
	for (int i = 0; i < m_iHeight*m_iWidth; i++) {
		cluster[i] = K + 1;
	}
	loop = 20;
	while (loop >0) {
		for (int y = 0; y < m_iHeight; y++) {
			for (int x = 0; x < m_iWidth; x++) {
				precluster = cluster[y*m_iWidth + x];
				getPixel(x, y, R, G, B);
				double min = 9999999999.9;
				for (int k = 0; k < K; k++) {
					dist = sqrt(pow(R - center[k][0], 2) + pow(G - center[k][1], 2) + pow(B - center[k][2], 2));
					if (dist < min) {
						min = dist;
						minIndex = k;
					}
				}
				cluster[y*m_iWidth + x] = minIndex;
			}
		}
		for (int k = 0; k < K; k++) {
			sum[k][0] = 0;
			sum[k][1] = 0;
			sum[k][2] = 0;
			number[k] = 0;
		}
		for (int y = 0; y < m_iHeight; y++) {
			for (int x = 0; x < m_iWidth; x++) {
				getPixel(x, y, R, G, B);
				sum[cluster[y*m_iWidth + x]][0] += R;
				sum[cluster[y*m_iWidth + x]][1] += G;
				sum[cluster[y*m_iWidth + x]][2] += B;
				number[cluster[y*m_iWidth + x]]++;
			}
		}
		for (int k = 0; k < K; k++) {
			center[k][0] = sum[k][0] / number[k];
			center[k][1] = sum[k][1] / number[k];
			center[k][2] = sum[k][2] / number[k];
		}
		loop--;
	}
	for (int y = 0; y < m_iHeight; y++) {
		for (int x = 0; x < m_iWidth; x++) {
			setPixel(x, y, center[cluster[y*m_iWidth + x]][0], center[cluster[y*m_iWidth + x]][1], center[cluster[y*m_iWidth + x]][2]);

		}
	}
}
void ImageProc::Gaussian() {
	int matrix[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } }, dR[3][3], dG[3][3], dB[3][3];
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[i + 1][j + 1] = 0;
						dG[i + 1][j + 1] = 0;
						dB[i + 1][j + 1] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[i + 1][j + 1] = R*matrix[i + 1][j + 1];
					dG[i + 1][j + 1] = G*matrix[i + 1][j + 1];
					dB[i + 1][j + 1] = B*matrix[i + 1][j + 1];
				}
			}
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					r += dR[i][j];
					g += dG[i][j];
					b += dB[i][j];
				}
			}
			R = r / 16; G = g / 16; B = b / 16;
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
}
void ImageProc::noise() {
	int  x, y;
	byte R, G, B;
	srand((unsigned int)time(NULL));
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			int chance = rand() % 10;
			if (chance == 0) {
				getPixel(x, y, R, G, B);
				setPixel(x, y, rand() % 255, rand() % 255, rand() % 255);
			}
		}
	}
}
void ImageProc::sharpening() {
	int matrix[3][3] = { { 0,-1,0 },{ -1,5,-1 },{ 0,-1,0 } }, dR[3][3], dG[3][3], dB[3][3];
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[i + 1][j + 1] = 0;
						dG[i + 1][j + 1] = 0;
						dB[i + 1][j + 1] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[i + 1][j + 1] = R*matrix[i + 1][j + 1];
					dG[i + 1][j + 1] = G*matrix[i + 1][j + 1];
					dB[i + 1][j + 1] = B*matrix[i + 1][j + 1];
				}
			}
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					r += dR[i][j];
					g += dG[i][j];
					b += dB[i][j];
				}
			}
			if (r < 0)r = 0;
			if (r > 255)r = 255;
			if (g < 0)g = 0;
			if (g > 255)g = 255;
			if (b < 0)b = 0;
			if (b > 255)b = 255;
			R = r; G = g; B = b;
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
}
void ImageProc::smoothing() {
	int  x, y;
	byte R, G, B, dR[9], dG[9], dB[9];
	byte* rgb = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[(i + 1)*(j + 1)] = 0;
						dG[(i + 1)*(j + 1)] = 0;
						dB[(i + 1)*(j + 1)] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[(i + 1)*(j + 1)] = R;
					dG[(i + 1)*(j + 1)] = G;
					dB[(i + 1)*(j + 1)] = B;
				}
			}
			byte temp;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (dR[j]<dR[i]) {
						temp = dR[i];
						dR[i] = dR[j];
						dR[j] = temp;
					}
					if (dG[j]<dG[i]) {
						temp = dG[i];
						dG[i] = dG[j];
						dG[j] = temp;
					}
					if (dB[j]<dB[i]) {
						temp = dB[i];
						dB[i] = dB[j];
						dB[j] = temp;
					}
				}
			}
			R = dR[4]; G = dG[4]; B = dB[4];
			rgb[(y * m_iWidth * 3 + x * 3) + 0] = R;
			rgb[(y * m_iWidth * 3 + x * 3) + 1] = G;
			rgb[(y * m_iWidth * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
}
void ImageProc::HSI() {
	double H, S, I;
	double RR, GG, BB;
	double angle1, angle2;
	int cnt = 0;

	byte * RGB = new byte[m_iWidth*m_iHeight * 3];
	RGB = getRGB();

	cnt = 0;

	for (int i = 0; i<m_iWidth; i++) {
		for (int j = 0; j<m_iWidth; j++) {
			H = (double)(RGB[(getAddr(i, j) + 0)] / 255.0)*360.0;
			S = (double)(RGB[(getAddr(i, j) + 1)] / 255.0);
			I = (double)(RGB[(getAddr(i, j) + 2)] / 255.0);

			if (I <= 0.0) {
				RGB[getAddr(i, j)] = 0;
				RGB[getAddr(i, j) + 1] = 0;
				RGB[getAddr(i, j) + 2] = 0;
				continue;
			}
			if (I >= 1.0) {
				RGB[getAddr(i, j)] = 255;
				RGB[getAddr(i, j) + 1] = 255;
				RGB[getAddr(i, j) + 2] = 255;
				continue;
			}

			if (H<0.0)
				H += 360;

			if (H<120.0) {
				angle1 = H*0.017453293;;
				angle2 = (60 - H)*0.017453293;;
				BB = (1.0 - S) / 3.0;
				RR = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				GG = 1.0 - RR - BB;
			}
			else if (120.0<H && H <= 240.0) {
				H = H - 120.0;
				angle1 = H*0.017453293;;
				angle2 = (60 - H)*0.017453293;;
				RR = (1.0 - S) / 3.0;
				GG = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				BB = 1.0 - RR - GG;
			}
			else {
				H = H - 240.0;
				angle1 = H*0.017453293;;
				angle2 = (60 - H)*0.017453293;;
				GG = (1.0 - S) / 3.0;
				BB = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				RR = 1.0 - GG - BB;
			}

			RR = RR*255.0*3.0*I;
			GG = GG*255.0*3.0*I;
			BB = BB*255.0*3.0*I;

			if (RR>255.0)
				RR = 255.0;
			if (GG>255.0)
				GG = 255.0;
			if (BB>255.0)
				BB = 255.0;

			RGB[getAddr(i, j)] = (unsigned char)(RR);
			RGB[getAddr(i, j) + 1] = (unsigned char)(GG);
			RGB[getAddr(i, j) + 2] = (unsigned char)(BB);

		}

	}


	setRGB(RGB);

}


void ImageProc::compensation() {
	double* H = new double[m_iHeight*m_iWidth];
	double* S = new double[m_iHeight*m_iWidth];
	double* I = new double[m_iHeight*m_iWidth];
	byte R, G, B;

	double dR, dG, dB;
	double angle1, angle2;
	int histogram[4][256] = {}, L[4] = {};
	int x, y, min = 0, max = 0, mid = 0;
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);
			double minRGB;
			minRGB = (double)R;
			double RGB[3] = { (double)R,(double)G,(double)B };
			for (int i = 0; i < 3; i++) {
				if (RGB[i] < minRGB)
					minRGB = RGB[i];
			}
			//To-do  위의 solHSI를 이용해서 solH,solS,solI 바꿀것
			/*	H[y*m_iWidth + x] = (double)solH(R, G, B) * 360 / 255;
			S[y*m_iWidth + x] = (double)solS(R, G, B) / 255;
			I[y*m_iWidth + x] = (double)solI(R, G, B) / 255;*/
			H[y*m_iWidth + x] = (double)acos(-(double)((0.5f*((R - G) + (R - B))) / sqrt((R - G)*(R - G) + (R - B)*(G - B)))) * 360 / 255;
			S[y*m_iWidth + x] = (double)(1 - (3 / (R, G, B))*minRGB) / 255;
			I[y*m_iWidth + x] = (double)((R, G, B) / 3) / 255;
			int i = (R + G + B) / 3;
			histogram[(y * 2 / m_iHeight) * 2 + (x * 2 / m_iWidth)][i]++;
			L[(y * 2 / m_iHeight) * 2 + (x * 2 / m_iWidth)] += i;
		}
	}
	for (int j = 0; j < 4; j++) {
		L[j] = L[j] / (m_iHeight*m_iWidth / 4);
		if (L[j] > L[max])
			max = j;
		if (L[j] < L[min])
			min = j;
		if (max != j&&min != j)
			mid = j;
		for (int i = 1; i < 256; i++) {
			histogram[j][i] += histogram[j][i - 1];

		}
		for (int i = 0; i < 256; i++) {
			histogram[j][i] = histogram[j][i] * 255 / (m_iHeight*m_iWidth);
		}
	}
	for (int i = 0; i < 256; i++) {
		printf("%d  %d %d %d %d \n", i, histogram[0][i], histogram[1][i], histogram[2][i], histogram[3][i]);
	}
	printf("\n%d %d %d\n\n", min, mid, max);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			histogram[mid][j];
			if (histogram[min][i] <= histogram[mid][j]) {
				histogram[min][i] = histogram[mid][j];
			}
			if (histogram[max][i] <= histogram[mid][j]) {
				histogram[max][i] = histogram[mid][j];
			}
			if (histogram[min][i] <= histogram[mid][j]) {
				break;
			}
			if (histogram[max][i] <= histogram[mid][j]) {
				break;
			}
		}
	}
	for (int i = 0; i < 256; i++) {
		printf("%d  %d %d %d %d \n", i, histogram[0][i], histogram[1][i], histogram[2][i], histogram[3][i]);
	}
	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			if (I[y*m_iWidth + x] <= 0) {
				setPixel(x, y, 0, 0, 0);
				continue;
			}
			if (I[y*m_iWidth + x] >= 1) {
				setPixel(x, y, 255, 255, 255);
				continue;
			}
			if (H[y*m_iWidth + x] < 0)
				H[y*m_iWidth + x] += 360;
			if (H[y*m_iWidth + x] <= 120) {
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dB = (1 - S[y*m_iWidth + x]) / 3;
				dR = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dG = 1 - dR - dB;
			}
			else if (H[y*m_iWidth + x]>120 && H[y*m_iWidth + x] <= 240) {
				H[y*m_iWidth + x] = H[y*m_iWidth + x] - 120;
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dR = (1 - S[y*m_iWidth + x]) / 3;
				dG = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dB = 1 - dR - dG;
			}
			else {
				H[y*m_iWidth + x] = H[y*m_iWidth + x] - 240;
				angle1 = H[y*m_iWidth + x] * 0.017453293;
				angle2 = (60 - H[y*m_iWidth + x])*0.017453293;
				dG = (1 - S[y*m_iWidth + x]) / 3;
				dB = (1 + (S[y*m_iWidth + x] * cos(angle1) / cos(angle2))) / 3;
				dR = 1 - dG - dB;
			}
			dR = dR * 255 * 3 * I[y*m_iWidth + x];
			dG = dG * 255 * 3 * I[y*m_iWidth + x];
			dB = dB * 255 * 3 * I[y*m_iWidth + x];
			if (dR > 255)dR = 255;
			if (dG > 255)dG = 255;
			if (dB > 255)dB = 255;
			if (dR < 0)dR = 0;
			if (dG < 0)dG = 0;
			if (dB < 0)dB = 0;
			R = (unsigned char)dR; G = (unsigned char)dG; B = (unsigned char)dB;
			setPixel(x, y, R, G, B);
		}
	}
}
void ImageProc::quantization(int step)
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			for (int i = 0; i < 255 / step; i++) {
				if (step * i <= R && R < step * (i + 1)) {
					R = step * i;
				}
				if (step * i <= G && G < step * (i + 1)) {
					G = step * i;
				}
				if (step * i <= B && B < step * (i + 1)) {
					B = step * i;
				}
			}

			setPixel(x, y, R, G, B);
		}
	}
}

void ImageProc::Kuwahara() {
	int x, y, count = 0;
	double vr = 0, vg = 0, vb = 0, sumr = 0, sumg = 0, sumb = 0, vrr = 0, vgg = 0, vbb = 0, minr = 987654321, ming = 987654321, minb = 987654321, anwr, anwg, anwb;
	byte R, G, B;
	byte *temp = new byte[m_iHeight*m_iWidth * 3];
	for (y = 2; y < m_iHeight - 2; y++)
	{
		for (x = 2; x < m_iWidth - 2; x++)
		{
			minr = 98765432; ming = 98765432; minb = 98765432;
			for (int q = 0; q < 2; q++)
			{
				for (int w = 0; w < 2; w++)
				{
					sumr = 0; sumg = 0; sumb = 0;
					vr = 0; vg = 0; vb = 0;
					count = 0;
					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							getPixel(x - 2 + l + q * 2, y - 2 + k + w * 2, R, G, B);

							vr += R * R; vg += G * G; vb += B * B;
							sumr += R; sumg += G; sumb += B;
							count++;
						}
					}

					vrr = (double)(vr / count) - ((double)(sumr / count)*(double)(sumr / count));
					vgg = (double)(vg / count) - ((double)(sumg / count)*(double)(sumg / count));
					vbb = (double)(vb / count) - ((double)(sumb / count)*(double)(sumb / count));
					if (vrr < minr) {
						minr = vrr;
						anwr = sumr / count;
					}
					if (vgg < ming) {
						ming = vgg;
						anwg = sumg / count;
					}
					if (vbb < minb) {
						minb = vbb;
						anwb = sumb / count;
					}
				}
			}
			anwr = xClip(anwr);
			anwg = xClip(anwg);
			anwb = xClip(anwb);
			temp[getAddr(x, y) + 0] = anwr;
			temp[getAddr(x, y) + 1] = anwg;
			temp[getAddr(x, y) + 2] = anwb;
		}
	}
	m_pRGB = temp;
}