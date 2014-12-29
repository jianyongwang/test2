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
	Mat cornerStrength;//��ʾ�ǵ�ǿ�ȵ�32Ϊ����ͼ��
	Mat cornerTh;//��ֵ����ǵ��32Ϊ����ͼ��
	Mat localMax;//�ֲ�����ֵͼ���ڲ�
	int neighbourhood;//����ƽ�����������صĳߴ�
	int aperture;//�ݶȼ���Ŀ׾���С
	double k;//Harris����
	double maxStrength;//��ֵ��������ǿ��
	double threshold;//����õ�����ֵ���ڲ�
	int nonMaxSize;//�Ǽ���ֵ���Ƶ��������صĳߴ�
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
	//�Խ�ͼ�������ֵ��
	threshold = qualityLevel*maxStrength;
	cv::threshold(cornerStrength, cornerTh, threshold, 255, cv::THRESH_BINARY);
	//ת��Ϊ8Ϊͼ��
	cornerTh.convertTo(cornerMap, CV_8U);
	//�Ǽ���ֵ����
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