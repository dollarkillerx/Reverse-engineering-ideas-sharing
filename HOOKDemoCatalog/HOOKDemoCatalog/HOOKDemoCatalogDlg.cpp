
// HOOKDemoCatalogDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HOOKDemoCatalog.h"
#include "HOOKDemoCatalogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHOOKDemoCatalogDlg 对话框



CHOOKDemoCatalogDlg::CHOOKDemoCatalogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOOKDEMOCATALOG_DIALOG, pParent)
	, deposit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHOOKDemoCatalogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, deposit);
	DDV_MinMaxInt(pDX, deposit, 0, INT_MAX);
}

BEGIN_MESSAGE_MAP(CHOOKDemoCatalogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHOOKDemoCatalogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHOOKDemoCatalogDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CHOOKDemoCatalogDlg 消息处理程序

BOOL CHOOKDemoCatalogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHOOKDemoCatalogDlg::OnPaint()
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
HCURSOR CHOOKDemoCatalogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int deposit_fun(int i, int p)
{
	i += p;
	return i;
}

void CHOOKDemoCatalogDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
	deposit = deposit_fun(deposit,100);
	UpdateData(FALSE);
	MessageBox(TEXT("存款成功"));
}

void CHOOKDemoCatalogDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnCancel();
	if (deposit < 100)
	{
		MessageBox(TEXT("余额不足  被保安吊打"));
		return;
	}
	deposit -= 100;
	UpdateData(FALSE);
}
