
// DlgProxy.cpp : 实现文件
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
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
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
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CBaiduTranslateDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IBaiduTranslate 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {CB83B94D-18B7-4034-9108-8593F6B27B55}
static const IID IID_IBaiduTranslate =
{ 0xCB83B94D, 0x18B7, 0x4034, { 0x91, 0x8, 0x85, 0x93, 0xF6, 0xB2, 0x7B, 0x55 } };

BEGIN_INTERFACE_MAP(CBaiduTranslateDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CBaiduTranslateDlgAutoProxy, IID_IBaiduTranslate, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {CB6CECE9-433C-44EF-BF0A-28B333B997CF}
IMPLEMENT_OLECREATE2(CBaiduTranslateDlgAutoProxy, "BaiduTranslate.Application", 0xcb6cece9, 0x433c, 0x44ef, 0xbf, 0xa, 0x28, 0xb3, 0x33, 0xb9, 0x97, 0xcf)


// CBaiduTranslateDlgAutoProxy 消息处理程序
