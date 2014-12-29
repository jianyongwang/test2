#include <cv.h>
#include <highgui.h>
#include "cornerHarris.h"
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("..\\..\\church01.jpg", CV_LOAD_IMAGE_GRAYSCALE);

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