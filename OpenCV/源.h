#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

void DetectedHarris(Mat* srcImage, Mat* DstImage, int blocksize = 7, int ksize = 3);
struct Harris
{
	Mat srcImage;
	Mat DstImage;
	String Name;
};
struct MyLess
{
	template<typename _Tp>
	//bool operator () (const Point_<_Tp>& pt1, const Point_<_Tp> & pt2) const
	//{
	//	return (pt1.x*pt1.x + pt1.y*pt1.y)<(pt2.x*pt2.x + pt2.y*pt2.y);
	//}
	bool operator () (const Point_<_Tp>& pt1, const Point_<_Tp> & pt2) const
	{
		if (pt1.x!=pt2.x)
		{
			return pt1.x < pt2.x;
		}
		else
		{
			return pt1.y < pt2.y;
		}

	}
};
struct Line
{
	Point point[19];
};
#define CuttingScale 40
#define WeiGrid 19//Î§ÆåÆåÅÌÍø¸ñ
#define WuZiGrid 15//Îå×ÓÆåÆåÅÌÍø¸ñ
const Scalar hsvYellowLow(0, 0, 120);
const Scalar hsvYelloHigh(255, 255, 255);
int threshold1 = 26, threshold2 = 43,threshold3=46;
set<Point, MyLess> po;
bool cuttingRangeResult[CuttingScale][CuttingScale] = { 0 };//0 black 1 white