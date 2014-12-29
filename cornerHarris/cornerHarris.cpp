#include <cv.h>
#include <highgui.h>
#include "cornerHarris.h"
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("..\\..\\church01.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	/*Mat cornerStrength;
	cornerHarris(image, cornerStrength, 3, 3, 0.01);
	Mat harrisCorner;
	Mat harrisCorner1;
	double threshod = 0.0001;
	cv::threshold(cornerStrength, harrisCorner, threshod, 255, cv::THRESH_BINARY);
	cv::threshold(harrisCorner, harrisCorner1, 30, 255, cv::THRESH_BINARY_INV);*/
	HarrisDetector harris;
	harris.detect(image);
	vector<Point> ptrs;
	harris.getCorners(ptrs, 0.01);
	harris.drawOnImage(image, ptrs);
	imshow("result", image);
	waitKey(0);
	system("pause");
	return 0;
}