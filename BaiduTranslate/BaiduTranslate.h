
// BaiduTranslate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBaiduTranslateApp: 
// �йش����ʵ�֣������ BaiduTranslate.cpp
//

class CBaiduTranslateApp : public CWinApp
{
public:
	CBaiduTranslateApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBaiduTranslateApp theApp;