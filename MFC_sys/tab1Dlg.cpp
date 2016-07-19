// tab1Dlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_sys.h"
#include "tab1Dlg.h"
#include "afxdialogex.h"


// tab1Dlg ��ܤ��

#define IMG_WIDTH 320
#define IMG_HIGHT 240

IMPLEMENT_DYNAMIC(tab1Dlg, CDialogEx)
IplImage *tab1Dlg::sImage_live = cvCreateImage(cvSize(IMG_WIDTH, IMG_HIGHT), IPL_DEPTH_8U, 4);
IplImage *tab1Dlg::sImage_depth = cvCreateImage(cvSize(IMG_WIDTH, IMG_HIGHT), IPL_DEPTH_8U, 1);
IplImage *tab1Dlg::sImage_depthGround = cvCreateImage(cvSize(IMG_WIDTH, IMG_HIGHT), IPL_DEPTH_8U, 1);

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
	DDX_Control(pDX, IDC_IMAGE_viewObj, m_img_viewObj);
	DDX_Control(pDX, IDC_IMAGE_detectObj, m_img_detectObj);
}


BEGIN_MESSAGE_MAP(tab1Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_getHisAndSet, &tab1Dlg::OnBnClickedButtongethisandset)
	ON_CBN_SELCHANGE(IDC_COMBO_objList, &tab1Dlg::OnCbnSelchangeComboobjlist)
	ON_BN_CLICKED(IDC_BUTTON_viewObj, &tab1Dlg::OnBnClickedButtonviewobj)
	ON_BN_CLICKED(IDC_BUTTON_detectObj, &tab1Dlg::OnBnClickedButtondetectobj)
END_MESSAGE_MAP()


// tab1Dlg �T���B�z�`��
CvRect tab1Dlg::findCase(IplImage* image)
{
	CvScalar pixel;
	CvPoint MaxP = cvPoint(0, 0);
	CvPoint MinP = cvPoint(320, 240);

	for (int i = 0; i < image->width; i++)
	{
		for (int j = 0; j < image->height; j++)
		{
			pixel = cvGet2D(image, j, i);
			if (pixel.val[0] > 1)
			{
				if (j < MinP.y)
					MinP.y = j;
				if (j > MaxP.y)
					MaxP.y = j;
				if (i < MinP.x)
					MinP.x = i;
				if (i > MaxP.x)
					MaxP.x = i;
			}
		}
	}
	CvRect theCase;
	theCase.x = MinP.x;
	theCase.y = MinP.y;
	theCase.width = MaxP.x - MinP.x;
	theCase.height = MaxP.y - MinP.y;
	return theCase;
}
void tab1Dlg::ShowImage(IplImage *Image, CWnd *pWnd)
{
	CDC	*dc = pWnd->GetWindowDC();
	IplImage *Temp = NULL;

	Temp = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
	cvResize(Image, Temp, CV_INTER_LINEAR);

	CvvImage Temp2;
	Temp2.CopyOf(Temp);
	Temp2.Show(*dc, 0, 0, Temp->width, Temp->height);
	cvReleaseImage(&Temp);
	ReleaseDC(dc);
}
float angle(CvPoint p1, CvPoint p2)
{
	float angle_temp;
	float xx, yy;

	xx = p2.x - p1.x;
	yy = p2.y - p1.y;

	if (xx == 0.0)
		angle_temp = 180 / 2.0;
	else
		angle_temp = atan(fabs(yy / xx)) * 180 / 3.141592;


	if ((xx < 0.0) && (yy >= 0.0))
		angle_temp = 270 - angle_temp;
	else if ((xx < 0.0) && (yy < 0.0))
		angle_temp = 270 + angle_temp;
	else if ((xx >= 0.0) && (yy < 0.0))
		angle_temp = 90 - angle_temp;
	else if ((xx > 0.0) && (yy > 0.0))
		angle_temp = 90 + angle_temp;
	return (angle_temp);
}




void tab1Dlg::OnCbnSelchangeComboobjlist()
{
	//comboobox��ܮɩҵo�ͪ��Ʊ�
	int select = m_combo_objList.GetCurSel();

	char path[100];
	sprintf_s(path, "objectHis/colorMaskData%d.png", select);
	ShowImage(cvLoadImage(path, 3), GetDlgItem(IDC_IMAGE_viewObj));
}


