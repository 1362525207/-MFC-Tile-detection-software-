#include "MyDeal.h"
const cv::Size ptSize(300,220);//点的尺寸
const int  off_boder=120;//边界距离
MyDeal::MyDeal()
{

}

Mat MyDeal::getGray(const Mat& src)
{
	Mat gray;
	if (src.channels() == 1)
		gray = src.clone();
	else
	{
		//cvtColor(src, gray, COLOR_BGR2GRAY);普通灰度化，也可以用
		Mat hsv;
		cvtColor(src, hsv, COLOR_BGR2HSV);
		extractChannel(hsv, gray, 2);
	}
	return gray;
}

int MyDeal::OTSU(Mat srcImage)
{
	int nCols = srcImage.cols;
	int nRows = srcImage.rows;
	int threshold = 0;
	//init the parameters
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}

	//统计灰度集中每个像素在整幅图像中的个数
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			nSumPix[(int)srcImage.at<uchar>(i, j)]++;
		}
	}

	//计算每个灰度级占图像中的概率分布
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
	}

	//遍历灰度级【0，255】，计算出最大类间方差下的阈值

	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 0; i < 256; i++)
	{
		//初始化相关参数
		w0 = w1 = u0 = u1 = u0_temp = u1_temp = delta_temp = 0;
		for (int j = 0; j < 256; j++)
		{
			//背景部分
			if (j <= i)
			{
				w0 += nProDis[j];
				u0_temp += j*nProDis[j];
			}
			//前景部分
			else
			{
				w1 += nProDis[j];
				u1_temp += j*nProDis[j];
			}
		}
		//计算两个分类的平均灰度
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		//依次找到最大类间方差下的阈值
		delta_temp = (float)(w0*w1*pow((u0 - u1), 2)); //前景与背景之间的方差(类间方差)
		if (delta_temp > delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}
	return threshold;
}

Mat MyDeal::ImgOpen(const Mat& src, int size_w)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size_w, size_w));

	Mat open_mat;
	morphologyEx(src, open_mat, MORPH_OPEN, element, Point(-1, -1));
	return open_mat;
}

int MyDeal::adjustBrightnessContrast(InputArray src, OutputArray dst, int brightness, int contrast)
{
	auto clip_rang = [](int value, int minV, int maxV)
		{
			return (value) > (maxV) ? (maxV) : (((value) < (minV)) ? (minV) : (value));
		};

	auto color_rang = [](int value)
		{
			return (value) > (255) ? (255) : (((value) < (0)) ? (0) : (value));
		};


	Mat input = src.getMat();
	if (input.empty()) {
		return -1;
	}

	dst.create(src.size(), src.type());
	Mat output = dst.getMat();

	brightness = clip_rang(brightness, -255, 255);
	contrast = clip_rang(contrast, -255, 255);

	/**
	Algorithm of Brightness Contrast transformation
	The formula is:
	y = [x - 127.5 * (1 - B)] * k + 127.5 * (1 + B);
	x is the input pixel value
	y is the output pixel value
	B is brightness, value range is [-1,1]
	k is used to adjust contrast
	k = tan( (45 + 44 * c) / 180 * PI );
	c is contrast, value range is [-1,1]
	*/

	double B = brightness / 255.;
	double c = contrast / 255.;
	double k = tan((45 + 44 * c) / 180 * CV_PI);

	Mat lookupTable(1, 256, CV_8U);
	uchar *p = lookupTable.data;
	for (int i = 0; i < 256; i++)
		p[i] = color_rang((i - 127.5 * (1 - B)) * k + 127.5 * (1 + B));

	LUT(input, lookupTable, output);

	return 0;
}

Mat MyDeal::ImgClose(const Mat& src, int size_w)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size_w, size_w));

	Mat colosrMat;

	morphologyEx(src, colosrMat, MORPH_CLOSE, element, Point(-1, -1), 1, BORDER_CONSTANT, Scalar::all(0));
	return colosrMat;
}

void MyDeal::emptyHole(const Mat srcimage, Mat& dstimage)
{
	Size m_Size = srcimage.size();
	Mat temimage;
	cv::copyMakeBorder(srcimage, temimage, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(0));
	floodFill(temimage, Point(0, 0), Scalar(255));//洪水填充
	Rect rect(1, 1, m_Size.width, m_Size.height);
	dstimage = (~temimage(rect));//去反
}

vector<Point> MyDeal::getMaxBwImgRect(const Mat& src)
{
	vector<vector<Point>> countous= getBwImgCountours(src);
	if (countous.size() == 0)
		return vector<Point>();

	return countous[0];

}

/// <summary>
/// 获取二进制轮廓
/// </summary>
/// <param name="src">The source.</param>
/// <returns>轮廓.</returns>
vector<vector<Point> > MyDeal::getBwImgCountours(const Mat& src)
{
	vector<vector<Point>> countous;
	Mat tempMat = src.clone();
	findContours(tempMat, countous, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if (countous.size() == 0)
		return countous;
	sort(countous.begin(), countous.end(), [](const vector<Point> &pts1, const vector<Point> &pts2)
	{
		return contourArea(pts1) > contourArea(pts2);
	});
	return countous;
}

vector<Point2f> MyDeal::sortPoints(const vector<Point2f>& _ptEnd)
{
	Rect rect = cv::boundingRect(_ptEnd);
	//	vector<Point >hull;
	//排序
	vector<Point2f> ptEnd;
	convexHull(_ptEnd, ptEnd);//凸包算法
	int minId = 0;
	double minDist = DBL_MAX;
	Point2f br(rect.br().x, rect.br().y);
	for (int i = 0; i < 4; i++)
	{
		double d2 = norm(ptEnd[(i + 2) % 4] - br);
		double d = norm(ptEnd[i]) + d2;

		if (d < minDist)
		{
			minDist = d;
			minId = i;
		}
	}
	vector<Point2f> hull(4);
	for (int i = 0; i < 4; i++)
	{
		hull[i] = ptEnd[(i + minId) % 4];
	}

	return hull;
}



void MyDeal::getTransmitImg(const Mat& src, const std::vector<Point2f>& verticesF, const std::vector<Point2f> dst_ptF,
                            Mat& dst)
{
	
	Rect rect = boundingRect(dst_ptF);//计算下范围
	rect.width += off_boder*2;
	rect.height += off_boder*2;//范围扩充

	Mat transmtx1 = getPerspectiveTransform(verticesF, dst_ptF); //仿射矩阵计算
	cv::warpPerspective(src, dst, transmtx1, rect.size(),
		INTER_LINEAR,
		BORDER_CONSTANT,
		Scalar::all(255)); //仿射
}





