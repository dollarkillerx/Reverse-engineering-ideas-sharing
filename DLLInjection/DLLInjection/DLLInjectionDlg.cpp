
// DLLInjectionDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DLLInjection.h"
#include "DLLInjectionDlg.h"
#include "afxdialogex.h"
#include "injection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDLLInjectionDlg 对话框



CDLLInjectionDlg::CDLLInjectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLLINJECTION_DIALOG, pParent)
	, dll_path(_T(""))
	, target(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDLLInjectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DLL, dll_path);
	DDX_Text(pDX, IDC_EDIT1, target);
}

BEGIN_MESSAGE_MAP(CDLLInjectionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_DROPFILES()
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_Openfile, &CDLLInjectionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDLLInjectionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDLLInjectionDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDLLInjectionDlg 消息处理程序

BOOL CDLLInjectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDLLInjectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDLLInjectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDLLInjectionDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}


void CDLLInjectionDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	// CDialogEx::OnClose();
}


void CDLLInjectionDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(TEXT("IN"));
	// CDialogEx::OnDropFiles(hDropInfo);
}


void CDLLInjectionDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码

	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("DLL(*.dll)|*.dll|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("dll"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		// SetDlgItemText(IDC_Openfile, strFilePath);
		dll_path = strFilePath;
		UpdateData(FALSE);
	}
}


void CDLLInjectionDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	DWORD pid = ProcessNameFindPID(target.GetBuffer(target.GetLength()));

	/*TCHAR str[20];
	wsprintf(str, "%d", pid);
	MessageBox(str);*/
	if (pid == 0) {
		MessageBox(target + "  进程不存在");
		return;
	}

	if (dll_path == "")
	{
		MessageBox("DLL 未选择!!!");
		return;
	}

	if (InjectDLL(pid, dll_path.GetBuffer(dll_path.GetLength())))
	{
		MessageBox("DLL注入成功");
	}
}

void CDLLInjectionDlg::OnBnClickedCancel()
{
	UpdateData(TRUE);
	DWORD pid = ProcessNameFindPID(target.GetBuffer(target.GetLength()));

	/*TCHAR str[20];
	wsprintf(str, "%d", pid);
	MessageBox(str);*/
	if (pid == 0) {
		MessageBox(target + "  进程不存在");
		return;
	}

	if (dll_path == "")
	{
		MessageBox("DLL 未选择!!!");
		return;
	}
	
	if (UnInjectDll(pid, dll_path.GetBuffer(dll_path.GetLength())))
	{
		MessageBox("DLL卸载成功");
	}
}
