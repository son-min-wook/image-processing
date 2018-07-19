#include <iostream>
#include <opencv2\highgui.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat img = imread("input.jpg");
	if (img.empty()) {
		cout << "Error : image cannot be loaded..!!" << endl;
		return -1;
	}
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", img);
	waitKey(0);
	destroyWindow("MyWindow");
	return 0;
}
