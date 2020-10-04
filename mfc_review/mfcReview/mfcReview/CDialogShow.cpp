// CDialogShow.cpp: 实现文件
//

#include "pch.h"
#include "mfcReview.h"
#include "CDialogShow.h"
#include "afxdialogex.h"


// CDialogShow 对话框

IMPLEMENT_DYNAMIC(CDialogShow, CDialogEx)

CDialogShow::CDialogShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW, pParent)
	, ssr1(_T(""))
{

}

CDialogShow::~CDialogShow()
{
}

void CDialogShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SP1, csp1);
	DDX_Control(pDX, IDC_SP2, csp2);
	DDX_Text(pDX, IDC_EDIT3, ssr1);
}


BEGIN_MESSAGE_MAP(CDialogShow, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogShow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogShow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogShow::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2XX, &CDialogShow::OnBnClickedButton2xx)
END_MESSAGE_MAP()


// CDialogShow 消息处理程序


void CDialogShow::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1;
	csp1.GetWindowTextW(str1);
	csp2.SetWindowTextW(str1);
}


void CDialogShow::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	// exit(0); // 退出整个程序

	CDialogShow::OnOK();  // 退出当前程序
	// CDialogShow::OnCancel();
}


void CDialogShow::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDialogShow::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 利用关联Value值类型的方式 设置内容
	ssr1 = TEXT("我的天啊");
	// 更新数据到控件中
	UpdateData(FALSE);
}

void CDialogShow::OnBnClickedButton2xx()
{
	// TODO: 在此添加控件通知处理程序代码

	// 将控件内容 同步到变量中
	UpdateData(TRUE);
	MessageBoxW(ssr1);
}
