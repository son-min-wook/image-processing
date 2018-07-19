#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
using namespace std;
using namespace cv;
int main(int argc, const char** argv) {
	Mat img = imread("MyPic.jpg", CV_LOAD_IMAGE_COLOR);
	if (img.empty()) {
		cout << "Error : image cannot be loaded..!!" << endl;
		return -1;
	}
	Mat imgH = img + Scalar(75, 75, 75);
	//img.convertTo(imgH,-1,1,75);
	Mat imgL = img + Scalar(-75, -75, -75);
	//img.convertTo(imgL,-1,1,-75);
	Mat imgG, imgM, imgB;
	GaussianBlur(img, imgG, Size(15, 15), 0, 0);
	medianBlur(img, imgM, 3);
	bilateralFilter(img, imgB, 1, 1, 1, BORDER_DEFAULT);
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("High Brightness", CV_WINDOW_AUTOSIZE);
	namedWindow("Low Brightness", CV_WINDOW_AUTOSIZE);
	namedWindow("Gaussian Blur", CV_WINDOW_AUTOSIZE);
	namedWindow("Median Blur", CV_WINDOW_AUTOSIZE);
	namedWindow("Bilateral Filter", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", img);
	imshow("High Brightness", imgH);
	imshow("Low Brightness", imgL);
	imshow("Gaussian Blur", imgG);
	imshow("Median Blur", imgM);
	imshow("Bilateral Filter", imgB);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
