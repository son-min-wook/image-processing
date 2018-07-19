#include <opencv2\highgui\highgui.hpp>
using namespace cv;
int main() {
	Mat img(500, 1000, CV_8UC3, Scalar(0, 0, 100));
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", img);
	waitKey(0);
	destroyWindow("MyWindow");
	return 0;
}
