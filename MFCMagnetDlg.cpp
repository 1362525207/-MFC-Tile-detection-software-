
// MFCMagnetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCMagnet.h"
#include "MFCMagnetDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const cv::Size ptSize(300, 200);//点的尺寸
const int  off_boder = 100;//边界距离
const cv::Size RSize(78, 52);//实际尺寸


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
 
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMagnetDlg 对话框



CMFCMagnetDlg::CMFCMagnetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCMAGNET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMagnetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCMagnetDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_IMAGE, &CMFCMagnetDlg::OnBnClickedBtnOpenImage)
	ON_BN_CLICKED(IDC_BTN_GRAY, &CMFCMagnetDlg::OnBnClickedBtnGray)
	ON_BN_CLICKED(IDC_BTN_CONCAST, &CMFCMagnetDlg::OnBnClickedBtnConcast)
	ON_BN_CLICKED(IDC_BTN_THRESHOD, &CMFCMagnetDlg::OnBnClickedBtnThreshod)
	ON_BN_CLICKED(IDC_BTN_DETECT, &CMFCMagnetDlg::OnBnClickedBtnDetect)
	ON_BN_CLICKED(IDC_BTN_OPEN_IMAGE6, &CMFCMagnetDlg::OnBnClickedBtnOpenImage6)
	ON_BN_CLICKED(IDC_BTN_THRESHOD2, &CMFCMagnetDlg::OnBnClickedBtnThreshod2)
	ON_BN_CLICKED(IDC_BTN_DETECT_MANAGE, &CMFCMagnetDlg::OnBnClickedBtnDetectManage)
	ON_BN_CLICKED(IDC_zhifangtu, &CMFCMagnetDlg::OnBnClickedzhifangtu)
	ON_BN_CLICKED(IDC_BTN_DETECT_MANAGE3, &CMFCMagnetDlg::OnBnClickedBtnDetectManage3)
END_MESSAGE_MAP()


// CMFCMagnetDlg 消息处理程序

BOOL CMFCMagnetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCMagnetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCMagnetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCMagnetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/// <summary>
/// 显示画图
/// </summary>
/// <param name="m_cvImg"></param>
/// <param name="ID"></param>
void CMFCMagnetDlg::DrawcvMat(const cv::Mat &m_cvImg, UINT ID)
{
	cv::Mat img;
	CRect rect;

	GetDlgItem(ID)->GetClientRect(&rect);

	if (rect.Width() % 4 != 0)
	{
		ScreenToClient(rect);
		rect.SetRect(rect.left, rect.top,
			rect.left + (rect.Width() + 3) / 4 * 4, rect.bottom);  //调整图像宽度为4的倍数

		GetDlgItem(ID)->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOMOVE);
	}

	cv::Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	cv::resize(m_cvImg, img, cv::Size(rect.Width(), rect.Height()));  //使图像适应控件大小 

	unsigned int m_buffer[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
	BITMAPINFO* m_bmi = (BITMAPINFO*)m_buffer;
	BITMAPINFOHEADER* m_bmih = &(m_bmi->bmiHeader);
	memset(m_bmih, 0, sizeof(*m_bmih));
	m_bmih->biSize = sizeof(BITMAPINFOHEADER);
	m_bmih->biWidth = img.cols; 
	m_bmih->biHeight = -img.rows; //在自下而上的位图中 高度为负
	m_bmih->biPlanes = 1;
	m_bmih->biCompression = BI_RGB;
	m_bmih->biBitCount = 8 * img.channels();

	if (img.channels() == 1) 
	{
		for (int i = 0; i < 256; i++)
		{
			m_bmi->bmiColors[i].rgbBlue = i;
			m_bmi->bmiColors[i].rgbGreen = i;
			m_bmi->bmiColors[i].rgbRed = i;
			m_bmi->bmiColors[i].rgbReserved = 0;
		}
	}

	CDC *pDC = GetDlgItem(ID)->GetDC();
	::StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, rect.Width(), rect.Height(), img.data, (BITMAPINFO*)m_bmi, DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(pDC);
}
void CMFCMagnetDlg::OnBnClickedBtnOpenImage()
{
	// TODO: 打开图片

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"All Files(*.jpg;*.bmp;*.png*)|**.jpg;*.bmp;*.png*||", NULL);
	CString strPath;
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
	}
	if (strPath.GetLength() == 0)
	{
		return;
	}
	std::string strFileName = strPath;
	srcImg = imread(strFileName);
	cv::resize(srcImg, srcImg, Size(), 0.3, 0.3);

	DrawcvMat(srcImg, IDC_STATIC_SHOW);
}

