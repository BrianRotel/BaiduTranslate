
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BaiduTranslate.h"
#include "DlgProxy.h"
#include "BaiduTranslateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBaiduTranslateDlgAutoProxy

IMPLEMENT_DYNCREATE(CBaiduTranslateDlgAutoProxy, CCmdTarget)

CBaiduTranslateDlgAutoProxy::CBaiduTranslateDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CBaiduTranslateDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CBaiduTranslateDlg)))
		{
			m_pDialog = reinterpret_cast<CBaiduTranslateDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CBaiduTranslateDlgAutoProxy::~CBaiduTranslateDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CBaiduTranslateDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IBaiduTranslate ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {CB83B94D-18B7-4034-9108-8593F6B27B55}
static const IID IID_IBaiduTranslate =
{ 0xCB83B94D, 0x18B7, 0x4034, { 0x91, 0x8, 0x85, 0x93, 0xF6, 0xB2, 0x7B, 0x55 } };

BEGIN_INTERFACE_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CBaiduTranslateDlgAutoProxy, IID_IBaiduTranslate, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {CB6CECE9-433C-44EF-BF0A-28B333B997CF}
IMPLEMENT_OLECREATE2(CBaiduTranslateDlgAutoProxy, "BaiduTranslate.Application", 0xcb6cece9, 0x433c, 0x44ef, 0xbf, 0xa, 0x28, 0xb3, 0x33, 0xb9, 0x97, 0xcf)


// CBaiduTranslateDlgAutoProxy ��Ϣ�������
