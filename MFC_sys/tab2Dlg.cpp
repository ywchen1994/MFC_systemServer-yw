// tab2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "tab2Dlg.h"
#include "afxdialogex.h"


// tab2Dlg 對話方塊

IMPLEMENT_DYNAMIC(tab2Dlg, CDialogEx)

tab2Dlg::tab2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_tab2, pParent)
	, m_map_Xpos(0)
	, m_map_Ypos(0)
	, m_ipText(_T("192.168.1.213:88"))
{

}
// 設定變換[之前]與[之後]的坐標 (左上,左下,右下,右上)
cv::Point2f gPts1[4] = { cv::Point2f(29, 0), cv::Point2f(0, 230), cv::Point2f(320, 240), cv::Point2f(305, 5) };
cv::Point2f gPts2[4] = { cv::Point2f(0, 0), cv::Point2f(0, 240), cv::Point2f(320, 240), cv::Point2f(320, 0) };
tab2Dlg::~tab2Dlg()
{
}

void tab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AXISMEDIACONTROL1, m_AMC);
	DDX_Control(pDX, IDC_IMAGE_IPcam, m_img_IPcam);
	DDX_Control(pDX, IDC_CHECK_IPcam_keystone, m_check_IPcam_keystone);
	DDX_Text(pDX, IDC_EDIT_map_Xpos, m_map_Xpos);
	DDX_Text(pDX, IDC_EDIT_map_Ypos, m_map_Ypos);
	DDX_Control(pDX, IDC_IMAGE_IPcam_map, m_img_IPcam_map);
	DDX_Text(pDX, IDC_EDIT_IPcamIP, m_ipText);
}


BEGIN_MESSAGE_MAP(tab2Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_connect_P3DX, &tab2Dlg::OnBnClickedButtonconnectP3dx)
	ON_BN_CLICKED(IDC_BUTTON_connectIPcam, &tab2Dlg::OnBnClickedButtonconnectipcam)
END_MESSAGE_MAP()

IplImage* tab2Dlg::sImage_IPcam = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
IplImage* tab2Dlg::sImage_IPcam_ground = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
// tab2Dlg 訊息處理常式
void tab2Dlg::OnBnClickedButtonconnectP3dx()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Aria::init();
	robot.lock();
	con.setPort("10.0.126.12", 8101);

	if (!con.openSimple())
	{
		("Open failed.");
		Aria::shutdown();
	}
	robot.setDeviceConnection(&con);
	if (!robot.blockingConnect())
	{
		printf("Could not connect to robot... exiting\n");
		Aria::shutdown();
	}
	robot.enableMotors();
	robot.disableSonar();		                 // Disables the sonar.
	robot.requestEncoderPackets();// Starts a continuous stream of encoder packets.

	robot.runAsync(true);
	robot.unlock();
}


void tab2Dlg::OnBnClickedButtonconnectipcam()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	try
	{
		this->UpdateData(true);
		//m_ipText = _T("169.254.179.228");//ip
		//m_ipText = _T("192.168.1.213:88");//ip
		mediaURL = (CString)"http://" + m_ipText + (CString)"/axis-cgi/mjpg/video.cgi";
		ctrlURL = (CString)"http://" + m_ipText + (CString)"/axis-cgi/com/ptz.cgi";
		//ctrlURL.Format(_T("http://%s/axis-cgi/com/ptz.cgi"), m_ipText);
		//mediaURL.Format(_T("http://%s/axis-cgi/mjpg/video.cgi"), m_ipText);
		m_user = "root";
		m_pass = "pass";
		m_AMC.Stop();
		m_AMC.put_MediaUsername(m_user);
		m_AMC.put_MediaPassword(m_pass);
		m_AMC.put_PTZControlURL(ctrlURL);
		m_AMC.put_MediaURL(mediaURL);
		m_AMC.put_StretchToFit(true);
		m_AMC.Play();
	}
	catch (COleDispatchException *e)
	{
		MessageBox(e->m_strDescription);
	}
	Sleep(2000);
}
