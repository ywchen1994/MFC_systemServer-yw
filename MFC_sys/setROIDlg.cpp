// setROIDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "setROIDlg.h"
#include "afxdialogex.h"


// setROIDlg 對話方塊

IMPLEMENT_DYNAMIC(setROIDlg, CDialogEx)

setROIDlg::setROIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_setROI, pParent)
{

}

setROIDlg::~setROIDlg()
{
}

void setROIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_RGB, m_img_RGB);
}


BEGIN_MESSAGE_MAP(setROIDlg, CDialogEx)
END_MESSAGE_MAP()


// setROIDlg 訊息處理常式
BOOL setROIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此加入額外的初始設定
	m_img_RGB.SetWindowPos(NULL, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
	pointNum = 0;

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}
