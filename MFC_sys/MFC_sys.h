
// MFC_sys.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_sysApp: 
// �аѾ\��@�����O�� MFC_sys.cpp
//

class CMFC_sysApp : public CWinApp
{
public:
	CMFC_sysApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_sysApp theApp;