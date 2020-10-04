#pragma once


// CDialogShow 对话框

class CDialogShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogShow)

public:
	CDialogShow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogShow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit csp1;
	CEdit csp2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
	CString ssr1;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2xx();
};
