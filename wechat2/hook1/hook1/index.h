#pragma once
#include <afxdialogex.h>

#include "wx_tools.h"


// index 对话框

class index : public CDialogEx
{
	DECLARE_DYNAMIC(index)

public:
	index(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~index();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString wx_id;
	CString wx_zh;
	CString wx_tx;
	CString wx_phone;
	CString wx_os;
	Wx wx;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
