
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CBaiduTranslateDlg;


// CBaiduTranslateDlgAutoProxy ����Ŀ��

class CBaiduTranslateDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CBaiduTranslateDlgAutoProxy)

	CBaiduTranslateDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CBaiduTranslateDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CBaiduTranslateDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBaiduTranslateDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

