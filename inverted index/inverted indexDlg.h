
// inverted indexDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
// CinvertedindexDlg ��ȭ ����
class CinvertedindexDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CinvertedindexDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INVERTEDINDEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

extern CString all_txt;