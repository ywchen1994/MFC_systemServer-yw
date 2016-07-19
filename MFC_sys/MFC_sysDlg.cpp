
// MFC_sysDlg.cpp : 實作檔
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

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMFC_sysDlg 對話方塊



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


// CMFC_sysDlg 訊息處理常式

BOOL CMFC_sysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	GetDlgItem(IDC_EDIT_scara_X)->SetWindowText(L"550");/*設定手臂初始位置*/
	GetDlgItem(IDC_EDIT_scara_Y)->SetWindowText(L"0");
	GetDlgItem(IDC_EDIT_scara_Z)->SetWindowText(L"150");
	GetDlgItem(IDC_EDIT_scara_T)->SetWindowText(L"0");

	m_Tab.InsertItem(0, _T("貨品選擇"));/*給予標籤名稱*/
	m_Tab.InsertItem(1, _T("運輸"));
	m_Tab.InsertItem(2, _T("設定"));

	m_TabPage1.Create(IDD_DIALOG_tab1, &m_Tab);
	m_TabPage2.Create(IDD_DIALOG_tab2, &m_Tab);
	m_TabPage3.Create(IDD_DIALOG_tab3, &m_Tab);

	//設定tab control 的第一頁在開始時能正確顯示
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
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFC_sysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC_sysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_sysDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此加入控制項告知處理常式程式碼
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
