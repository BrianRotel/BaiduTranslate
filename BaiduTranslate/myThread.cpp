// myThread.cpp: implementation of the myThread class.
// Code By BrianRotel 2020.01.12 for Game Factorio use BaiduTranslateAPI
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaiduTranslate.h"
#include "myThread.h"
#include "comm.h"
#include  "json/json.h"
#include <string>
#include "md5.h"
#include <locale.h> 
#ifdef _DEBUG
#pragma comment(lib, "lib/jsoncppd.lib")
#else
#pragma comment(lib, "lib/jsoncpp.lib")
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

myThread::myThread()
{
	pEditSoc = NULL;
	pEditRe = NULL;
	pButtonTrans = NULL;
	pProgressCtrl = NULL;
	pEditBrowseCtrl = NULL;
}

myThread::~myThread()
{

}

BOOL myThread::Work(CEdit *m_editSoc, CEdit *m_editRe, CButton *m_buttonTrans, CProgressCtrl *m_ProgressCtrl, CMFCEditBrowseCtrl *m_EditBrowseCtrl)
{
	if (m_editSoc == NULL )
		return FALSE;
	pEditSoc = m_editSoc;
	pEditRe = m_editRe;
	pButtonTrans = m_buttonTrans;
	pProgressCtrl = m_ProgressCtrl;
	pEditBrowseCtrl = m_EditBrowseCtrl;
	return StartThread();
}

