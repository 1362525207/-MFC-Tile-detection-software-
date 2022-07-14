#pragma once
#include <opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
class MyDeal
{
public:
	MyDeal();
	//	MyTrack atr;


	
	static Mat getGray(const Mat& src);
	//开运算
	static Mat ImgOpen(const Mat& src, int size_w);
	static int adjustBrightnessContrast(InputArray src, OutputArray dst, int brightness, int contrast);

	//闭运算
	//闭运算
	static Mat ImgClose(const Mat& src, int size_w);
	static int MyDeal::OTSU(Mat srcImage);
	//空洞获取
	static void emptyHole(const Mat srcimage, Mat& dstimage);



	static vector<Point> getMaxBwImgRect(const Mat& src);
	static vector<vector<Point> > getBwImgCountours(const Mat& src);


	/// <summary>
	/// 点排序
	/// </summary>
	/// <param name="pts">The PTS.</param>
	/// <returns>std.vector.Point2f</returns>
	static vector<Point2f> sortPoints(const vector<Point2f>& _ptEnd);

	/// <summary>
	/// 数据格式转换
	/// </summary>
	/// <param name="src">The source.</param>
	/// <param name="dst">The DST.</param>
	template <class SrcType, class DstType>
	static void convertVec(const std::vector<SrcType>& src, std::vector<DstType>& dst) {
		dst.resize(src.size());
		std::copy(src.begin(), src.end(), dst.begin());
	}
	
	static void getTransmitImg(const Mat& src, const std::vector<Point2f>& vertices, const std::vector<Point2f> dst_pt,Mat& dst);
};

