
// MFCMagnetDlg.h : ͷ�ļ�
//

#pragma once
#include "MyDeal.h"

// CMFCMagnetDlg �Ի���
class CMFCMagnetDlg : public CDialog
{
// ����
public:
	CMFCMagnetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCming_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	Mat srcImg;//ԭͼ
	Mat grayImg;//�Ҷ�ͼ
	Mat thImg;//��ֵ��ͼ
	Mat curImg;//��ǰͼƬ
	vector<Point2f> ptend;//�˵�

	Mat revImg;//У��ͼ
public:
	afx_msg void OnBnClickedBtnThreshod2();
	afx_msg void OnBnClickedBtnDetectManage();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedzhifangtu();
	afx_msg void OnBnClickedBtnDetectManage3();
};
