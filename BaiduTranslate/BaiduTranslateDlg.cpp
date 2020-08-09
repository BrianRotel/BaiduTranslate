
// BaiduTranslateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BaiduTranslate.h"
#include "BaiduTranslateDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"



// CBaiduTranslateDlg 对话框
IMPLEMENT_DYNAMIC(CBaiduTranslateDlg, CDialogEx);

CBaiduTranslateDlg::CBaiduTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BAIDUTRANSLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CBaiduTranslateDlg::~CBaiduTranslateDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CBaiduTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editRe);
	DDX_Control(pDX, IDC_EDIT1, m_editSoc);
	DDX_Control(pDX, IDC_Translate, m_buttonTrans);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_EditBrowseCtrl);
}

BEGIN_MESSAGE_MAP(CBaiduTranslateDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Translate, &CBaiduTranslateDlg::OnBnClickedTranslate)
END_MESSAGE_MAP()


// CBaiduTranslateDlg 消息处理程序

BOOL CBaiduTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBaiduTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBaiduTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CBaiduTranslateDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CBaiduTranslateDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CBaiduTranslateDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CBaiduTranslateDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL && m_myThread.GetThreadStatus())
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}
	//if (m_myThread.GetThreadStatus())
	//{
	//	//ShowWindow(SW_HIDE);
	//	if (m_myThread.StopThread())
	//	{
	//		return TRUE;
	//	}
	//	return FALSE;
	//}

	return TRUE;
}



void CBaiduTranslateDlg::OnBnClickedTranslate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString editBrowerCtrl;
	m_EditBrowseCtrl.GetWindowTextW(editBrowerCtrl);
	if (editBrowerCtrl.IsEmpty())
	{
		AfxMessageBox(_T("请选择文件"));
		return;
	}
	if (m_myThread.GetThreadStatus())
	{
		if (m_myThread.StopThread())
		{
			AfxMessageBox(_T("Thread killed successfuly!"));
			SetDlgItemText(IDC_Translate, _T("开始翻译"));
			return;
		}

		AfxMessageBox(_T("Could not abort thread."));
	}
	else
	{
		if (m_myThread.Work(&m_editSoc,&m_editRe,&m_buttonTrans,&m_ProgressCtrl,&m_EditBrowseCtrl))
		{
			SetDlgItemText(IDC_Translate, _T("停止翻译"));
			return;
		}

		AfxMessageBox(_T("Could not start thread."));
	}
}
