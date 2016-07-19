#pragma once
#include "afxwin.h"


// tab1Dlg 對話方塊

class tab1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(tab1Dlg)

public:
	tab1Dlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~tab1Dlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_tab1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	int m_totalObjNum;
	CComboBox m_combo_objList;
};
