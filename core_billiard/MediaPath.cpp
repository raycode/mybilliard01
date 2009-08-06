

#if defined(WIN32) || defined(WIN64)
#define NOMINMAX
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include "MediaPath.h"

#if defined(_XBOX)

#include <xtl.h>
#include <Xbdm.h>

static bool MediaFileExists(const char *fname)
{
	FILE *fp=fopen(fname,"rb");
	if(fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}

char* FindMediaFile(const char *fname,char *buff)
{
	wcscpy(buff,"d:\\");
	wcscat(buff,fname);

	if(MediaFileExists(buff))
		return buff;

	DmMapDevkitDrive();

	wcscpy(buff,"DEVKIT:\\");
	wcscat(buff,fname);

	if(MediaFileExists(buff))
		return buff;

	char msg[1024];
	sprintf(msg, "Can't find media file: %s\n", fname);
	OutputDebugString(msg);

	return buff;
}

char* GetTempFilePath(char *buff)
{
	wcscpy(buff,"d:\\");
	return buff;
}

#elif defined(__CELLOS_LV2__)

#include <sys/paths.h>

char* FindMediaFile(const char *fname,char *buff)
{
	wcscpy(buff,SYS_APP_HOME "/");
	wcscat(buff,fname);
	return buff;
}

char* GetTempFilePath(char *buff)
{
	wcscpy(buff,SYS_APP_HOME "/");
	return buff;
}

#elif defined(WIN32) || defined(WIN64)

static bool MediaFileExists(const wchar_t *fname)
{
    std::ifstream ifs( fname, std::ios_base::binary );
    return ifs.good();
}

wchar_t* FindMediaFile(const wchar_t *fname, wchar_t *buff)
{
	wchar_t curPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, curPath);
	wcscat(curPath, L"\\");

    wcscpy(buff, curPath);
	wcscat(buff, fname);
	if(MediaFileExists(buff))
		return buff;

    wcscpy(buff, curPath);
    wcscat(buff, L"..\\");
    wcscat(buff, fname);
    if(MediaFileExists(buff))
        return buff;

    wchar_t basePath[MAX_PATH];
	GetModuleFileName(NULL, basePath, MAX_PATH);
	wchar_t* pTmp = wcsrchr(basePath, '\\');
	if(pTmp != NULL){
		*pTmp = 0;
		SetCurrentDirectory(basePath);
		pTmp = wcsrchr(basePath, '\\');
		if(pTmp != NULL){
			*pTmp = 0;
		}
		pTmp = wcsrchr(basePath, '\\');
		if(pTmp != NULL){
			*(pTmp + 1) = 0;
		}
	}

	wcscpy(buff,fname);
	if(MediaFileExists(buff))
		return buff;

    return NULL;
}

wchar_t * GetTempFilePath(wchar_t *buff)
{
	wcscpy(buff, L"");
	return buff;
}

#elif defined(LINUX)

static bool MediaFileExists(const char *fname)
{
	FILE *fp=fopen(fname,"rb");
	if(fp == NULL)
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}

char* FindMediaFile(const char *fname,char *buff)
{
	wcscpy(buff,fname);
	if(MediaFileExists(buff))
		return buff;

	wcscpy(buff,"../../Samples/Media/");
	wcscat(buff,fname);
	if(MediaFileExists(buff))
		return buff;

	wcscpy(buff,"../../../Media/");
	wcscat(buff,fname);
	if(MediaFileExists(buff))
		return buff;

	wcscpy(buff,"../../Media/");
	wcscat(buff,fname);
	if(MediaFileExists(buff))
		return buff;

	wcscpy(buff,"Samples/Media/");
	wcscat(buff,fname);
	if(MediaFileExists(buff))
		return buff;

	printf("Can't find media file: %s\n", fname);

	wcscpy(buff,fname);
	return buff;
}

char* GetTempFilePath(char *buff)
{
	wcscpy(buff,"");
	return buff;
}

#endif