void CMFCMagnetDlg::OnBnClickedBtnGray()
{
	//  灰度化
	grayImg = MyDeal::getGray(srcImg);
	DrawcvMat(grayImg, IDC_STATIC_SHOW);
}
void CMFCMagnetDlg::OnBnClickedzhifangtu()
{
	MatND dstHist;//得到的直方图     
	int dims = 1;//得到的直方图的维数 灰度图的维数为1
	float hranges[2] = { 0, 255 };	//直方图统计的灰度值范围
	const float *ranges[1] = { hranges };   // 这里需要为const类型，二维数组用来指出每个区间的范围  
	int bin = 256;//直方图横坐标的区间数 即横坐标被分成多少份
	int channels = 0;//图像得通道 灰度图的通道数为0
	/* 计算图像的直方图 */
	calcHist(&grayImg, 1/*输入图像个数*/, &channels, Mat()/*掩码*/, dstHist, dims, &bin, ranges);
	int height = 150;	//直方图高度
	int scale = 3;	//垂直缩放比
	int horvizon_scale = 3;	//水平缩放比
	//获取最大值和最小值  
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0); //找到直方图中的最大值和最小值 
	int shift_vertical = 10;//直方图偏移值,偏移用于显示水平坐标
	int shift_horvizon = 40;//直方图偏移值,偏移用于显示垂直坐标
	//绘制出直方图  
	Mat dstImage(height*scale, bin*horvizon_scale + shift_horvizon, CV_8UC3, Scalar(255, 255, 255));//创建一个彩色三通道矩阵,大小a*b,填充0
	int hpt = saturate_cast<int>((dstImage.rows - shift_vertical)*0.95); //最大值对应的Y坐标,防止溢出
	for (int i = 0; i < bin; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*horvizon_scale + shift_horvizon, dstImage.rows - 1 - shift_vertical), Point((i + 1)*horvizon_scale + shift_horvizon - 1, dstImage.rows - realValue - shift_vertical), Scalar(0, 0, 255), 1, 8, 0);
	}
	//绘制垂直刻度
	char string[100];
	CvFont font;
	double font_size = 0.8;//字体大小
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1, 1, 0, 1, 8);//字体结构初始化 
	Size text_size;
	for (int i = hpt; i >= 0;)
	{
		_itoa(maxValue*i / hpt, string, 10);//把一个整数转换为字符串  
		//在图像中显示文本字符串  
		text_size = getTextSize(string, CV_FONT_HERSHEY_PLAIN, font_size, 1, NULL);	//获得字体大小
		putText(dstImage, string, cvPoint(0, dstImage.rows - i - shift_vertical + text_size.height / 2), cv::FONT_HERSHEY_PLAIN, font_size, Scalar(0, 0, 0), 1, 8, 0);
		i -= hpt / 8;	//只显示8个刻度
	}
	copyMakeBorder(dstImage, dstImage, 1, 1, 1, 10, BORDER_CONSTANT, Scalar::all(255));
	//刻画水平刻度
	for (int i = bin - 1; i >= 0;)
	{
		_itoa(i, string, 10);//把一个整数转换为字符串  
		//在图像中显示文本字符串  
		text_size = getTextSize(string, CV_FONT_HERSHEY_PLAIN, font_size, 1, NULL);	//获得字体大小
		putText(dstImage, string, cvPoint(i*horvizon_scale + shift_horvizon - text_size.width / 2, dstImage.rows - 2), cv::FONT_HERSHEY_PLAIN, font_size, Scalar(0, 0, 0), 1, 8, 0);
		i -= bin / 20;	//只显示10个刻度
	}
	// 显示直方图
	DrawcvMat(dstImage, IDC_STATIC_SHOW);
}
void CMFCMagnetDlg::OnBnClickedBtnConcast()
{
	//中值滤波
	int ww = 5;
	Mat blurMat;
	cv::medianBlur(grayImg, blurMat, ww);
	//	对比度调整
	MyDeal::adjustBrightnessContrast(blurMat, curImg, -100, 30);
	DrawcvMat(curImg, IDC_STATIC_SHOW);
}
void CMFCMagnetDlg::OnBnClickedBtnThreshod()
{
	//	二值化
	threshold(curImg, thImg, 30, 255, 1);
	//闭操作
	thImg = MyDeal::ImgClose(thImg,11);
	DrawcvMat(thImg, IDC_STATIC_SHOW);
}