void tab1Dlg::OnBnClickedButtongethisandset()
{
	//1.�NRGB�Pdepth�ϰ��B�z�åB�নhis(OK)
	//2.��his�Ϧs��bojectHis����Ƨ���(OK)
	//3.���Ʈw�u��ƪ��Ѽ�+1

	//1. Ū��**********
	IplImage* pImg_live = nullptr;
	if (sImage_live->nChannels == 3)
	{
		pImg_live = cvCloneImage(sImage_live);
	}
	else if (sImage_live->nChannels == 4)
	{
		pImg_live = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
		cvCvtColor(sImage_live, pImg_live, CV_BGRA2BGR);
	}
	else { MessageBox(L"pImg_live Channels error"); }

	IplImage* pImg_depth = nullptr;
	if (sImage_depth->nChannels == 3)
	{
		pImg_depth = cvCloneImage(sImage_depth);
	}
	if (sImage_depth->nChannels == 1)
	{
		pImg_depth = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
		cvCvtColor(sImage_depth, pImg_depth, CV_GRAY2BGR);
	}
	else { MessageBox(L"pImg_depth Channels error"); }

	//2.����β`�׷�B�n���m��v��(colorMask)**********
	IplImage* pImg_colorMask = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
	cvAnd(pImg_depth, pImg_live, pImg_colorMask);//(ch3,ch3,ch3)

												 //3.�নhis**********
												 //3-1.��ROI
	CvRect selection;
	selection = findCase(pImg_depth);

	CvPoint MaxPoint = cvPoint(selection.x + selection.width, selection.y + selection.height);
	CvPoint MinPoint = cvPoint(selection.x, selection.y);
	//cvRectangle(pImg_depth, MaxPoint, MinPoint, cvScalar(255, 255, 0), 3);
	//cvShowImage("Depth Mask ROI", pImg_setDepth);

	//3-2.���o��m����(hisImgData)
	CSpatch_inTab1.setImage(pImg_colorMask);

	IplImage* hisImgData = CSpatch_inTab1.drawHistImg(selection, maskRange);


	//3-3.�x�s��m���� �P colorMask�ϵ�viewObj��
	char path[100];
	sprintf_s(path, "objectHis/hisImgData%d.png", m_totalObjNum);
	cvSaveImage(path, hisImgData);
	hisData[m_totalObjNum] = CSpatch_inTab1.histogram;

	sprintf_s(path, "objectHis/colorMaskData%d.png", m_totalObjNum);
	cvSaveImage(path, pImg_colorMask);

	//4.����**********
	//4-1.�s�W��combobox
	CString objNum;
	objNum.Format(_T("%d"), m_totalObjNum);
	m_combo_objList.InsertString(m_totalObjNum, objNum);
	m_combo_objList.SetCurSel(m_totalObjNum);
	//4-2.view
	sprintf_s(path, "objectHis/colorMaskData%d.png", m_totalObjNum);
	ShowImage(cvLoadImage(path, 3), GetDlgItem(IDC_IMAGE_viewObj));
	//4-3.�u��w�Ӽ�+1
	m_totalObjNum++;
	UpdateData(false);


	cvReleaseImage(&hisImgData);
	cvReleaseImage(&pImg_live);
	cvReleaseImage(&pImg_depth);
	cvReleaseImage(&pImg_colorMask);
}


void tab1Dlg::OnBnClickedButtonviewobj()
{
	// 1.��ܩҿ�ܪ��u��his
	int select = m_combo_objList.GetCurSel();
	char path[100];
	sprintf_s(path, "objectHis/hisImgData%d.png", select);
	cvShowImage("hisImgData", cvLoadImage(path, 3));
}


void tab1Dlg::OnBnClickedButtondetectobj()
{
	// 1.�]�w�D����"�ثe�����u��s��:"
	//camshift
	//Contour

	int select = m_combo_objList.GetCurSel();

	//1. Ū��**********
	IplImage* pImg_live = nullptr;
	if (sImage_live->nChannels == 3)
	{
		pImg_live = cvCloneImage(sImage_live);
	}
	else if (sImage_live->nChannels == 4)
	{
		pImg_live = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
		cvCvtColor(sImage_live, pImg_live, CV_BGRA2BGR);
	}
	else { MessageBox(L"pImg_live Channels error"); }

	IplImage* pImg_depth = nullptr;
	if (sImage_depth->nChannels == 3)
	{
		pImg_depth = cvCloneImage(sImage_depth);
	}
	if (sImage_depth->nChannels == 1)
	{
		pImg_depth = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
		cvCvtColor(sImage_depth, pImg_depth, CV_GRAY2BGR);
	}
	else { MessageBox(L"pImg_depth Channels error"); }

	//2.����β`�׷�B�n���m��v��(colorMask)**********
	IplImage* pImg_colorMask = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
	cvAnd(pImg_depth, pImg_live, pImg_colorMask); //(ch3,ch3,ch3)

	CSpatch_inTab1.setImage(pImg_colorMask);

	CvBox2D trackBox = CSpatch_inTab1.getTrackBox(maskRange, hisData[select]);

	IplImage* pImg_track = cvCloneImage(pImg_live);

	CvPoint LTP, RBP;
	LTP.x = trackBox.center.x - trackBox.size.width / 2;
	LTP.y = trackBox.center.y - trackBox.size.height / 2;
	RBP.x = trackBox.center.x + trackBox.size.width / 2;
	RBP.y = trackBox.center.y + trackBox.size.height / 2;
	if (trackBox.size.width > IMG_WIDTH || trackBox.size.width<0 || trackBox.size.height>IMG_HIGHT || trackBox.size.height < 0)
	{
		MessageBox(L"Detect Fail");
	}
	else
	{
		cvRectangle(pImg_track, LTP, RBP, cvScalar(0, 50, 255), 3);

		//contour**********
		CContour contour;

		IplImage* pConImage = nullptr;
		pConImage = contour.DoContour(pImg_depth);

		for (int i = 0; i <= contour.ObjectQuantity; i++)
		{
			//�����I�btrackWindow�̫h���
			if (contour.CenterPoint[i].x > LTP.x && contour.CenterPoint[i].x < RBP.x && contour.CenterPoint[i].y > LTP.y && contour.CenterPoint[i].y < RBP.y)
			{
				cvCircle(pImg_track, contour.CenterPoint[i], 5, CV_RGB(255, 0, 0), 2);
				cvCircle(pImg_track, contour.ClosestPoint[i], 5, CV_RGB(0, 0, 255), 2);
				m_gripCenterX = contour.CenterPoint[i].x;
				m_gripCenterY = contour.CenterPoint[i].y;
				m_gripDegree = angle(contour.CenterPoint[i], contour.ClosestPoint[i]);
				UpdateData(false);
			}
		}
		ShowImage(pImg_track, GetDlgItem(IDC_IMAGE_detectObj));
		cvReleaseImage(&pConImage);
	}

	cvReleaseImage(&pImg_track);
	cvReleaseImage(&pImg_colorMask);
	cvReleaseImage(&pImg_live);
	cvReleaseImage(&pImg_depth);
}