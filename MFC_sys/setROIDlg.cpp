// setROIDlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "setROIDlg.h"
#include "afxdialogex.h"


// setROIDlg ��ܤ��

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


// setROIDlg �T���B�z�`��
BOOL setROIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �b���[�J�B�~����l�]�w
	m_img_RGB.SetWindowPos(NULL, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
	pointNum = 0;

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}
