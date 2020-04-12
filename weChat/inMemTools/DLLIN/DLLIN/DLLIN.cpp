// DLLIN.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "DLLIN.h"

#include <stdio.h>
#include <Windows.h>
#include "resource.h"
#include <TlHelp32.h>

#define WECHAT_PROCESS_NAME "WeChat.exe"

INT_PTR CALLBACK Dlgproc(
	HWND Arg1,
	UINT Arg2,
	WPARAM Arg3,
	LPARAM Arg4
);
void InjectDLL();
DWORD ProcessNameFindPID(LPCSTR ProcessName);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// 初始化模态框 ,  params: 句柄包含对话框模板的模块的句柄，模态框地址,拥有对话框的窗口的句柄,操作函数指针
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN),NULL,&Dlgproc);
	return 0;
}


// 对模态框事件的监听
INT_PTR CALLBACK Dlgproc(
	HWND hwndDlg, // 对话框句柄
	UINT uMags,  // 事件编号
	WPARAM wParam,
	LPARAM iParam
)
{
	// 初始化事件
	if (uMags == WM_INITDIALOG) {
		MessageBox(NULL,"首次加载","标题",0);
	}

	// 关闭事件
	if(uMags == WM_CLOSE)
	{
		MessageBox(NULL, "Close Dialog", "Close", 0); // params: 对话框句柄,具体内容,标题,类型
		EndDialog(hwndDlg,0); // 关闭 params: 对话框句柄,返回值
	}

	// 所有的按钮都是走这一个宏
	if(uMags == WM_COMMAND) // 按钮事件
	{
		if (wParam == ID_unin)
		{
			MessageBox(NULL,"unin","",0);
		}
		if (wParam == ID_in)
		{
			InjectDLL();
			// MessageBox(NULL, "in", "", 0);
		}
	}
	
	return FALSE;
}


// 补充知识:
// CHAR 存放单个字符
// WCHAR       存放双字符
// TCHAR 与WCHAR无异
// PTCHAR 指向双字符类型字符串
// LPSTR 一个32位的指向字符串的指针
// LPCSTR    一个32位的指向字符串常量的指针
// LPWSTR    一个32位的指向unicode字符串的指针
// LPCWSTR  一个32位的指向unicode字符串常量的指针
// PSTR     指向字符串的指针，poionter   string

// 1. 获取微信进程句柄
	// 通过微信进程名称获取微信pid
	// 通过pid打开微信进程获取到进程句柄
DWORD ProcessNameFindPID(LPCSTR ProcessName)
{
	// #include <TlHelp32.h>
	// 1. 获取到整个系统的进程快照
		// params:   dwFlags: 要怎样的进程线程? (TH32CS_SNAPPROCESS系统中所有的进程)  th32ProcessID: 要包含在快照中的进程的进程标识符。此参数可以为零以指示当前进程
	HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL); // 获取整个系统进程快照
	// 2. 然后在快照里面对比 ProcessName
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32); // 为了兼容不同的编译器
	do
	{
		// szExeFile 进程名称
		// thi32ProcessID 进程ID
		if (strcmp(ProcessName,processInfo.szExeFile) == 0)
		{
			return processInfo.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &processInfo));

	return 0;
}

// 2. 在微信内部申请一块内存用来放置dll路径
void InjectDLL()
{
	CHAR pathStr[0x100] = { "D://" };
	// 1.获取到微信进程句柄
	DWORD PID = ProcessNameFindPID(WECHAT_PROCESS_NAME);
	if (PID == 0)
	{
		MessageBox(NULL, "没有找到微信的PID", "错误", 0);
		return;
	}

	// 2.打开进程句柄
	// params: 访问权限,是否继承该句柄,进程PID   PROCESS_ALL_ACCESS最高权限
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS,FALSE,PID);
	if (process == NULL)
	{
		MessageBox(NULL, "进程打开失败 可能权限不足 或者 关闭了应用", "错误", 0);
		return;
	}

	// 3.申请内存
	// params: 句柄,空间(null则随机分配),分配多大空间,内存类型,内存保护          mem_commit可提交     PAGE_READWRITE 可读可写
	// 如果成功返回基地址
	LPVOID dllAddr = VirtualAllocEx(process, NULL, strlen(pathStr),MEM_COMMIT,PAGE_READWRITE);
	if (dllAddr == NULL)
	{
		MessageBox(NULL, "申请内存失败", "错误", 0);
		return;
	}
	
	// 4. 写入dll地址到微信内存中去
	// params: 进程句柄,内存写入地址,写入内容,写入字节，指向变量的指针(可选)
	if (WriteProcessMemory(process, dllAddr, pathStr, strlen(pathStr), NULL) == 0)
	{
		MessageBox(NULL, "写入失败", "错误", 0);
		return;
	}

	MessageBox(NULL, "写入成功", "Success", 0);

	CHAR test[0x100] = { 0 };
	sprintf_s(test,"写入的地址为: %p",dllAddr);
	OutputDebugString(test);
}

// 3. 写入dll路径  通过远程线程执行函数  执行LoadLibaray函数加载写入路径的dll



