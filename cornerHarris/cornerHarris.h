#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;
class HarrisDetector
{
public:
	HarrisDetector() :neighbourhood(3), aperture(3), k(0.01), maxStrength(0.0), threshold(0.01), nonMaxSize(3){
	}
	void setLocalMaxWindowSize(int nonMaxSize1){
		nonMaxSize = nonMaxSize1;
	}
	void detect(const Mat &image);
	Mat getCornerMap(double qualityLevel);
	void getCorners(vector<Point> &points, double qualityLevel);
	void getCorners(vector<Point>&points, const Mat &cornerMap);
	void drawOnImage(Mat &image, const vector<Point> & points, Scalar color, int radius);

private:
	Mat cornerStrength;//表示角点强度的32为浮点图像
	Mat cornerTh;//阈值化后角点的32为浮点图像
	Mat localMax;//局部极大值图像（内部
	int neighbourhood;//导数平滑的相邻像素的尺寸
	int aperture;//梯度计算的孔径大小
	double k;//Harris参数
	double maxStrength;//阈值计算的最大强度
	double threshold;//计算得到的阈值（内部
	int nonMaxSize;//非极大值抑制的相邻像素的尺寸
	Mat kernel;
};
void HarrisDetector::detect(const Mat &image)
{
	cornerHarris(image, cornerStrength, neighbourhood, aperture, k);
	double minStrength;
	minMaxLoc(cornerStrength, &minStrength, &maxStrength);
	Mat dilated;
	compare(cornerStrength, dilated, localMax, cv::CMP_EQ);
}
Mat HarrisDetector::getCornerMap(double qualityLevel)
{
	Mat cornerMap;
	//对角图像进行阈值化
	threshold = qualityLevel*maxStrength;
	cv::threshold(cornerStrength, cornerTh, threshold, 255, cv::THRESH_BINARY);
	//转换为8为图像
	cornerTh.convertTo(cornerMap, CV_8U);
	//非极大值抑制
	bitwise_and(cornerMap, localMax, cornerMap);
	return cornerMap;
}
void HarrisDetector::getCorners(vector<Point> &points, double qualityLevel)
{
	Mat cornerMap = getCornerMap(qualityLevel);
	getCorners(points, cornerMap);
}
void HarrisDetector::getCorners(vector<Point>&points, const Mat &cornerMap)
{
	for (int i = 0; i < cornerMap.rows; i++)
	{
		const uchar*rowPtr = cornerMap.ptr<uchar>(i);
		for (int  j = 0; j < cornerMap.cols; j++)
		{
			if (rowPtr[j])
				points.push_back(Point(i, j));
		}
	}
}
void HarrisDetector::drawOnImage(Mat &image, const vector<Point> & points, 
	Scalar color = Scalar(255, 255, 255), int radius=3)
{
	vector<Point>::const_iterator it = points.begin();
	while (it!=points.end())
	{
		circle(image, *it, radius, color);
		it++;
	}
}