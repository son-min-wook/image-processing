#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
using namespace std;
using namespace cv;
int main(int argc, const char** argv) {
	VideoCapture cap("C:\Users\a.avi");
	if (!cap.isOpened()) {
		cout << "Cannot open the video file" << endl;
		return -1;
	}
	//cap.set(CV_CAP_PROP_POS_MSEC,300);
	double fps = cap.get(CV_CAP_PROP_FPS);
	cout << "Frame per seconds : " << fps << endl;
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
	while (1) {
		Mat frame;
		bool bSuccess = cap.read(frame);
		if (!bSuccess) {
			cout << "cannot read the frame from video file " << endl;
			break;
		}
		imshow("MyVdeo", frame);
		if (waitKey(30) == 27) {
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}
	return 0;
}
