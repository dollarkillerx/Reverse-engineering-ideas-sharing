#include <Windows.h>
#include <stdio.h>
#include "resource.h"
/**
 * 微信基地址: version2.9.0
 * username: 16B48AC
 * pub_wxid:16B4A10
 * phone:16B48E0
 * os:16B4CE8
 * 头像指针:16B4B74
 * wxid:16B4A58
 */


 // 获取wechat 基质
DWORD getWechatAddr()
{
    // 因为这里DLL已经注入到 进程中

    // 直接获取就行
    HMODULE addr = LoadLibrary("WeChatWin.dll");
    return (DWORD)addr;
}

// 读取内存数据
VOID readWechatData(HWND hwndDlg)
{
    // 获取wechat.dll 基础地址
    DWORD wechatAddr = getWechatAddr();

    // 装数据容器  (长度100 零填充)
    CHAR wxid[0x100] = { 0 };
    DWORD wxP = wechatAddr + 0x16B4A58;
    sprintf_s(wxid,"%s", *(DWORD *)wxP);
    SetDlgItemText(hwndDlg, ID_WXID,wxid);

    CHAR wxzh[0x100] = { 0 };
    sprintf_s(wxzh, "%s", wechatAddr + 0x16B4A10);
    SetDlgItemText(hwndDlg, ID_WXZH, wxzh);

    CHAR wxtx[0x100] = { 0 };
    DWORD txP = wechatAddr + 0x16B4B74;
	// 一级指针  *(DWORD *)txP
    sprintf_s(wxtx, "%s", *(DWORD*)txP);
    SetDlgItemText(hwndDlg, ID_WXTX, wxtx);
	
	
}
