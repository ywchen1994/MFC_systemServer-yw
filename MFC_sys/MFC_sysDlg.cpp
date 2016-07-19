
// MFC_sysDlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "MFC_sysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define IMG_WIDTH 320
#define IMG_HIGHT 240

// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_sysDlg ��ܤ��



CMFC_sysDlg::CMFC_sysDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_SYS_DIALOG, pParent)
	, m_detectObjNum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_sysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_binPickLive, m_image_binPickLive);
	DDX_Control(pDX, IDC_IMAGE_binPickLiveDepth, m_img_binPickLiveDepth);
	DDX_Control(pDX, IDC_LIST_server, m_list_server);
	DDX_Text(pDX, IDC_EDIT_detectObjNum, m_detectObjNum);
	DDX_Control(pDX, IDC_TAB2, m_Tab);
}

BEGIN_MESSAGE_MAP(CMFC_sysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CMFC_sysDlg::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CMFC_sysDlg �T���B�z�`��

BOOL CMFC_sysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	GetDlgItem(IDC_EDIT_scara_X)->SetWindowText(L"550");/*�]�w���u��l��m*/
	GetDlgItem(IDC_EDIT_scara_Y)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT_scara_Z)->SetWindowText(L"150");
	GetDlgItem(IDC_EDIT_scara_T)->SetWindowText(L"0");

	m_Tab.InsertItem(0, _T("�f�~���"));/*�������ҦW��*/
	m_Tab.InsertItem(1, _T("�B��"));
	m_Tab.InsertItem(2, _T("�]�w"));

	m_TabPage1.Create(IDD_DIALOG_tab1, &m_Tab);
	m_TabPage2.Create(IDD_DIALOG_tab2, &m_Tab);
	m_TabPage3.Create(IDD_DIALOG_tab3, &m_Tab);

	//�]�wtab control ���Ĥ@���b�}�l�ɯॿ�T���
	CRect rTab, rItem;
	m_Tab.GetItemRect(0, &rItem);
	m_Tab.GetClientRect(&rTab);
	int x = rItem.left;
	int y = rItem.bottom + 1;
	int cx = rTab.right - rItem.left - 3;
	int cy = rTab.bottom - y - 2;
	m_TabPage3.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabPage2.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabPage1.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
	//**************************************************************************//
	CRect winRect;
	m_image_binPickLive.GetWindowRect(&winRect);
	m_image_binPickLive.SetWindowPos(NULL, 30, 30, 320, 240, SWP_SHOWWINDOW);
	//m_img_binPickLiveDepth.GetWindowRect(&winRect);
	m_img_binPickLiveDepth.SetWindowPos(NULL, 30 + 320, 30, 320, 240, SWP_SHOWWINDOW);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CMFC_sysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMFC_sysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMFC_sysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_sysDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CRect rTab, rItem;
	m_Tab.GetItemRect(0, &rItem);
	m_Tab.GetClientRect(&rTab);
	int x = rItem.left;
	int y = rItem.bottom + 1;
	int cx = rTab.right - rItem.left - 3;
	int cy = rTab.bottom - y - 2;
	int tab = m_Tab.GetCurSel();

	m_TabPage1.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabPage2.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
	m_TabPage3.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);

	switch (tab)
	{
	case 0:
		m_TabPage1.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	case 1:
		m_TabPage2.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	case 2:
		m_TabPage3.SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);
		break;
	}

	*pResult = 0;
}
