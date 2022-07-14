
// MFCMagnetDlg.h : 头文件
//

#pragma once
#include "MyDeal.h"

// CMFCMagnetDlg 对话框
class CMFCMagnetDlg : public CDialog
{
// 构造
public:
	CMFCMagnetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCming_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
void DrawcvMat(const cv::Mat &cvImg, UINT ID);
DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenImage();
	afx_msg void OnBnClickedBtnGray();
	afx_msg void OnBnClickedBtnConcast();
	afx_msg void OnBnClickedBtnThreshod();
	afx_msg void OnBnClickedBtnDetect();
	afx_msg void OnBnClickedBtnOpenImage6();



private:
	Mat srcImg;//原图
	Mat grayImg;//灰度图
	Mat thImg;//二值化图
	Mat curImg;//当前图片
	vector<Point2f> ptend;//端点

	Mat revImg;//校正图
public:
	afx_msg void OnBnClickedBtnThreshod2();
	afx_msg void OnBnClickedBtnDetectManage();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedzhifangtu();
	afx_msg void OnBnClickedBtnDetectManage3();
};
