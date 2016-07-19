// tab1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "tab1Dlg.h"
#include "afxdialogex.h"


// tab1Dlg 對話方塊

IMPLEMENT_DYNAMIC(tab1Dlg, CDialogEx)

tab1Dlg::tab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_tab1, pParent)
	, m_totalObjNum(0)
{

}

tab1Dlg::~tab1Dlg()
{
}

void tab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_objList, m_combo_objList);
}


BEGIN_MESSAGE_MAP(tab1Dlg, CDialogEx)
END_MESSAGE_MAP()


// tab1Dlg 訊息處理常式
