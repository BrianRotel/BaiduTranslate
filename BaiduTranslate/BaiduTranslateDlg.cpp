
// BaiduTranslateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BaiduTranslate.h"
#include "BaiduTranslateDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"



// CBaiduTranslateDlg �Ի���
IMPLEMENT_DYNAMIC(CBaiduTranslateDlg, CDialogEx);

CBaiduTranslateDlg::CBaiduTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BAIDUTRANSLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CBaiduTranslateDlg::~CBaiduTranslateDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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


// CBaiduTranslateDlg ��Ϣ�������

BOOL CBaiduTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBaiduTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaiduTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString editBrowerCtrl;
	m_EditBrowseCtrl.GetWindowTextW(editBrowerCtrl);
	if (editBrowerCtrl.IsEmpty())
	{
		AfxMessageBox(_T("��ѡ���ļ�"));
		return;
	}
	if (m_myThread.GetThreadStatus())
	{
		if (m_myThread.StopThread())
		{
			AfxMessageBox(_T("Thread killed successfuly!"));
			SetDlgItemText(IDC_Translate, _T("��ʼ����"));
			return;
		}

		AfxMessageBox(_T("Could not abort thread."));
	}
	else
	{
		if (m_myThread.Work(&m_editSoc,&m_editRe,&m_buttonTrans,&m_ProgressCtrl,&m_EditBrowseCtrl))
		{
			SetDlgItemText(IDC_Translate, _T("ֹͣ����"));
			return;
		}

		AfxMessageBox(_T("Could not start thread."));
	}
}
