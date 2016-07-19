
// MFC_sysDlg.h : ���Y��
//

#pragma once
#include"Cvvimage.h"
#include"..//Kinect2Capture//Kinect2Capture.h"
#include"..//CamShiftPatch//CamShiftPatch.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "tab1Dlg.h"
#include "tab2Dlg.h"
#include "tab3Dlg.h"
#include "setROIDlg.h"

struct CMythreadParam
{
public:
	HWND hWnd;
	LPVOID m_lpPara;
	UINT   m_case;
	BOOL m_blthreading;
};

// CMFC_sysDlg ��ܤ��
class CMFC_sysDlg : public CDialogEx
{
// �غc
public:
	CMFC_sysDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_SYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// tab control
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	tab1Dlg m_TabPage1;
	tab2Dlg m_TabPage2;
	tab3Dlg m_TabPage3;


	CStatic m_image_binPickLive;
	CStatic m_img_binPickLiveDepth;
	CListBox m_list_server;
	CString m_detectObjNum;

	
};
