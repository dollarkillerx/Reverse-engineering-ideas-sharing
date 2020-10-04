#pragma once


// CDialogExec 对话框

class CDialogExec : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExec)

public:
	CDialogExec(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogExec();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXEC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic sb1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_btn2;
};
