#pragma once
#include <exception>
#include <Windows.h>
#include <TlHelp32.h>

// 通过进程名称获取进程ID   
// Params: 进程名称
// Return: 进程ID  (不存在返回0)
DWORD ProcessNameFindPID(char* ProcessName)
{
	// 获取当前系统进程快照 
	HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	// 找到名称相同的
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	do
	{
		// th32ProcessID 进程ID
		// szExeFile 进程名称
		if (strcmp(ProcessName, processInfo.szExeFile) == 0)
		{
			return processInfo.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &processInfo));

	return 0;
}

// 注入
// Params: 进程ID,dll地址
bool InjectDLL(DWORD dwProcessId, char* dllPath)
{
	try
	{
		// 获取进程句柄
		// params: 进程访问权限(PROCESS_ALL_ACCESS全部的),是否继承句柄FALSE，进程ID,
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

		// 远程申请一块内存
		// params: 远程地址,内存起始地址,大小(+1防止溢出),内存分配类型,分配页面区域的内存保护
		// 申请成功返回其内存地址
		SIZE_T paramsLen = strlen(dllPath) + 1;
		LPVOID paramsAddress = VirtualAllocEx(hProcess, NULL, paramsLen, MEM_COMMIT, PAGE_READWRITE);
		if (paramsAddress == nullptr)
		{
			throw "申请内存失败";
		}

		// 写内存
		// params： 进程地址,参数地址,数据,长度,NULL
		WriteProcessMemory(hProcess, paramsAddress, dllPath, paramsLen, NULL);

		// 获取LoadLibrary 函数地址
		HMODULE load_addr = LoadLibrary(TEXT("Kernel32.dll"));
		LPTHREAD_START_ROUTINE load_libaray_addr = (LPTHREAD_START_ROUTINE)GetProcAddress(load_addr, "LoadLibraryA");


		// params: 进程句柄,为NULL默认安全描述符,堆栈初始大小0默认,函数指针，函数参数的指针，运行状态0立即运行，远程指向函数返回指针
		HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, load_libaray_addr, paramsAddress, 0, NULL);
		if (hThread == nullptr)
		{
			throw "线程创建失败";
		}
		// 等待线程事件结束
		WaitForSingleObject(hThread, 2000);

		// 释放申请的虚拟内存空间
/*
	 【释放申请的虚拟内存空间】
  参数1：目标进程的句柄。该句柄必须拥有 PROCESS_VM_OPERATION 权限
  参数2：指向要释放的虚拟内存空间首地址的指针
  参数3：虚拟内存空间的字节数
  参数4：MEM_DECOMMIT仅标示内存空间不可用，内存页还将存在。
		 MEM_RELEASE这种方式很彻底，完全回收。
  */
		VirtualFreeEx(hProcess, paramsAddress, paramsLen, MEM_DECOMMIT);
		// 回收资源
		CloseHandle(hThread);
		CloseHandle(hProcess);

	}
	catch (std::exception& e)
	{
		MessageBox(NULL, TEXT("DLL注入异常"), TEXT("ERRO"), MB_OK);
		return false;
	}

	return true;
}

// 卸载DLL
// params: 进程ID，dllpath
bool UnInjectDll(DWORD dwProcessId, char* dllPath)
{
	try
	{
		// get process handle
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
		if (hProcess == nullptr)
		{
			throw "Open Process Error";
		}

		HMODULE freeLibrary = LoadLibrary(TEXT("Kernel32.dll"));
		LPTHREAD_START_ROUTINE freeLibraryAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(freeLibrary, "FreeLibrary");
		// params: 进程句柄,为NULL默认安全描述符,堆栈初始大小0默认,函数指针，函数参数的指针，运行状态0立即运行，远程指向函数返回指针
		HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, freeLibraryAddr, NULL, 0, NULL);
		if (hThread == nullptr)
		{
			throw "线程创建失败";
		}
		// 等待线程事件结束
		WaitForSingleObject(hThread, 2000);
		// 回收资源
		CloseHandle(hThread);
		CloseHandle(hProcess);
	}
	catch (std::exception& e)
	{
		MessageBox(NULL, TEXT("DLL卸载异常"), TEXT("ERRO"), MB_OK);
		return false;
	}

	return true;
}
