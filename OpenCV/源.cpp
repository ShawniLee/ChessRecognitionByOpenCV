#include "源.h"


void on_trackbar(int alpha_slider, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	resize(src1, src1, Size(src1.cols / (alpha_slider+1), src1.rows / (alpha_slider + 1)), (0, 0), (0, 0), 3);
	imshow("【效果图】之一", src1);
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
	// 归一化与转换  
	normalize(HarrisImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型     
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			//Mat::at<float>(j,i)获取像素值，并与阈值比较
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
// @brief:  判断棋盘真实角点位置
// @Param: int samePosDistance，两真实角点间距/samePosDistance，用来消除重复点
// @Param: set存储实际角点容器
//************************************

void deleteSameChessPos(int samePosDistance,Mat *srcImage)
{
	Point upperLeftPoint, lowerRightPoint;
	int xStep = (*srcImage).size().width / CuttingScale;
	int yStep = (*srcImage).size().height / CuttingScale;
	int count = 0, sumRange = po.size() / 20;//遍历范围为该子周边SUM/20个点是否接近
	set<Point, MyLess>::iterator deletetemp;
	set<Point, MyLess>::iterator i, j;
	for (i = po.begin();; )
	{
		upperLeftPoint.x = i->x - samePosDistance;//左上角位置
		upperLeftPoint.y = i->y - samePosDistance;
		lowerRightPoint.x = i->x + samePosDistance;//右下角点位置
		lowerRightPoint.y = i->y + samePosDistance;
		//去除无效点
		//if (!cuttingRangeResult[upperLeftPoint.x/ xStep][upperLeftPoint.y/yStep])
		//	i=temp.erase(i);
		//else
		//去重
		Rect detectRange(upperLeftPoint, lowerRightPoint);//检测区域
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
// @brief:  从WeiGrid+5个点中剔除方差大于平均值的点o=-09 
// @Param: 待处理的点数组
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
//	for (int i = 0; i < WeiGrid; i++)//如果已经到达了列表末尾，没有足够的点可供挑选了，直接返回
//	{
//		if(Ytemp[i].x==0 || Ytemp[i].y==0)
//			return;
//	}
//	//对Y求方差
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
//		//对X求方差
//		{
//			for (int i = 0; i < WeiGrid; i++)
//			{
//				sum += temp[i].x;//检测X的波动程度，X尽量相同
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
// @brief:  删除不在棋盘上的角点
// @Param: 角点周围距离distance
// @Param: set存储实际角点容器
// @Param: output存储位置
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
		
		//TODO：统计生成Image的黑色？数量，超过阈值，则认为该点是棋盘区域中的点，否则删除
	}
}

int main()
{
	//载入原始图   
	Mat srcImage = imread("0010.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	Mat  dstImage1, dstImage2,HarrisImage;//临时变量和目标图的定义
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5)); //获取自定义核
	//转换为灰度图并平滑滤波
	cvtColor(srcImage, dstImage1, COLOR_BGR2GRAY);
	//blur(srcImage, srcImage, Size(3, 3));
	//定义变量
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	dstImage1 = dstImage1 > 100;//增大亮度
	findContours(dstImage1, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//绘制轮廓图
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


	////选出有效白色角点
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
