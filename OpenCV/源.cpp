//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//		����������������������ͷ�ļ�
//---------------------------------------------------------------------------------------------- 
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

//-----------------------------------�������ռ��������֡�---------------------------------------
//		����������������ʹ�õ������ռ�
//----------------------------------------------------------------------------------------------- 
using namespace cv;

//-----------------------------------��main( )������--------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-----------------------------------------------------------------------------------------------
void on_trackbar(int alpha_slider, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	resize(src1, src1, Size(src1.cols / (alpha_slider+1), src1.rows / (alpha_slider + 1)), (0, 0), (0, 0), 3);
	imshow("��Ч��ͼ��֮һ", src1);
}
int main()
{
	//����ԭʼͼ   
	Mat srcImage = imread("0010.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
	Mat  dstImage1, dstImage2;//��ʱ������Ŀ��ͼ�Ķ���
	//ת��Ϊ�Ҷ�ͼ��ƽ���˲�
	cvtColor(srcImage, dstImage1, COLOR_BGR2GRAY);
	//blur(srcImage, srcImage, Size(3, 3));
	//�������
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	dstImage1 = dstImage1 > 100;
	namedWindow("dstImage1", 0);
	resizeWindow("dstImage1", dstImage1.cols / 2, dstImage1.rows / 2);
	imshow("dstImage1", dstImage1);
	findContours(dstImage1, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//��������ͼ
	dstImage2 = Mat::zeros(dstImage1.size(), CV_8UC3);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
		drawContours(dstImage2, contours, i, color, LINE_4, 8, hierarchy);
	}

	

	namedWindow("����ͼ",0);
	resizeWindow("����ͼ",dstImage2.cols /2, dstImage2.rows /2);
	imshow("����ͼ", dstImage2);
	waitKey();
	return 0;
}