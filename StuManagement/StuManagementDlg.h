
// StuManagementDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CStuManagementDlg �Ի���
class CStuManagementDlg : public CDialogEx
{
// ����
public:
	CStuManagementDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LISTC;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	// ѧ�ű༭��ĳ�Ա����
	int Edit_id;
	// ��ѧ�ɼ��༭���Ա����
	int Edit_math;
	// ������Ƴɼ��༭��ĳ�Ա����
	int Edit_cpp;
	// �����༭��ĳ�Ա����
	CString Edit_name;
	afx_msg void OnBnClickedButtonread();
	afx_msg void OnBnClickedButtonmod();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	int Radiomale;
};
