// index.cpp: 实现文件
//

#include "pch.h"
#include "hook1.h"
#include "index.h"
#include "afxdialogex.h"
#include "wx_tools.h"


// index 对话框

IMPLEMENT_DYNAMIC(index, CDialogEx)

index::index(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, wx_id(_T(""))
	, wx_zh(_T(""))
	, wx_tx(_T(""))
	, wx_os(_T(""))
{

}

index::~index()
{
}

void index::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, wx_id);
	DDX_Text(pDX, IDC_EDIT2, wx_zh);
	DDX_Text(pDX, IDC_EDIT3, wx_tx);
	DDX_Text(pDX, IDC_EDIT4, wx_phone);
	DDX_Text(pDX, IDC_EDIT5, wx_os);
}


BEGIN_MESSAGE_MAP(index, CDialogEx)
	ON_BN_CLICKED(IDOK, &index::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &index::OnBnClickedCancel)
END_MESSAGE_MAP()


// index 消息处理程序


void index::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();

	wx_id = wx.GetWxID();
	wx_os = wx.GetOS();
	wx_phone = wx.GetPhoneNumber();
	wx_tx = wx.GetAvatar();
	wx_zh = wx.GetUserName();
	UpdateData(FALSE);
}


void index::OnBnClickedCancel()
{
	UpdateData(TRUE);
	wx.UpdataWxID(wx_id.GetBuffer(wx_id.GetLength()));
}
