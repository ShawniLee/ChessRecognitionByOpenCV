//-----------------------------------【头文件包含部分】---------------------------------------
//		描述：包含程序所依赖的头文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

//-----------------------------------【命名空间声明部分】---------------------------------------
//		描述：包含程序所使用的命名空间
//----------------------------------------------------------------------------------------------- 
using namespace cv;

//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
void on_trackbar(int alpha_slider, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	resize(src1, src1, Size(src1.cols / (alpha_slider+1), src1.rows / (alpha_slider + 1)), (0, 0), (0, 0), 3);
	imshow("【效果图】之一", src1);
}
int main()
{
	//载入原始图   
	Mat srcImage = imread("0010.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	Mat  dstImage1, dstImage2;//临时变量和目标图的定义
	//转换为灰度图并平滑滤波
	cvtColor(srcImage, dstImage1, COLOR_BGR2GRAY);
	//blur(srcImage, srcImage, Size(3, 3));
	//定义变量
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	dstImage1 = dstImage1 > 100;
	namedWindow("dstImage1", 0);
	resizeWindow("dstImage1", dstImage1.cols / 2, dstImage1.rows / 2);
	imshow("dstImage1", dstImage1);
	findContours(dstImage1, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//绘制轮廓图
	dstImage2 = Mat::zeros(dstImage1.size(), CV_8UC3);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
		drawContours(dstImage2, contours, i, color, LINE_4, 8, hierarchy);
	}

	

	namedWindow("轮廓图",0);
	resizeWindow("轮廓图",dstImage2.cols /2, dstImage2.rows /2);
	imshow("轮廓图", dstImage2);
	waitKey();
	return 0;
}