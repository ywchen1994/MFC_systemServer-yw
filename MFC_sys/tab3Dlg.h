#pragma once
#include "afxwin.h"
#include "tab1Dlg.h"

// tab3Dlg ��ܤ��

class tab3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(tab3Dlg)

public:
	tab3Dlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~tab3Dlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_tab3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	tab1Dlg m_TabPage1;
	void ShowImage(IplImage *Image, CWnd *pWnd, int channels);

	CStatic m_img_keystone;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	bool FLAG_liveStart;

	int m_Xpos;
	int m_Ypos;

	int m_G_Xpos;
	int m_G_Ypos;

	int m_A_Xpos;
	int m_A_Ypos;

	int m_Ac_Xpos;
	int m_Ac_Ypos;

	
	int m_globleZeroOnArm_x;
	int m_globleZeroOnArm_y;

	int m_globleZeroOnImg_x;
	int m_globleZeroOnImg_y;

	float m_cam2globle_x;
	float m_cam2globle_y;
	
	
	
};
