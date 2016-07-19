#include "CamShiftPatch.h"

CvScalar hsv2rgb(float hue)
{
	int rgb[3], p, sector;
	static const int sector_data[][3] =
	{ { 0, 2, 1 }, { 1, 2, 0 }, { 1, 0, 2 }, { 2, 0, 1 }, { 2, 1, 0 }, { 0, 1, 2 } };
	hue *= 0.033333333333333333333333333333333f;
	sector = cvFloor(hue);  //�˥h�p���I
	//std::cout<<"sector:" << sector << std::endl;
	p = cvRound(255 * (hue - sector));//���̪���
	printf("\np before:%d\n", p);
	printf("sector:%d\n", sector);
	p ^= sector ? 255 : 0;    //��sector!=0 �h p^=255  ===> �Yp=p^11111111(��XOR�B��)�A�۷���k;    ��sector=0�hp^=0  ===> �Yp�P0��XOR�B��A�۷�󤣧��ܭ�
	printf("p after:%d\n", p);
	rgb[sector_data[sector][0]] = 255;
	rgb[sector_data[sector][1]] = 0;
	rgb[sector_data[sector][2]] = p;
	return cvScalar(rgb[2], rgb[1], rgb[0], 0);
}

CamShiftPatch::CamShiftPatch(IplImage* image)
{
	histogram = 0;
	originImage = 0;
	originImage = cvCreateImage(cvGetSize(image), 8, 3);
	cvCopy(image, originImage, 0);
}
CamShiftPatch::CamShiftPatch()
{
	histogram = 0;
	originImage = 0;
}
CamShiftPatch::~CamShiftPatch()
{
}

void CamShiftPatch::setImage(IplImage* image)
{
	originImage = cvCreateImage(cvGetSize(image), 8, 3);
	cvCopy(image, originImage, 0);
}
IplImage* CamShiftPatch::getInRangeMask(CvScalar maskRange, IplImage* &hue)
{
	IplImage *mask = 0;
	mask = cvCreateImage(cvGetSize(originImage), 8, 1);//�B�n�Ŷ��A��q�D

	IplImage *hsv = 0;
	hue = cvCreateImage(cvGetSize(originImage), 8, 1); //1 channel
	hsv = cvCreateImage(cvGetSize(originImage), 8, 3);
	cvCvtColor(originImage, hsv, CV_BGR2HSV); //�m��Ŷ��ഫBGR to HSV 


	//cvShowImage("hsv", hsv);
	cvInRangeS(//cvInRangeS �\�ର => �ˬd�Ʋդ����O�_�b��Ӽƶq����
		hsv, //�Ĥ@�ӭ�Ʋ�
		cvScalar(0, maskRange.val[2], MIN(maskRange.val[0], maskRange.val[1]), 0),  //�]�A�i���U���
		cvScalar(180, 256, MAX(maskRange.val[0], maskRange.val[1]), 0), //���]�A�i���W���
		mask);
	//�o��G�Ȫ�MASK  
	cvSplit(hsv, hue, 0, 0, 0); //�u����HUE���q  
	
	//cvShowImage("mask", mask);

	IplImage* returnImg = nullptr;
	returnImg = cvCloneImage(mask);

	cvReleaseImage(&mask);
	cvReleaseImage(&hsv);

	return returnImg;
}

IplImage* CamShiftPatch::drawHistImg(CvRect selectROI, CvScalar maskRange)
{
	IplImage* hue = 0;
	hue = cvCreateImage(cvGetSize(originImage), 8, 1);
	IplImage *mask = getInRangeMask(maskRange, hue);//CvScalar 0->Vmin  1->Vmax  2->Smin

	//---�]�wROI�M�e�X�����---

	float max_val = 0.f;
	cvSetImageROI(hue, selectROI);
	cvSetImageROI(mask, selectROI);

	
	int hdims = 48; //����HIST���ӼơA�V���V��T 
	float hranges_arr[] = { 0, 180 }; //����Ͻd��
	float* hranges = hranges_arr;//���V�Ȥ�Ͻd��
	histogram = cvCreateHist(1, &hdims, CV_HIST_ARRAY, &hranges, 1); //�]�w����Ϫ��榡
	cvCalcHist(&hue, histogram, 0, mask); //�Hhue��T �o�쪽��� (�u��ROI��������T)
	cvGetMinMaxHistValue(histogram, 0, &max_val, 0, 0); //�u��̤j�� 
	cvConvertScale(histogram->bins, histogram->bins, max_val ? 255. / max_val : 0., 0); //�Y��bin��϶�[0,255]  
	//input      output        �ثש�j���Y�p         �����C�⪺�W��       
	cvResetImageROI(hue); // remove ROI  
	cvResetImageROI(mask);
	//track_window = selectROI; //�j�����Y�@�}�lROI��

	//----�e�����hist to histimg------------------

	IplImage* histimg = cvCreateImage(cvSize(320, 200), 8, 3);  //�������ܪŶ��A�T�q�D
	cvZero(histimg); //�m�I�����¦�

	int bin_w = 0;
	bin_w = histimg->width / hdims; // hdims:�����ӼơA�hbin_w�������e��  

	for (int i = 0; i < hdims; i++)
	{
		int val = cvRound(cvGetReal1D(histogram->bins, i)*histimg->height / 255);  //cvGetReal1D(��������סA�ĴX��) 
		CvScalar color = hsv2rgb(i*180.f / hdims); //�bRGB�Ŷ��W�A����ϨC�����C��p��   180/hdims��ܨC�@��h�e �A i*180/hdims�N����b�����Ӧ�m�F �Ѩ��Ӧ�m���C���T�ഫ��RGB  
		cvRectangle(histimg, cvPoint(i*bin_w, histimg->height), cvPoint((i + 1)*bin_w, histimg->height - val), color, -1, 8, 0);//�e�X���P�C�⪺���������
	}
	//---�]�wROI�M�e�X����� end---
	IplImage* returnImg = nullptr;
	returnImg = cvCloneImage(histimg);

	cvReleaseImage(&hue);
	cvReleaseImage(&mask);
	cvReleaseImage(&histimg);

	return returnImg;
}

CvBox2D CamShiftPatch::getTrackBox(CvScalar maskRange, CvHistogram *hist)
{
	IplImage* backproject = cvCreateImage(cvGetSize(originImage), 8, 1);//�ϧ�v�Ŷ��A��q�D
	IplImage* hue = 0;
	hue = cvCreateImage(cvGetSize(originImage), 8, 1);
	IplImage *mask = getInRangeMask(maskRange, hue);

	cvCalcBackProject(&hue, backproject, hist); //�ϥ�back project��k �A�p��hue���ϧ�v��
	cvAnd(backproject, mask, backproject, 0);   // �Nbackproject �Pmask ��AND �B�� �A���backproject 

	CvConnectedComp track_comp;
	CvBox2D track_box; // tracking��^���ϰ�box�A�a���� 

	CvRect zero;
	zero.x = 0; zero.y = 0; zero.width = 320; zero.height = 240;
	track_window = zero;

	for (int i = 0; i < 10; i++)
	{
		cvCamShift(
			backproject,    //��m���v���G�Ϲ�
			track_window,   //Search Window����l��
			cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1),//�ΨӧP�_�j�M�O�_����@�Ӽз�
			&track_comp,    //�O�s�B�⵲�G,�]�A�s��Search Window����m�M���n
			&track_box     //�]�t�Q���ܪ��骺�̤p�x��
			);
		track_window = track_comp.rect;
	}

	cvReleaseImage(&backproject);
	cvReleaseImage(&hue);
	cvReleaseImage(&mask);

	return track_box;
}
