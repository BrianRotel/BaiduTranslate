
// BaiduTranslateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "myThread.h"
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
class CBaiduTranslateDlgAutoProxy;


// CBaiduTranslateDlg 对话框
class CBaiduTranslateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaiduTranslateDlg);
	friend class CBaiduTranslateDlgAutoProxy;

// 构造
public:
	CBaiduTranslateDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CBaiduTranslateDlg();
	myThread m_myThread;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BAIDUTRANSLATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CBaiduTranslateDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
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
