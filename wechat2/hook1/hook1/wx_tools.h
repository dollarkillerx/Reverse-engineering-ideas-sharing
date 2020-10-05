#pragma once
#include "Windows.h"
#include <stdio.h>


//username         地址 : 647040CC        偏移量 : 17740CC
//phone_number     地址 : 64704100        偏移量 : 1774100
//wx_id            地址 : 64704230        偏移量 : 1774230
//os               地址 : 64704520        偏移量 : 1774520
//avatar           地址 : 64704394        偏移量 : 1774394 *

class Wx
{
	DWORD winAdd;
public:
	Wx()
	{
		HMODULE winAddH = LoadLibrary(TEXT("WeChatWin.dll"));
		winAdd = (DWORD)winAddH;
	}
	CHAR* GetWxID()
	{
		return readWechatData(0x1774230);
	}
	CHAR * GetPhoneNumber()
	{
		return readWechatData(0x1774100);
	}
	CHAR * GetUserName()
	{
		return readWechatData(0x17740CC);
	}
	CHAR * GetOS()
	{
		return readWechatData(0x1774520);
	}
	CHAR * GetAvatar()  // avatar这是一个指针
	{
		DWORD avatarPit = getPointerAddress(0x1774394);
		// (DWORD*)avatarPit;   这样就能转为指针
		*(DWORD*)avatarPit;
		CHAR data[0x100] = { 0 };
		sprintf_s(data, "%s", *(DWORD*)avatarPit);
		return data;
	}
	VOID UpdataWxID(char * wx_id)
	{
		// 更新微信ID
		// GetCurrentProcess 获取当前进程句柄
		WriteProcessMemory(GetCurrentProcess(), (LPVOID)(winAdd + 0x1774230),wx_id,sizeof(wx_id),NULL);
	}
private:
	CHAR * readWechatData(DWORD addr)
	{
		CHAR data[0x100] = { 0 };
		sprintf_s(data,"%s",winAdd + addr);
		return data;
	}
	DWORD getPointerAddress(DWORD addr)
	{
		return winAdd + addr;
	}
};