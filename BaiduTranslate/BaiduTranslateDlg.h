
// BaiduTranslateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "myThread.h"
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
class CBaiduTranslateDlgAutoProxy;


// CBaiduTranslateDlg �Ի���
class CBaiduTranslateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaiduTranslateDlg);
	friend class CBaiduTranslateDlgAutoProxy;

// ����
public:
	CBaiduTranslateDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CBaiduTranslateDlg();
	myThread m_myThread;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BAIDUTRANSLATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CBaiduTranslateDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTranslate();


public:
	
	
	CEdit m_editRe;
	CEdit m_editSoc;
	CButton m_buttonTrans;
	CProgressCtrl m_ProgressCtrl;
	CMFCEditBrowseCtrl m_EditBrowseCtrl;
};
