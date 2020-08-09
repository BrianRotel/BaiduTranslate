#include "comm.h"
#define CURL_STATICLIB
#include "curl/curl.h"
#ifdef _DEBUG
#pragma comment(lib, "lib/libcurld.lib")
#else
#pragma comment(lib, "lib/libcurl.lib")
#endif

#pragma comment(lib, "lib/libeay32.lib")
#pragma comment(lib, "lib/ssleay32.lib")

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")


CLibCurl::CLibCurl()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

CLibCurl::~CLibCurl()
{
	curl_global_cleanup();
}

int CLibCurl::DownloadVersion(const char* url, const char* sendbuf, char** recvbuf, char* Err)
{
	if (Err) Err[0] = '\0';

	int iRet = 0;

	CURL* curl = curl_easy_init();
	struct curl_slist* list = NULL;

	if (!curl)
	{
		sprintf(Err, "初始化失败");
		return -1;
	}

	CURLcode res;
	struct MemoryStruct recv_chunk;
	recv_chunk.memory = (char*)malloc(1);
	if (recv_chunk.memory == NULL)
	{
		curl_easy_cleanup(curl);
		sprintf(Err, "初始化失败");
		return -1;
	}

	recv_chunk.size = 0;
	memset(recv_chunk.memory, 0x00, 1);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 1L);

	{
		//list = curl_slist_append(list, "reference: pscb/sunyard");
		list = curl_slist_append(list, "Expect:");
		//list = curl_slist_append(list, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	}

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

#ifdef _DEBUG
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(sendbuf));
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sendbuf);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&recv_chunk);

	res = curl_easy_perform(curl);

	if (CURLE_OK != res)
	{
		sprintf(Err, "%s %s", Err, curl_easy_strerror(res));
		iRet = -1;
		goto RET;
	}
	long response_code;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	if (200 != response_code)
	{
		iRet = -1;
		sprintf(Err, "%s", "HTTP返回状态码不对");
	}

RET:
	*recvbuf = recv_chunk.memory;
	if (list)
		curl_slist_free_all(list);
	return iRet;
}

int CLibCurl::DownloadFile(const char* url, const char* path, char* Err)
{
	CURL* curl;
	CURLcode res;
	FILE* fp = NULL;

	int iRet = 0;

	curl = curl_easy_init();

	if (!curl) return -1;


	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

	// SSL not check
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#ifdef _DEBUG
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
	// 连接超时
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

	// 传输超时
	//curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo);
	//curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &prog);

	/* abort if slower than 30 bytes/sec during 60 seconds */
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 60L);
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 30L);

	fp = fopen(path, "wb");
	if (NULL == fp)
	{
		iRet = -1;
		sprintf(Err, "创建文件失败:%s", strerror(errno));
		goto RET;
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	res = curl_easy_perform(curl);
	if (CURLE_OK != res)
	{
		iRet = -1;
		sprintf(Err, "%s %s", Err, curl_easy_strerror(res));
		goto RET;
	}
	long response_code;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	if (response_code != 200)
	{
		iRet = -1;
		sprintf(Err, "%s", "HTTP返回状态码不对");
	}
RET:
	if (fp) fclose(fp);
	if (iRet == -1)
	{
		::DeleteFileA(path);
	}
	curl_easy_cleanup(curl);
	return iRet;
}

void CLibCurl::FreeMem(void* mem)
{
	if (mem)
		free(mem);
}

size_t CLibCurl::WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;
	char* tmp = mem->memory;
	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		mem->memory = tmp;
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

