// tab1Dlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "tab1Dlg.h"
#include "afxdialogex.h"


// tab1Dlg ��ܤ��

IMPLEMENT_DYNAMIC(tab1Dlg, CDialogEx)

tab1Dlg::tab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_tab1, pParent)
	, m_totalObjNum(0)
	, m_gripCenterX(0)
	, m_gripCenterY(0)
	, m_gripDegree(0)
{

}

tab1Dlg::~tab1Dlg()
{
}

void tab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_objList, m_combo_objList);
	DDX_Text(pDX, IDC_EDIT_gripCenterY, m_gripCenterY);
	DDX_Text(pDX, IDC_EDIT_gripDegree, m_gripDegree);
}


BEGIN_MESSAGE_MAP(tab1Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_getHisAndSet, &tab1Dlg::OnBnClickedButtongethisandset)
	ON_CBN_SELCHANGE(IDC_COMBO_objList, &tab1Dlg::OnCbnSelchangeComboobjlist)
	ON_BN_CLICKED(IDC_BUTTON_viewObj, &tab1Dlg::OnBnClickedButtonviewobj)
	ON_BN_CLICKED(IDC_BUTTON_detectObj, &tab1Dlg::OnBnClickedButtondetectobj)
END_MESSAGE_MAP()


// tab1Dlg �T���B�z�`��


void tab1Dlg::OnBnClickedButtongethisandset()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}


void tab1Dlg::OnCbnSelchangeComboobjlist()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}


void tab1Dlg::OnBnClickedButtonviewobj()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}


void tab1Dlg::OnBnClickedButtondetectobj()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}
