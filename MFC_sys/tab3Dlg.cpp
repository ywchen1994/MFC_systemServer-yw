// tab3Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "tab3Dlg.h"
#include "afxdialogex.h"


// tab3Dlg 對話方塊

IMPLEMENT_DYNAMIC(tab3Dlg, CDialogEx)

tab3Dlg::tab3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_tab3, pParent)
	, m_G_Xpos(0)
{

}

tab3Dlg::~tab3Dlg()
{
}

void tab3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_keystone, m_img_keystone);
	DDX_Text(pDX, IDC_STATIC_G_Xpos, m_G_Xpos);
}


BEGIN_MESSAGE_MAP(tab3Dlg, CDialogEx)
END_MESSAGE_MAP()


// tab3Dlg 訊息處理常式
