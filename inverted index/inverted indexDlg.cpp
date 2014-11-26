
// inverted indexDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "inverted index.h"
#include "inverted indexDlg.h"
#include "afxdialogex.h"
#include <list>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct Node
{
	CString term;
	int docID;	
}NodeData;

list<NodeData> m_list;
list<NodeData>::iterator i_list;

bool compare(NodeData& first, NodeData& second)
{
	if (first.term < second.term)
		return true;
	else
		return false;
}

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CinvertedindexDlg ��ȭ ����



CinvertedindexDlg::CinvertedindexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CinvertedindexDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CinvertedindexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CinvertedindexDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CinvertedindexDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CinvertedindexDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CinvertedindexDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CinvertedindexDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CinvertedindexDlg �޽��� ó����

BOOL CinvertedindexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CinvertedindexDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CinvertedindexDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CinvertedindexDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CinvertedindexDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.	
	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_ALLOWMULTISELECT, _T("txt ����(*.txt)|*.txt|"));
	CString token;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();		
		while (pos)
		{		
			CString Filename = dlg.GetNextPathName(pos);

			CStdioFile File;
			File.Open(Filename, CFile::modeRead);
			CString str;
			while (File.ReadString(str))
			{				
				str.Replace(_T(":"), _T(""));
				str.Replace(_T(";"), _T(""));
				str.Replace(_T("."), _T(""));
				str.Replace(_T(":"), _T(""));
				str.Replace(_T("`"), _T(""));
				str.Replace(_T("~"), _T(""));
				str.Replace(_T("!"), _T(""));
				str.Replace(_T("@"), _T(""));
				str.Replace(_T("#"), _T(""));
				str.Replace(_T("$"), _T(""));
				str.Replace(_T("%"), _T(""));
				str.Replace(_T("^"), _T(""));
				str.Replace(_T("&"), _T(""));
				str.Replace(_T("*"), _T(""));
				str.Replace(_T("("), _T(""));
				str.Replace(_T(")"), _T(""));
				str.Replace(_T("-"), _T(""));
				str.Replace(_T("_"), _T(""));
				str.Replace(_T("="), _T(""));
				str.Replace(_T("+"), _T(""));
				str.Replace(_T("|"), _T(""));
				str.Replace(_T("["), _T(""));
				str.Replace(_T("]"), _T(""));
				str.Replace(_T("{"), _T(""));
				str.Replace(_T("}"), _T(""));
				str.Replace(_T(""), _T(""));
				str.Replace(_T(","), _T(""));
				str.Replace(_T("/"), _T(""));
				str.Replace(_T("?"), _T(""));
				token += str;
				str.Replace(_T(" "), _T("|"));
				all_txt += str;
				all_txt += _T("?");
				token += _T("\r\n");
			}
			File.Close();			
		}
		//Generate postings
		all_txt.MakeLower();
		CStdioFile tokenization;
		tokenization.Open(_T("tokenization.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		token.MakeLower();
		tokenization.WriteString(token);
		tokenization.Close();
				
		CString resToken;
		int curPos = 0;
		resToken = all_txt.Tokenize(_T("|"), curPos);
		
		CStdioFile id;
		int cnt = 1;
		id.Open(_T("generate.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		
		while (resToken != "")
		{	
			char check = all_txt.GetAt(curPos - 1);
			
			CString index;			
			index.Format(_T("%d"), cnt);			
			id.WriteString(resToken + "\t" + index + "\r\n");;
			NodeData obj;
			obj.term = resToken;
			obj.docID = cnt;
			m_list.push_back(obj);
			resToken = all_txt.Tokenize(_T("| ?"), curPos);
			if (check == '?')
				cnt++;			
		}		
		id.Close();	
		
		//Sort postings
		m_list.sort(compare);
		CStdioFile sort;
		sort.Open(_T("sort.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (i_list = m_list.begin(); i_list != m_list.end(); i_list++)
		{
			CString term, index;
			term = i_list->term;
			index.Format(_T("%d"), i_list->docID);
			sort.WriteString(term + "\t" + index + "\r\n");
		}
		sort.Close();
	}

}

void CinvertedindexDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_EDIT1, _T(""));
	CStdioFile File;
	CString str, display_str;
	if (!File.Open(_T("tokenization.txt"), CFile::modeRead))
	{
		MessageBox(_T("������ ���� ���߽��ϴ�."));
	}
	else
	{
		while (File.ReadString(str))
		{
			display_str += str;
			display_str += _T("\r\n");
		}

		SetDlgItemText(IDC_EDIT1, display_str);
		File.Close();
	}
}

void CinvertedindexDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_EDIT1, _T(""));
	CStdioFile File;
	CString str, display_str;
	if (!File.Open(_T("generate.txt"), CFile::modeRead))
	{
		MessageBox(_T("������ ���� ���߽��ϴ�."));
	}
	else
	{
		while (File.ReadString(str))
		{
			display_str += str;
			display_str += _T("\r\n");
		}

		SetDlgItemText(IDC_EDIT1, display_str);
		File.Close();
	}
}

void CinvertedindexDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_EDIT1, _T(""));

	CStdioFile File;
	CString str, display_str;

	if (!File.Open(_T("sort.txt"), CFile::modeRead))
	{
		MessageBox(_T("������ ���� ���߽��ϴ�."));
	}
	else
	{
		while (File.ReadString(str))
		{
			display_str += str;
			display_str += _T("\r\n");
		}

		SetDlgItemText(IDC_EDIT1, display_str);
		File.Close();
	}
}