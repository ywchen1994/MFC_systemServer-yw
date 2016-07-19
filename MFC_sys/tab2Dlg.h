#pragma once
#include "axismediacontrol1.h"
#include "afxwin.h"
#include "Aria.h"
#include"Cvvimage.h"
// tab2Dlg ��ܤ��
struct CTab2threadParam
{
public:
	HWND hWnd;
	LPVOID m_lpPara;
	UINT   m_case;
	BOOL m_blthreading;
};
class tab2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(tab2Dlg)

public:
	tab2Dlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~tab2Dlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_tab2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	//P3DX
	ArTcpConnection con;
	ArRobot robot;
	ArTime start;

	CAxismediacontrol1 m_AMC;
	CStatic m_img_IPcam;
	CButton m_check_IPcam_keystone;

	int m_map_Xpos;
	int m_map_Ypos;

	CStatic m_img_IPcam_map;
	CString m_ipText;

	afx_msg void OnBnClickedButtonconnectP3dx();
	afx_msg void OnBnClickedButtonconnectipcam();

	static IplImage* sImage_IPcam;
	static IplImage* sImage_IPcam_ground;

	// IPcam ip
	CString m_ipText;
	CString	m_user;
	CString	m_pass;
	CString ctrlURL;
	CString mediaURL;
	unsigned char *PTZImage;
};
