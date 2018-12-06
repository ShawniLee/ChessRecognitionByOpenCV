#include "Դ.h"


void on_trackbar(int alpha_slider, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	resize(src1, src1, Size(src1.cols / (alpha_slider+1), src1.rows / (alpha_slider + 1)), (0, 0), (0, 0), 3);
	imshow("��Ч��ͼ��֮һ", src1);
}
//void Harris_trackBar(int, void* userdata) {
//	Harris temp = *(Harris*)userdata;
//	DetectedHarris(&temp.srcImage, &temp.DstImage,threshold1);
//	imshow(temp.Name, temp.DstImage);
//}
bool cmp(Point x, Point y)
{
	return x.y < y.y;
}

void DetectedHarris(Mat* srcImage, Mat* DstImage,int blocksize,int ksize)
{
	const int thresh = 100;
	Mat grayImage,HarrisImage,normImage,scaledImage;
	cvtColor(*srcImage, grayImage, CV_BGR2GRAY);
	cornerHarris(grayImage, HarrisImage, blocksize, ksize, 0.05, BORDER_DEFAULT);
	// ��һ����ת��  
	normalize(HarrisImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//����һ�����ͼ���Ա任��8λ�޷�������     
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			//Mat::at<float>(j,i)��ȡ����ֵ��������ֵ�Ƚ�
			if ((int)normImage.at<float>(j, i) > thresh)
			{
				po.insert(Point(i, j));
			}
		}
	}
	scaledImage.copyTo(*DstImage);
}
void ShowWindows(Mat srcImage,String Name)
{
	namedWindow(Name, 0);
	resizeWindow(Name, srcImage.cols / 2, srcImage.rows / 2);
	imshow(Name, srcImage);
}

void inRange_trackBar(int, void* userdata) {
	Harris temp = *(Harris*)userdata;
	inRange(temp.srcImage, Scalar(threshold1, threshold2, threshold3), hsvYelloHigh, temp.DstImage);
	ShowWindows(temp.DstImage, "abc");
}

//************************************
// Method:    deleteSameChessPos
// @brief:  �ж�������ʵ�ǵ�λ��
// @Param: int samePosDistance������ʵ�ǵ���/samePosDistance�����������ظ���
// @Param: set�洢ʵ�ʽǵ�����
//************************************

void deleteSameChessPos(int samePosDistance,Mat *srcImage)
{
	Point upperLeftPoint, lowerRightPoint;
	int xStep = (*srcImage).size().width / CuttingScale;
	int yStep = (*srcImage).size().height / CuttingScale;
	int count = 0, sumRange = po.size() / 20;//������ΧΪ�����ܱ�SUM/20�����Ƿ�ӽ�
	set<Point, MyLess>::iterator deletetemp;
	set<Point, MyLess>::iterator i, j;
	for (i = po.begin();; )
	{
		upperLeftPoint.x = i->x - samePosDistance;//���Ͻ�λ��
		upperLeftPoint.y = i->y - samePosDistance;
		lowerRightPoint.x = i->x + samePosDistance;//���½ǵ�λ��
		lowerRightPoint.y = i->y + samePosDistance;
		//ȥ����Ч��
		//if (!cuttingRangeResult[upperLeftPoint.x/ xStep][upperLeftPoint.y/yStep])
		//	i=temp.erase(i);
		//else
		//ȥ��
		Rect detectRange(upperLeftPoint, lowerRightPoint);//�������
		count = 0;
		for (j = i, ++j; count<sumRange;)
		{
			if (j == po.end())
				break;
			if (j->inside(detectRange))
			{
				j = po.erase(j);

			}
			else
			{
				++j;
				++count;
			}
		}
		++i;
		if (i == po.end())
		{
			break;
		}
	}
}

//************************************
// Method:    CalcCustomVariance
// @brief:  ��WeiGrid+5�������޳��������ƽ��ֵ�ĵ�o=-09 
// @Param: ������ĵ�����
//************************************

//void CalcCustomVariance(Point temp[WeiGrid + 5])//position=false X   position=true Y   
//{
//	float Average, Variance = 0,min=std::numeric_limits<float>::max(),index=0;
//	int sum[WeiGrid + 5] = { 0 }, Var[WeiGrid + 5] = { 0 };
//	Point Ytemp[WeiGrid + 5];
//	for (int i = 0; i < WeiGrid + 5; i++)
//	{
//		Ytemp[i] = temp[WeiGrid + 5];
//	}
//	for (int i = 0; i < WeiGrid; i++)//����Ѿ��������б�ĩβ��û���㹻�ĵ�ɹ���ѡ�ˣ�ֱ�ӷ���
//	{
//		if(Ytemp[i].x==0 || Ytemp[i].y==0)
//			return;
//	}
//	//��Y�󷽲�
//	{	
//		sort(Ytemp[0], Ytemp[WeiGrid + 4], cmp);
//		for (int i = 1; i < WeiGrid + 5; i++)
//		{
//			sum[i] = sum[i - 1] + Ytemp[i].y;
//			Var[i] = Var[i - 1] + Ytemp[i].y * Ytemp[i].y;
//		}
//		for (int i = WeiGrid; i <= WeiGrid+5; i++) {
//			double tmp = (Var[i] - Var[i - WeiGrid]) - 1.0 * (sum[i] - sum[i - WeiGrid]) * (sum[i] - sum[i - WeiGrid]) / WeiGrid;
//			if (tmp < min) {
//				min = tmp;
//				index = i;
//			}
//			for (int i = 0; i < WeiGrid+5; i++)
//			{
//
//			}
//		}
//
//	}
//
//}

