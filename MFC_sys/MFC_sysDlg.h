
// MFC_sysDlg.h : 標頭檔
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

// CMFC_sysDlg 對話方塊
class CMFC_sysDlg : public CDialogEx
{
// 建構
public:
	CMFC_sysDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_SYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