void CMFCMagnetDlg::OnBnClickedBtnDetect()
{
	// TODO: 标志物检测

	vector<vector<Point>> countous = MyDeal::getBwImgCountours(thImg);

	ptend.clear();

	Mat temp = srcImg.clone();
	for (int i = countous.size() - 1; i > 0; i--)
	{
		if (contourArea(countous[i]) < 15)
		{
			continue;
		}
		cv::drawContours(temp, countous, i, Scalar(0, 0, 255), 2);
		//计算轮廓矩
		Moments mu = moments(countous[i], false);

		ptend.push_back(Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00));
		if (ptend.size() == 4)
		{
			break;
		}
	}
	//点排序
	ptend = MyDeal::sortPoints(ptend);
	for (int i = 0; i < 4; i++)
	{
		cv::line(temp, ptend[i], ptend[(i + 1) % 4], Scalar(0, 255, 0), 2);
	}
	DrawcvMat(temp, IDC_STATIC_SHOW);
}


void CMFCMagnetDlg::OnBnClickedBtnOpenImage6()
{
	// TODO: 校正

	vector<Point2f> ptendDstF(4);
	//定义4个标准点的位置
	ptendDstF[0] = Point2f(off_boder, off_boder);
	ptendDstF[1] = Point2f(off_boder + ptSize.width, off_boder);
	ptendDstF[2] = Point2f(off_boder + ptSize.width, off_boder + ptSize.height);
	ptendDstF[3] = Point2f(off_boder, off_boder + ptSize.height);
	MyDeal::getTransmitImg(grayImg, ptend, ptendDstF, revImg);
	DrawcvMat(revImg, IDC_STATIC_SHOW);
}


void CMFCMagnetDlg::OnBnClickedBtnThreshod2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnGray();
	OnBnClickedBtnConcast();
	OnBnClickedBtnThreshod();
	OnBnClickedBtnDetect();
	OnBnClickedBtnOpenImage6();

// 	int ww = 5;
// 	Mat blurMat;
// 	cv::GaussianBlur(revImg, blurMat, cv::Size(ww, ww), 
// 		0.3*(ww / 2 - 1) + .8);
// //	对比度调整
// 	MyDeal::adjustBrightnessContrast(blurMat, curImg, -20, 80);

	int  ostuThreshold = MyDeal::OTSU(revImg);
	cv::Mat otsuResultImage = cv::Mat::zeros(revImg.rows, revImg.cols, CV_8UC1);
	threshold(revImg, thImg, ostuThreshold, 255, 1);//OTSU

	DrawcvMat(thImg, IDC_STATIC_SHOW);
}

string myToString(const float &v)
{
	char chCode[20];
	sprintf(chCode, "%.2f", v);  // .2 是控制输出精度的，两位小数
	string strCode(chCode);
	return strCode;
}

void CMFCMagnetDlg::OnBnClickedBtnDetectManage()
{
	// TODO: 检测
	vector<vector<Point>>  countours=MyDeal::getBwImgCountours(thImg);
	vector<Rect> rects;
	vector<Point2f> centers;
	vector<float> radiuss;
	for (int i = 0; i <countours.size(); i++)
	{
		if (contourArea(countours[i]) < 2000)//面积  去除小轮廓
		{
			break;
		}
		Point2f center; float radius;
		//最小闭合圆
		cv::minEnclosingCircle(countours[i], center, radius);
		centers.push_back(center);
		radiuss.push_back(radius);
		rects.push_back(boundingRect(countours[i]));
	}
	Mat temp;
	cvtColor(revImg, temp, COLOR_GRAY2BGR);
	//获取空洞
	Mat emptyImg;
	MyDeal::emptyHole(thImg, emptyImg);

	float w = RSize.width*1.0 / ptSize.width;
	float h = RSize.height*1.0 / ptSize.height;
	float rate = w;
	
	
	for (int i = 0; i <centers.size(); i++)
	{
		//计算空洞面积比
		float  s=cv::countNonZero(emptyImg(rects[i]))*1.0/ rects[i].area();
		
		
		Scalar color(0, 255, 0);
		if(s>0.04)//比过滤
		{
			color = Scalar(0, 0, 255);//红色
		}
		float v = radiuss[i] * rate;
		string str="out:"+myToString(v)+"mm";
		float v2 = (radiuss[i]-5) * rate;
		string str2 = "in:" + myToString(v2) + "mm";
		
		cv::circle(temp, centers[i], radiuss[i], color, 2);
		cv::circle(temp, centers[i], 2, color, -1);
		cv::putText(temp, str, centers[i],FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 2);

		cv::putText(temp, str2 ,Point(centers[i].x, centers[i].y-20), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 0), 2);
	}
	DrawcvMat(temp, IDC_STATIC_SHOW);

	
}

