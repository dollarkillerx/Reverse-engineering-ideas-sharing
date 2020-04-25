// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Windows.h>
#include "resource.h"
#include <stdio.h>

// 前置声明
INT_PTR CALLBACK Dlgproc(
    HWND Arg1,
    UINT Arg2,
    WPARAM Arg3,
    LPARAM Arg4
);
void EasyMessage(LPCSTR data);
DWORD getWechatAddr();
VOID readWechatData(HWND hwndDlg);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		// 初始化模态框 ,  params: 句柄包含对话框模板的模块的句柄，模态框地址,拥有对话框的窗口的句柄,操作函数指针
		DialogBox(hModule, MAKEINTRESOURCE(ID_MAIN), NULL, &Dlgproc);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


// 对模态框事件的监听
INT_PTR CALLBACK Dlgproc(
	HWND hwndDlg, // 对话框句柄
	UINT uMags,  // 事件编号
	WPARAM wParam,
	LPARAM iParam
)
{
	switch (uMags)
	{
	case WM_INITDIALOG:  // 初始化事件
	{
		readWechatData(hwndDlg);
		MessageBox(NULL, "首次加载", "标题", 0);
		break;
	}
	case WM_CLOSE:     // 当用户点击关闭事件
	{
		// MessageBox(NULL, "Close Dialog", "Close", 0); // params: 对话框句柄,具体内容,标题,类型
		EndDialog(hwndDlg, 0); // 关闭 params: 对话框句柄,返回值
		break;
	}
	case WM_COMMAND: // 按钮事件
	{
		switch (wParam)
		{
		case ID_READ: // 读取
		{
			EasyMessage("read");
			break;
		}
		case ID_WRITE: // 写入
		{
			EasyMessage("write");
			break;
		}
		}
		break;
	}
	default:
		{
			// MessageBox(NULL, "Default", "标题", 0);
			// EndDialog(hwndDlg, 0); // 关闭 params: 对话框句柄,返回值
			break;
		}
	}

	return FALSE;
}


void EasyMessage(LPCSTR data)
{
	MessageBox(NULL, data, "Message", 0);
}

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
	sprintf_s(wxid, "%s", *(DWORD*)wxP);
	SetDlgItemText(hwndDlg, ID_WXID, wxid);

	CHAR wxzh[0x100] = { 0 };
	sprintf_s(wxzh, "%s", wechatAddr + 0x16B4A10);
	SetDlgItemText(hwndDlg, ID_WXZH, wxzh);

	CHAR wxtx[0x100] = { 0 };
	DWORD txP = wechatAddr + 0x16B4B74;
	// 一级指针  *(DWORD *)txP
	sprintf_s(wxtx, "%s", *(DWORD*)txP);
	SetDlgItemText(hwndDlg, ID_WXTX, wxtx);

}

