
// DlgProxy.h: 头文件
//

#pragma once

class CBaiduTranslateDlg;


// CBaiduTranslateDlgAutoProxy 命令目标

class CBaiduTranslateDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CBaiduTranslateDlgAutoProxy)

	CBaiduTranslateDlgAutoProxy();           // 动态创建所使用的受保护的构造函数

// 特性
public:
	CBaiduTranslateDlg* m_pDialog;

// 操作
public:

// 重写
	public:
	virtual void OnFinalRelease();

// 实现
protected:
	virtual ~CBaiduTranslateDlgAutoProxy();

	// 生成的消息映射函数

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBaiduTranslateDlgAutoProxy)

	// 生成的 OLE 调度映射函数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

