#pragma once
#pragma warning(disable: 4996)
// 接收数据
struct MemoryStruct {
	char* memory;
	size_t size;
};
class CLibCurl
{
public:
	CLibCurl();
	~CLibCurl();

public:
	int DownloadVersion(const char* url, const char* sendbuf, char** recvbuf, char* Err);
	int DownloadFile(const char* url, const char* path, char* Err);

	void FreeMem(void *mem);

	static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);
	//static size_t read_callback(void* dest, size_t size, size_t nmemb, void* userp);
};

class CJsonParser
{
	//std::UTF8String 
};
class JsonInstaller
{
private:
	JsonInstaller(void) {};
public:
	static bool Install(char* records_json);
	static bool Backup(char* records_json);
};