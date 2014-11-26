
// inverted indexDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CinvertedindexDlg 대화 상자



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


// CinvertedindexDlg 메시지 처리기

BOOL CinvertedindexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CinvertedindexDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CinvertedindexDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CinvertedindexDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CFileDialog dlg(TRUE, _T("txt"), _T("*.txt"), OFN_ALLOWMULTISELECT, _T("txt 파일(*.txt)|*.txt|"));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_EDIT1, _T(""));
	CStdioFile File;
	CString str, display_str;
	if (!File.Open(_T("tokenization.txt"), CFile::modeRead))
	{
		MessageBox(_T("파일을 열지 못했습니다."));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_EDIT1, _T(""));
	CStdioFile File;
	CString str, display_str;
	if (!File.Open(_T("generate.txt"), CFile::modeRead))
	{
		MessageBox(_T("파일을 열지 못했습니다."));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_EDIT1, _T(""));

	CStdioFile File;
	CString str, display_str;

	if (!File.Open(_T("sort.txt"), CFile::modeRead))
	{
		MessageBox(_T("파일을 열지 못했습니다."));
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