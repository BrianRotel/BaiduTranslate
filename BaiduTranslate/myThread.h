// myThread.h: interface for the myThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTHREAD_H__41BEA7DF_5B3F_4A0A_B01C_F65CB47690E6__INCLUDED_)
#define AFX_MYTHREAD_H__41BEA7DF_5B3F_4A0A_B01C_F65CB47690E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AG_Thread.h"

class myThread : public CAG_Thread  
{
public:
	myThread();
	virtual ~myThread();

	// I provide this function to pass any kind of parameters
	BOOL Work(CEdit *Source, CEdit *Return = NULL, CButton *ButtonTrans = NULL, CProgressCtrl *pProgressCtrl = NULL, CMFCEditBrowseCtrl* m_EditBrowseCtrl=NULL);
	
protected:
	// Progress controll to show progress
	CEdit *pEditRe;
	CEdit *pEditSoc;
	CButton *pButtonTrans;
	CProgressCtrl *pProgressCtrl;
	CMFCEditBrowseCtrl* pEditBrowseCtrl;
	int gTime;
	CString T_ReturnIO;

	// must override this function
	UINT ThreadMain();
public:
	CString CommitGetTrans(CString str);
	void ConvertGBKToUtf8(char * strGBK, char * strUtf8, int utflen);
	void ConvertUtf8ToGBK(char * strUtf8, char * strGBK);
	void ReadConfigFile(LPCTSTR name=NULL);
	void OperLocalFile(CString& strFile, CString& strContent);
	void ChangeClientConf(LPCTSTR key, LPCTSTR value);
	void myThread::PrintTxt();
public:
	//TCHAR g_GetCurrentDir[MAX_PATH] = L"F:\\mfc4\\BaiduTranslate\\Debug";
	
};

#endif // !defined(AFX_MYTHREAD_H__41BEA7DF_5B3F_4A0A_B01C_F65CB47690E6__INCLUDED_)
