// CDialogExec.cpp: 实现文件
//

#include "pch.h"
#include "mfcReview.h"
#include "CDialogExec.h"
#include "afxdialogex.h"


// CDialogExec 对话框

IMPLEMENT_DYNAMIC(CDialogExec, CDialogEx)

CDialogExec::CDialogExec(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXEC, pParent)
{

}

CDialogExec::~CDialogExec()
{
}

void CDialogExec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST1, sb1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
}


BEGIN_MESSAGE_MAP(CDialogExec, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogExec::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogExec::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialogExec 消息处理程序


void CDialogExec::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	sb1.SetWindowTextW(TEXT("呵呵呵"));
}


void CDialogExec::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	sb1.GetWindowTextW(str);
	MessageBox(str);

	m_btn2.SetWindowTextW(TEXT("已经弹出了"));
	m_btn2.EnableWindow(FALSE); // 设置禁用
}