//void CalcVariance() {
//	float XVariance, YVariance;
//	for (set<Point, MyLess>::iterator i = po.begin(); i != po.end(); i++)
//	{
//		int count = 0;
//		Point temp[WeiGrid+5];
//		for (set<Point, MyLess>::iterator j = i; count < WeiGrid+5; count++, j++)
//		{
//			if (j == po.end())
//			{
//				break;
//			}
//			temp[count] = *j;
//		}
//
//		//��X�󷽲�
//		{
//			for (int i = 0; i < WeiGrid; i++)
//			{
//				sum += temp[i].x;//���X�Ĳ����̶ȣ�X������ͬ
//			}
//			Average = sum / (float)WeiGrid;
//			for (int i = 0; i < WeiGrid; i++)
//			{
//				Variance += pow((temp[i].x - Average), 2);
//			}
//		}
//	}
//}

void DrawHarris(Mat* srcImage) {
	for (set<Point, MyLess>::iterator i = po.begin(); i != po.end(); i++)
	{
		circle(*srcImage, *i, 5, Scalar(255, 255, 255), 2, 8, 0);
	}
}

//************************************
// Method:    deleteUnLocatedChessPos
// @brief:  ɾ�����������ϵĽǵ�
// @Param: �ǵ���Χ����distance
// @Param: set�洢ʵ�ʽǵ�����
// @Param: output�洢λ��
//************************************
void deleteUnLocatedChessPos(Mat* inputImage,Mat * outputImage,int distance, set<Point, MyLess>  & temp)
{
	inRange(*inputImage, hsvYellowLow, hsvYelloHigh, *outputImage);
	ShowWindows(*outputImage, "temp");
	Mat HsvImage;
	set<Point, MyLess>::iterator i;
	for (i = temp.begin(); i != temp.end(); i++)
	{
		Mat roi = HsvImage(Rect(i->x - distance, i->y - distance, i->x + distance, i->y + distance));
		
		//TODO��ͳ������Image�ĺ�ɫ��������������ֵ������Ϊ�õ������������еĵ㣬����ɾ��
	}
}

int main()
{
	//����ԭʼͼ   
	Mat srcImage = imread("0010.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
	Mat  dstImage1, dstImage2,HarrisImage;//��ʱ������Ŀ��ͼ�Ķ���
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5)); //��ȡ�Զ����
	//ת��Ϊ�Ҷ�ͼ��ƽ���˲�
	cvtColor(srcImage, dstImage1, COLOR_BGR2GRAY);
	//blur(srcImage, srcImage, Size(3, 3));
	//�������
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	dstImage1 = dstImage1 > 100;//��������
	findContours(dstImage1, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//��������ͼ
	dstImage2 = Mat::zeros(dstImage1.size(), CV_8UC3);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		Scalar color = Scalar(255,255,255);
		drawContours(dstImage2, contours, i, color, LINE_4, 8, hierarchy);
	}

	morphologyEx(dstImage2, dstImage2, MORPH_ERODE, element);
	DetectedHarris(&dstImage2, &HarrisImage);
	deleteSameChessPos(15, &HarrisImage);
	//CalcVariance();
	//set<Point, MyLess>::iterator temp = po.begin();
	//for (int i=0;i<po.size(); i++)
	//{
	//	cout << *temp;
	//	++temp;
	//	if (i%19==0)
	//	{
	//		cout << endl;
	//	}
	//}
	DrawHarris(&srcImage);
	//Harris temp2;
	//temp2.DstImage = dstImage2;
	//temp2.srcImage = srcImage;
	ShowWindows(srcImage, "abc");
	//createTrackbar("H", "abc", &threshold1, 255, inRange_trackBar, &temp2);
	//createTrackbar("S", "abc", &threshold2, 255, inRange_trackBar, &temp2);
	//createTrackbar("B", "abc", &threshold3, 255, inRange_trackBar, &temp2);


	////ѡ����Ч��ɫ�ǵ�
	//int xStep = srcImage.size().width / CuttingScale;
	//int yStep = srcImage.size().height / CuttingScale;
	//for (int i = 0; i < CuttingScale; i++)
	//{
	//	for (int j = 0; j < CuttingScale; j++)
	//	{
	//		Mat roi = srcImage(Rect(0 + xStep * i, 0 + yStep * j, xStep, yStep)),resultMean,resultStddev;
	//		meanStdDev(roi, resultMean, resultStddev);
	//		if (resultMean.at<double>(0, 0) > 75)
	//		{
	//			cuttingRangeResult[i][j] = true; 
	//		}
	//	}
	//}
	waitKey();
	return 0;
}