void CMFCMagnetDlg::OnBnClickedBtnDetectManage3()
{
	vector<vector<Point>>  countours = MyDeal::getBwImgCountours(thImg);
	vector<Rect> rects;
	vector<Point2f> centers;
	vector<float> radiuss;
	for (int i = 0; i <countours.size(); i++)
	{
		if (contourArea(countours[i]) < 2000)//面积  去除小轮廓
		{
			break;
		}
		Point2f center; float radius;
		//最小闭合圆
		cv::minEnclosingCircle(countours[i], center, radius);
		centers.push_back(center);
		radiuss.push_back(radius);
		rects.push_back(boundingRect(countours[i]));
	}
	Mat temp;
	cvtColor(revImg, temp, COLOR_GRAY2BGR);
	//获取空洞
	Mat emptyImg;
	MyDeal::emptyHole(thImg, emptyImg);
	float w = RSize.width*1.0 / ptSize.width;
	float h = RSize.height*1.0 / ptSize.height;
	float rate = (w+h)/2;
	Mat onemage;
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
	morphologyEx(emptyImg, onemage, MORPH_CLOSE, element1, Point(-1, -1), 1, BORDER_CONSTANT, Scalar::all(0));
	int edgeThresh = 60;
	// canny检测
	Canny(onemage, onemage, edgeThresh, edgeThresh * 3, 3);
	vector<vector<Point>> countours1;
	Mat tempMat2 = onemage.clone();
	findContours(tempMat2, countours1, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	sort(countours1.begin(), countours1.end(), [](const vector<Point> &pts1, const vector<Point> &pts2)
	{
		return contourArea(pts1) > contourArea(pts2);
	});
	vector<Point2f> centers1;
	vector<float> radiuss1;
	for (int i = 0; i <countours1.size(); i++)
	{
		if (contourArea(countours1[i]) < 50 || contourArea(countours1[i]) > 500)//面积  去除小轮廓
		{
			break;
		}
		Point2f center1; float radius1;
		//最小闭合圆
		cv::minEnclosingCircle(countours1[i], center1, radius1);
		centers1.push_back(center1);
		radiuss1.push_back(radius1);
	}
	for (int i = 0; i <centers1.size(); i++)
	{
		Scalar color(0, 255, 0);
		if (radiuss1[i] >10)
		{
			continue;
		}
		float v = radiuss1[i] * rate;
		string str = "out:" + myToString(v) + "mm" ;
		cv::circle(temp, centers1[i], radiuss1[i], color, 2);
		cv::putText(temp, str, Point(centers1[i].x, centers1[i].y + 20), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 2);
	}
	for (int i = 0; i <centers.size(); i++)
	{
		//计算空洞面积比
		float  s = cv::countNonZero(emptyImg(rects[i]))*1.0 / rects[i].area();

		Scalar color(0, 255, 0);
		if (s>0.04)//比过滤
		{
			color = Scalar(0, 0, 255);//红色
		}
		float v = radiuss[i] * rate;
		string str = "out:" + myToString(v) + "mm";
		float v2 = (radiuss[i] - 5) * rate;
		string str2 = "in:" + myToString(v2) + "mm";

		cv::circle(temp, centers[i], radiuss[i], color, 2);
		cv::circle(temp, centers[i], 2, color, -1);
		cv::putText(temp, str, centers[i], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 2);
		cv::putText(temp, str2, Point(centers[i].x, centers[i].y - 20), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 0), 2);
	}
	DrawcvMat(temp, IDC_STATIC_SHOW);
}
