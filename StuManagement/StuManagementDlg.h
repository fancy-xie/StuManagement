
// StuManagementDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CStuManagementDlg 对话框
class CStuManagementDlg : public CDialogEx
{
// 构造
public:
	CStuManagementDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LISTC;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	// 学号编辑框的成员变量
	int Edit_id;
	// 数学成绩编辑框成员变量
	int Edit_math;
	// 程序设计成绩编辑框的成员变量
	int Edit_cpp;
	// 姓名编辑框的成员变量
	CString Edit_name;
	afx_msg void OnBnClickedButtonread();
	afx_msg void OnBnClickedButtonmod();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	int Radiomale;
};