UINT myThread::ThreadMain()
{
	// init progress control
	//m_pProgress->SetWindowTextW(L"ss");
	//m_pProgress->SetPos(0);
	//CString show;
	ReadConfigFile(/*L"locale.cfg"*/);

#if 0
	pProgressCtrl->SetRange32(0, 425);
	for(int i=1; i<426; ++i)
	{
		//show.Format(L"%d", i);
		pProgressCtrl->SetPos(i);
		//if(ShouldDie())
			//return 1;
		CString str1;
		CString str2;
		str1.Format(L"%d", 425);
		str2.Format(L"%d", i);
		pEditSoc->SetWindowTextW(str1);
		pEditRe->SetWindowTextW(str2);

		//m_pProgress->SetPos(i);
		Sleep(10);
	}
#endif
	return 0;
}
#pragma region GBK编码转UTF8编码
void myThread::ConvertGBKToUtf8(char * strGBK, char * strUtf8, int utflen)
{
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL, 0);
	unsigned short * wszUtf8 = new unsigned short[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);
	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);
	strcpy(strUtf8, szUtf8);
	delete[] szUtf8;
	delete[] wszUtf8;
}
#pragma region UTF8编码转GBK编码
void myThread::ConvertUtf8ToGBK(char * strUtf8, char * strGBK)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	strcpy(strGBK, szGBK);
	delete[] szGBK;
	delete[] wszGBK;
}
CString myThread::CommitGetTrans(CString str)
{
	CLibCurl client;
	int iRet = 0;
	char* RecvBuf = NULL;
	CString m_Err;
	char Err[1024 + 1];
	TCHAR ORGNURL[2048 + 1] = L"http://api.fanyi.baidu.com/api/trans/vip/translate?";
	Json::Value root;
	std::string request;
	CString querry(str);

	//TCHAR str[1280] = L"Enablegametweaks-FuelEmissionsMultipliers";


	root["q"] = querry.GetBuffer();
	root["from"] = "en";
	root["to"] = "zh";
	root["appid"] = "20200107000373569";
	int rand_no = time(NULL);
#if 0
	int i = 0;
	while (rand_no <= gTime)
	{
		++i;
		Sleep(200);
		rand_no = time(NULL);
	}

	gTime = rand_no;
	CString sleeptime;
	sleeptime.Format(_T("睡了%d次"), i);
	pEditSoc->SetWindowTextW(sleeptime);

#endif
	CString Rand;
	Rand.Format(_T("%d"), rand_no);

	root["salt"] = Rand.GetBuffer();//随机数
	string s_md5 = "20200107000373569";// +st2 + "12306kBFfC8dCRweaFrlN4A";//appid + q + salt + 密钥06kBFfC8dCRweaFrlN4A____ 06kBFfC8dCRweaFrlN4A  
	{
		USES_CONVERSION;
		s_md5.append(CT2A(querry.GetBuffer()));
	}
	{
		USES_CONVERSION;
		s_md5.append(CT2A(Rand.GetBuffer()));
	}

	s_md5.append("06kBFfC8dCRweaFrlN4A");//20200107000373569apple12306kBFfC8dCRweaFrlN4A

										 //MD5 gMD5(s_md5);
	std::string local_md5 = MD5::MD5String(s_md5);//3bb7ca4a49798c8a0b802eaae50c3dcb
	CString md5(local_md5.c_str());
	root["sign"] = local_md5;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";
	//CString  cstr = L"http://api.fanyi.baidu.com/api/trans/vip/translate?q=Enablegametweaks-FuelEmissionsMultipliers&from=en&to=zh&appid=20200107000373569&salt=1435660288&sign=6b4c12816779ff364bcc278162dc56e3";
	CString  cstr = ORGNURL;
	cstr = cstr + "q=" + querry + "&from=en&to=zh&appid=20200107000373569&salt=" + Rand + "&sign=" + md5;
	_stprintf_s(ORGNURL, ARRAYSIZE(ORGNURL), _T("%s"), cstr.GetBuffer());

	request = Json::writeString(builder, root);
	{
		USES_CONVERSION;
		iRet = client.DownloadVersion(T2A(ORGNURL), "{}", &RecvBuf, Err);
	}


	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	//Json::String version;
	//Json::String arrList;
	Json::String err;
	Json::Value result;
	Json::String orgnresult;
	Json::Value orgn;
	Json::String retcode;
	Json::String retstr;
	//Json::Value upresult;
	//Json::Value records;
	if (!reader->parse(RecvBuf, RecvBuf + strlen(RecvBuf), &result, &err))
	{
		//goto RET;
		delete[] reader;
		client.FreeMem(RecvBuf);
		return false;
	}

	orgn = result["trans_result"];

	char s[1280];

	for (int i = 0; i < orgn.size(); ++i)
	{
		Json::String sys_name = orgn[i]["dst"].asString();
		ConvertUtf8ToGBK((char*)sys_name.c_str(), s);
	}
	CString strReturn = NULL;
	strReturn = s;
	if (!strReturn.IsEmpty())
	{
		delete[] reader;
		client.FreeMem(RecvBuf);
		return strReturn;
	}
	delete[] reader;
	client.FreeMem(RecvBuf);
	//return true;
	return strReturn;
}
void myThread::OperLocalFile(CString& strFile, CString& strContent)
{
	HANDLE hFile = CreateFile(strFile,
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile) return;
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (INVALID_FILE_SIZE == dwFileSize || 0 == dwFileSize)
	{
		CloseHandle(hFile);
		return;
	}
	LPTSTR pszBuffer = strContent.GetBufferSetLength(dwFileSize + sizeof(TCHAR));
	if (pszBuffer == NULL) return;
	memset(pszBuffer, 0x00, dwFileSize + sizeof(TCHAR));
	DWORD dwBytesToRead = dwFileSize, dwBytesRead = 0, dwBytes;
	do
	{
		if (!ReadFile(hFile, (BYTE*)pszBuffer + dwBytesRead, dwBytesToRead - dwBytesRead, &dwBytes, NULL))
		{
			break;
		}
		dwBytesRead += dwBytes;
	} while (dwBytesRead < dwBytesToRead);
	CloseHandle(hFile);
	int oper = IS_TEXT_UNICODE_ASCII16 /*| IS_TEXT_UNICODE_STATISTICS */ | IS_TEXT_UNICODE_SIGNATURE;
	BOOL IsUnicode = IsTextUnicode((LPVOID)pszBuffer, dwBytesRead, &oper);
	if (!IsUnicode)
	{
		// ANSI
		{
			USES_CONVERSION;
			_stprintf_s(pszBuffer, dwFileSize + sizeof(TCHAR), _T("%s"), A2T(((CHAR*)pszBuffer)));
		}
	}
	else
	{
		// Unicode
		{
			USES_CONVERSION;
			_stprintf_s(pszBuffer, dwFileSize + sizeof(TCHAR), _T("%s"), W2T((WCHAR*)pszBuffer));
		}
	}
	strContent.ReleaseBuffer();
	if (strContent.GetLength() > 1 && strContent.GetAt(0) == 0xfeff)
	{
		strContent.Delete(0, 1);
	}
}
void myThread::ReadConfigFile(LPCTSTR name)
{
	// 读取配置文件	
	CString en_strReturn;
	CString en_strStar;
	CString strConfig;
	CString strConfigtxt;

	pEditBrowseCtrl->GetWindowTextW(strConfigtxt);
	strConfigtxt.Remove(TEXT('\"'));
	TCHAR* modulePath = strConfigtxt.GetBufferSetLength(MAX_PATH);
	//::PathAppend(modulePath, g_zdCefVersion);
	::PathAppend(modulePath, name);
#pragma region 获得文件行数
	//char line[1280] = { 0 };
	//int count = 0;
	//strConfigtxt.ReleaseBuffer();
	//{
	//	USES_CONVERSION;
	//	char fname[MAX_PATH] = {0};
	//	//W2A(modulePath);
	//	sprintf(fname,"%s", W2A(modulePath));
	//	FILE * fp = fopen(fname, "r");
	//	if (!fp)
	//		return;
	//	while (fgets(line, 1280, fp))
	//	{
	//		count++;
	//	}
	//}

	OperLocalFile(strConfigtxt, strConfig);
	//GetTxtLine();
#pragma region 获得文件行数
	/*int j = 0;
	CString rn_str = _T("\r\n");
	int npos = 0;
	while (true)
	{
		npos = strConfig.Find(rn_str, npos+4);
		if (npos == -1)break;
		++j;
	}*/
	TCHAR* pszConfig = strConfig.GetBuffer();
	int j = lstrlen(pszConfig);
	TCHAR* token = NULL;
	TCHAR* next_token = NULL;
	TCHAR seps[] = TEXT("\r\n");
	token = _tcstok_s(pszConfig, seps, &next_token);
	
	pProgressCtrl->SetRange32(0, j);
	//翻译乱码,解决想法:
	/*
	*1.将流中所有空格后一位的字符变为大写,写一个梳理函数,
	*2.执行翻译,将读取的字符累计,翻译时累计
	*3.写入新文件.写一个写文件函数
	*用到的知识,C++iostream,20200111,最近做多线程有点头疼
	*/
	int i = 0;
	while (token != NULL)
	{
		if (ShouldDie())
			goto Ret;
		i = lstrlen(next_token);
		if (i <= 100) {
			for (int z =0;z<100;++z);
		}
		int k = i <=0 ? j : j-i;
		//int k = j-i;
		pProgressCtrl->SetPos(k);//因为分隔符总比字符串少1,而字符	
		CString strRecode(token);
		strRecode = strRecode.Trim();//
		//strRecode = L"SolarPowerPlant&Boiler";
		while (true)
		{
			int npos = strRecode.Find(L" ");
			int npos1 = strRecode.Find(L"&");
			//int npos2 = strRecode.Find(L"+");
			if (npos == -1 && npos1 == -1 /*&& npos2 == -1*/)break;			
			if (npos >= 0) {
				char m_str = strRecode.GetAt(npos + 1);
				if (m_str > 'a' && m_str < 'z')
				{
					m_str -= 32;
				}
				strRecode.Delete(npos, 1);
				strRecode.SetAt(npos, m_str);
			}
			if (npos1 >= 0) {
				strRecode.SetAt(npos1, 'A');
				strRecode.Insert(npos1 + 1, 'n');
				strRecode.Insert(npos1 + 2, 'd');
			}
			//if (npos2 >= 0) {
			//	strRecode.SetAt(npos2, '');
			//}

		}
		
		strRecode.Remove('+');
		//strRecode.Replace(' ', '\n');
		
		int a = strRecode.FindOneOf(L"=");
		if(a == -1)T_ReturnIO = T_ReturnIO + strRecode + L"\r\n";
		if (a > 0)
		{

			en_strReturn = strRecode.Mid(a + 1);
			en_strStar = strRecode.Mid(0, a);
			pEditSoc->SetWindowTextW(en_strReturn);
			//strReturn = L"PrototypeArtilleryDamage:__1__";
			if (!en_strReturn.IsEmpty())
			{
				CString cn_strReturn = CommitGetTrans(en_strReturn);
				
				if (!cn_strReturn.IsEmpty() )
				{
					//strStar = strStar + "=" + str;
					pEditRe->SetWindowTextW(cn_strReturn);
					T_ReturnIO = T_ReturnIO + en_strStar + L"=" + cn_strReturn + L"\r\n";
					//ChangeClientConf(en_strStar, cn_strReturn);
					//PostMessage(strR);
				}

				//测试CProgressCtrl
				/*
				CString str_i;
				str_i.Format(L"%d", k);
				pEditRe->SetWindowTextW(str_i);
				*/
				
				//MessageBox(L"有值");
				//IDC_EDIT2
				//m_pProgress->SetWindowTextW(strR);
				//str.ReleaseBuffer();
			}
		}
		Sleep(1500);//5秒延迟
		token = _tcstok_s(NULL, seps, &next_token);
		//++i;
	}
#pragma region 翻译自然结束.
	PrintTxt();
	AfxMessageBox(_T("翻译结束"));
	pButtonTrans->SetWindowTextW(_T("开始翻译"));
	StopThread();
#pragma region 翻译被终止 /*1.点了结束翻译按钮*/ 2.文件未找到 3.结束程序
Ret:
	strConfig.ReleaseBuffer();
	//SetDlgItemText(IDC_Translate, _T("开始翻译"));
	//pButtonTrans->SetDlgItemTextW(pButtonTrans->GetDlgCtrlID(),_T("开始翻译"));
	
	return;
}
void myThread::ChangeClientConf(LPCTSTR key, LPCTSTR value)
{
	CString strConfig;
	CString strNewConfig;
	CString strConfigtxt;
	CString strNewtxt;
	pEditBrowseCtrl->GetWindowTextW(strConfigtxt);
	strConfigtxt.Remove(TEXT('\"'));
	int position = strConfigtxt.ReverseFind('\\');
	int length = strConfigtxt.GetLength();
	strNewtxt = strConfigtxt.Right(length - position - 1);
	strConfigtxt = strConfigtxt.Left(position+1);
	
	strNewtxt = strNewtxt.Left(strNewtxt.ReverseFind('.'));
	//功能重复
	/*TCHAR* modulePath = strConfigtxt.GetBufferSetLength(MAX_PATH);
	//::PathAppend(modulePath, g_zdCefVersion);
	::PathAppend(modulePath, strNewtxt);
	::PathAppend(modulePath, TEXT(".txt"));
	*/
	//
	strConfigtxt.Append(strNewtxt);
	strConfigtxt.Append(_T(".txt"));

	strConfigtxt.ReleaseBuffer();
	OperLocalFile(strConfigtxt, strConfig);
	BOOL FIND = FALSE;
	TCHAR* pszConfig = strConfig.GetBuffer();
	TCHAR* token = NULL;
	TCHAR* next_token = NULL;
	TCHAR seps[] = TEXT("\r\n");
	token = _tcstok_s(pszConfig, seps, &next_token);
	while (token != NULL)
	{
		CString strRecode(token);
		strRecode = strRecode.Trim();
		//if (_tcsnicmp(TEXT("SYSTEM"), strRecode.GetBuffer(), _tcslen(TEXT("SYSTEM"))) == 0)
		//{
		//}
		//else if (_tcsnicmp(key, strRecode.GetBuffer(), _tcslen(key)) == 0)
		if (_tcsnicmp(key, strRecode.GetBuffer(), _tcslen(key)) == 0)
		{
			strNewConfig.AppendFormat(_T("%s=%s\r\n"), key, value);
			FIND = TRUE;
		}
		else
		{
			strNewConfig.Append(token);
			strNewConfig.Append(TEXT("\r\n"));
			//MessageBox(_T("")+token);
		}
		token = _tcstok_s(NULL, seps, &next_token);
	}
	strConfig.ReleaseBuffer();
	if (!FIND)
	{
		strNewConfig.AppendFormat(_T("%s=%s\r\n"), key, value);
	}
	if (strNewConfig.GetAt(0) != 0xfeff)
	{
		strNewConfig.Insert(0, 0xfeff);
	}
	HANDLE hFile;
	for (;;)
	{
		hFile = CreateFile(strConfigtxt,
			GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
			break;
		Sleep(200);
	}
	DWORD dwBytesToWrite = strNewConfig.GetLength() * sizeof(TCHAR);
	DWORD dwBytesWritten = 0;
	if (FALSE == WriteFile(hFile, strNewConfig.GetBuffer(), dwBytesToWrite, &dwBytesWritten, NULL))
	{
		//g_log.Add(2, fmtmsg(_T("参数[%s]报错失败[%s]"), key, value));
	}
	CloseHandle(hFile);
}
void myThread::PrintTxt()
{
	CString strConfigtxt;
	CString strNewtxt;
	pEditBrowseCtrl->GetWindowTextW(strConfigtxt);
	strConfigtxt.Remove(TEXT('\"'));
	int position = strConfigtxt.ReverseFind('\\');
	int length = strConfigtxt.GetLength();
	strNewtxt = strConfigtxt.Right(length - position - 1);
	strConfigtxt = strConfigtxt.Left(position + 1);

	strNewtxt = strNewtxt.Left(strNewtxt.ReverseFind('.'));

	strConfigtxt.Append(strNewtxt);
	strConfigtxt.Append(_T("1.cfg"));

	WORD unicode = 0xFEFF;
	if (!T_ReturnIO.IsEmpty())
	{
		//pEditRe->SetWindowTextW(lll);
		CStdioFile File;
		File.Open(strConfigtxt, CFile::modeReadWrite | CFile::typeUnicode | CFile::modeCreate);
		File.Write(&unicode, 2);
		File.Write(T_ReturnIO, wcslen(T_ReturnIO) * sizeof(wchar_t));
		//File.SeekToEnd();
		//File.WriteString(T_ReturnIO);
		File.Close();
	}
}