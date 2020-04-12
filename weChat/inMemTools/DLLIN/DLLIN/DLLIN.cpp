// DLLIN.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "DLLIN.h"
#include <Windows.h>
#include "resource.h"

INT_PTR CALLBACK Dlgproc(
	HWND Arg1,
	UINT Arg2,
	WPARAM Arg3,
	LPARAM Arg4
);
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
			MessageBox(NULL, "in", "", 0);
		}
	}
	
	return FALSE;
}






