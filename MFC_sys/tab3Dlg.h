#pragma once
#include "afxwin.h"


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

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_img_keystone;
	int m_G_Xpos;
};
