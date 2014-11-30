
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

typedef struct Posting
{
	CString term;
	int cnt = 0;
	int list[1000];
}PostingData;

list<NodeData> m_list;
list<NodeData>::iterator i_list;

list<PostingData> p_list;
list<PostingData>::iterator pi_list;
PostingData intersecting_result;

bool compare(NodeData& first, NodeData& second)
{
	if (first.term < second.term)
		return true;
	else
		return false;
}

bool Posting_compare(PostingData& first, PostingData& second)
{
	if (first.cnt > second.cnt)
		return true;
	else
		return false;
}

void intersecting(PostingData first, PostingData second)
{	
	intersecting_result.term = "";
	for (int i = 0; i < intersecting_result.cnt; i++)
	{
		intersecting_result.list[i] = 0;
	}
	intersecting_result.cnt = 0;
	int result_cnt = 0, checkpos = 0;
	for (int i = 0; i < first.cnt; i++)
	{
		for (int j = checkpos; j < second.cnt; j++)
		{
			if (first.list[i] == second.list[j])
			{
				intersecting_result.list[result_cnt] = first.list[i];
				intersecting_result.cnt++;
				result_cnt++;
				checkpos = j + 1;
				break;
			}
		}
	}
}
void orintersecting(PostingData first, PostingData second)
{
	intersecting_result.term = "";
	for (int i = 0; i < intersecting_result.cnt; i++)
	{
		intersecting_result.list[i] = 0;
	}
	intersecting_result.cnt = 0;
	int result_cnt = 0, checkpos = 0, temp_cnt = 0;
	for (int i = 0; i < first.cnt + second.cnt; i++)
	{
		if (i < first.cnt){
			intersecting_result.list[result_cnt] = first.list[i];
			intersecting_result.cnt++;
			result_cnt++;
		}
		else{
			int samecheck = 0;
			for (int j = 0; j < first.cnt; j++){
				if (first.list[j] == second.list[temp_cnt]){
					samecheck = 1;
				}				
			}
			if (samecheck != 1){
				intersecting_result.list[result_cnt] = second.list[temp_cnt];
				intersecting_result.cnt++;
				result_cnt++;
			}
			temp_cnt++;
		}
	}
	for (int i = 0; i < intersecting_result.cnt; i++){
		for (int j = 1; j < intersecting_result.cnt - i; j++){
			if (intersecting_result.list[j - 1] > intersecting_result.list[j]){
				int temp = intersecting_result.list[j];
				intersecting_result.list[j] = intersecting_result.list[j - 1];
				intersecting_result.list[j - 1] = temp;
			}
		}
	}

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
	//  DDX_Text(pDX, IDC_EDIT2, m_edit2);
}

BEGIN_MESSAGE_MAP(CinvertedindexDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CinvertedindexDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CinvertedindexDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CinvertedindexDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CinvertedindexDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CinvertedindexDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CinvertedindexDlg::OnBnClickedButton6)
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
	m_list.clear();
	p_list.clear();
	all_txt = "";
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
		
		PostingData begin;
		begin.term = _T("0");
		begin.list[0] = 0;
		begin.cnt = 0;
		p_list.push_back(begin);
		pi_list = p_list.begin();
		int m_listcnt = 0;
		for (i_list = m_list.begin(); i_list != m_list.end(); i_list++)
		{
			if (m_listcnt == m_list.size() - 1)
			{
				PostingData obj;
				obj.term = i_list->term;
				obj.list[obj.cnt] = i_list->docID;
				obj.cnt = obj.cnt++;

				p_list.push_back(obj);
				pi_list++;
				break;
			}
			//������ ���ͷ����� �ʰ����� �ʰ� ó���� �ϸ� ��
			if (i_list->term != i_list++->term)
			{				
				i_list--;
				PostingData obj;
				obj.term = i_list->term;
				obj.list[obj.cnt] = i_list->docID;
				obj.cnt = obj.cnt++;

				p_list.push_back(obj);
				pi_list++;
			}
			else
			{				
				CString nowterm;								
				i_list--;
				PostingData obj;
				obj.term = i_list->term;
				obj.list[obj.cnt] = i_list->docID;
				obj.cnt = obj.cnt++;

				p_list.push_back(obj);
				pi_list++;
				i_list++;
				nowterm = i_list->term;				
				while (i_list->term == nowterm)
				{			
					if (i_list->docID != pi_list->list[pi_list->cnt - 1])
					{
						pi_list->list[pi_list->cnt] = i_list->docID;
						pi_list->cnt = pi_list->cnt++;
						i_list++;
						m_listcnt++;
					}
					else
					{
						i_list++;
						m_listcnt++;
					}
					if (m_listcnt == m_list.size() - 1)
					{
						break;
					}
				}
				i_list--;
			}
			m_listcnt++;
		}
		p_list.pop_front();
		CStdioFile Postingfile;
		Postingfile.Open(_T("postingfile.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
		{
			CString term, index;
			term = pi_list->term;
			if (pi_list->cnt > 1)
			{
				Postingfile.WriteString(term + "\t->\t");
				for (int i = 0; i < pi_list->cnt; i++)
				{
					index.Format(_T("%d"), pi_list->list[i]);
					Postingfile.WriteString(index + " ");
				}
				Postingfile.WriteString(_T("\r\n"));
			}
			else
			{
				index.Format(_T("%d"), pi_list->list[0]);
				Postingfile.WriteString(term + "\t->\t" + index + "\r\n");
			}
		}
		Postingfile.Close();
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

void CinvertedindexDlg::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_EDIT1, _T(""));

	CStdioFile File;
	CString str, display_str;

	if (!File.Open(_T("postingfile.txt"), CFile::modeRead))
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


void CinvertedindexDlg::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString query;
	GetDlgItemText(IDC_EDIT2, query);

	CString resToken;
	CString token[100] = { 0, }, ortoken[100] = { 0, };
	int curPos = 0, token_cnt = 0, ortoken_cnt = 0;
	query.Replace(_T(":"), _T(""));
	query.Replace(_T(";"), _T(""));
	query.Replace(_T("."), _T(""));
	query.Replace(_T(":"), _T(""));
	query.Replace(_T("`"), _T(""));
	query.Replace(_T("~"), _T(""));
	query.Replace(_T("!"), _T(""));
	query.Replace(_T("@"), _T(""));
	query.Replace(_T("#"), _T(""));
	query.Replace(_T("$"), _T(""));
	query.Replace(_T("%"), _T(""));
	query.Replace(_T("^"), _T(""));
	query.Replace(_T("&"), _T(""));
	query.Replace(_T("*"), _T(""));
	query.Replace(_T("("), _T(""));
	query.Replace(_T(")"), _T(""));
	query.Replace(_T("-"), _T(""));
	query.Replace(_T("_"), _T(""));
	query.Replace(_T("="), _T(""));
	query.Replace(_T("+"), _T(""));
	query.Replace(_T("|"), _T(""));
	query.Replace(_T("["), _T(""));
	query.Replace(_T("]"), _T(""));
	query.Replace(_T("{"), _T(""));
	query.Replace(_T("}"), _T(""));
	query.Replace(_T(""), _T(""));
	query.Replace(_T(","), _T(""));
	query.Replace(_T("/"), _T(""));
	query.Replace(_T("?"), _T(""));
	query.Replace(_T(" "), _T(""));
	query.Replace(_T("AND"), _T("&"));
	query.Replace(_T("OR"), _T("|"));

	if (query.Find(_T("|")) != -1)
	{
		int orPos = 0;
		resToken = query.Tokenize(_T("|"), orPos);
		if (resToken.Find(_T("&")) != -1)
		{
			int tempPos = 0;
			CString temp = resToken, temp1;
			while (temp != "")
			{
				temp = resToken.Tokenize(_T("&"), tempPos);
				if (temp == "")
				{
					ortoken[ortoken_cnt] = temp1;
					ortoken_cnt++;
					break;
				}
				temp1 = temp;
			}
		}
		else
		{
			ortoken[ortoken_cnt] = resToken;
			ortoken_cnt++;
		}
		while (resToken != "")
		{
			resToken = query.Tokenize(_T("|"), orPos);
			if (resToken == "")
				break;
			if (resToken.Find(_T("&")) != -1)
			{
				int tempPos = 0;
				CString temp = resToken;
				temp = resToken.Tokenize(_T("&"), tempPos);
				ortoken[ortoken_cnt] = temp;
				ortoken_cnt++;
			}
			else{
				ortoken[ortoken_cnt] = resToken;
				ortoken_cnt++;
			}
		}
	}

	resToken = query.Tokenize(_T("&"), curPos);
	if (resToken.Find(_T("|")) != -1)
	{
		int tempPos = 0;
		CString temp = resToken, temp1;
		while (temp != "")
		{
			temp = resToken.Tokenize(_T("|"), tempPos);
			if (temp == "")
			{
				token[token_cnt] = temp1;
				token_cnt++;
				break;
			}
			temp1 = temp;
		}
	}
	else
	{
		token[token_cnt] = resToken;
		token_cnt++;
	}
	while (resToken != "")
	{
		resToken = query.Tokenize(_T("&"), curPos);
		if (resToken == "")
			break;
		if (resToken.Find(_T("|")) != -1)
		{
			int tempPos = 0;
			CString temp = resToken;
			temp = resToken.Tokenize(_T("|"), tempPos);
			token[token_cnt] = temp;
			token_cnt++;
		}
		else{
			token[token_cnt] = resToken;
			token_cnt++;
		}
	}

	for (int i = 0; i < token_cnt; i++)
	{
		for (int j = 0; j < ortoken_cnt; j++)
		{
			if (token[i] == ortoken[j])
			{
				token[i] = "";
			}
		}
	}

	if (token_cnt > 1 && ortoken_cnt==0)
	{
		int termcheck = 0;
		list<PostingData> in_list;
		list<PostingData>::iterator ini_list;
		for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
		{
			for (int i = 0; i < token_cnt; i++)
			{
				if (pi_list->term == token[i])
				{
					PostingData obj;
					termcheck++;
					obj.term = pi_list->term;
					obj.cnt = pi_list->cnt;
					for (int j = 0; j < obj.cnt; j++)
					{
						obj.list[j] = pi_list->list[j];
					}
					in_list.push_back(obj);
				}
			}
		}
		if (termcheck != token_cnt)
		{
			MessageBox(_T("�˻� ����� �����ϴ�."));
			SetDlgItemText(IDC_EDIT1, _T(""));
		}
		in_list.sort(Posting_compare);

		int ini_check = 0;
		for (ini_list = in_list.begin(); ini_list != in_list.end(); ini_list++)
		{
			if (ini_check == in_list.size())
				break;

			if (ini_list == in_list.begin())
			{
				PostingData obj, obj1;
				obj.term = ini_list->term;
				obj.cnt = ini_list->cnt;
				for (int i = 0; i < obj.cnt; i++)
				{
					obj.list[i] = ini_list->list[i];
				}
				ini_list++;
				ini_check++;
				obj1.term = ini_list->term;
				obj1.cnt = ini_list->cnt;
				for (int i = 0; i < obj1.cnt; i++)
				{
					obj1.list[i] = ini_list->list[i];
				}
				intersecting(obj, obj1);
			}
			else
			{
				PostingData obj;
				obj.term = ini_list->term;
				obj.cnt = ini_list->cnt;
				for (int i = 0; i < obj.cnt; i++)
				{
					obj.list[i] = ini_list->list[i];
				}

				if (intersecting_result.cnt >= obj.cnt)
				{
					intersecting(intersecting_result, obj);
				}
				else if (intersecting_result.cnt < obj.cnt)
				{
					intersecting(obj, intersecting_result);
				}
			}
			ini_check++;
		}

		if (intersecting_result.cnt == 0)
		{
			MessageBox(_T("�˻� ����� �����ϴ�."));
			SetDlgItemText(IDC_EDIT1, _T(""));			
		}
		else if (intersecting_result.cnt != 0)
		{
			CString outlist, index;
			outlist += _T("Intersection:\r\n");
			for (int i = 0; i < intersecting_result.cnt; i++)
			{
				index.Format(_T("%d"), intersecting_result.list[i]);
				outlist += index;
				if (i != intersecting_result.cnt - 1)
					outlist += _T(" -> ");
			}
			outlist += _T("\r\n\r\nSearch Result :\r\n");
			CStdioFile File;
			for (int i = 0; i < intersecting_result.cnt; i++)
			{
				CString str, display_str;
				CString filename, fileindex;
				fileindex.Format(_T("%d"), intersecting_result.list[i]);
				filename += fileindex;
				filename += _T(".txt");
				display_str += filename;
				display_str += _T("\r\n");
				if (!File.Open(filename, CFile::modeRead))
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
					File.Close();
				}
				outlist += display_str;
			}
			SetDlgItemText(IDC_EDIT1, _T(""));
			SetDlgItemText(IDC_EDIT1, outlist);
		}
	}
	else if (token_cnt == 1 && ortoken_cnt==0)
	{
		int termcheck = 0;
		for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
		{
			if (pi_list->term == token[token_cnt - 1])
			{
				termcheck = 1;				
				CString outlist, index;								
				outlist += _T("Intersection:\r\n");
				for (int i = 0; i < pi_list->cnt; i++)
				{
					index.Format(_T("%d"), pi_list->list[i]);	
					outlist += index;
					if (i != pi_list->cnt - 1)
						outlist += _T(" -> ");
				}
				outlist += _T("\r\n\r\nSearch Result :\r\n");
				CStdioFile File;				
				for (int i = 0; i < pi_list->cnt; i++)
				{
					CString str, display_str;
					CString filename, fileindex;
					fileindex.Format(_T("%d"), pi_list->list[i]);
					filename += fileindex;
					filename += _T(".txt");
					display_str += filename;
					display_str += _T("\r\n");
					if (!File.Open(filename, CFile::modeRead))
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
						File.Close();
					}
					outlist += display_str;
				}				
				SetDlgItemText(IDC_EDIT1, _T(""));
				SetDlgItemText(IDC_EDIT1, outlist);
			}
		}
		if (termcheck == 0)
		{
			MessageBox(_T("�˻� ����� �����ϴ�."));
			SetDlgItemText(IDC_EDIT1, _T(""));
		}
	}
	else if (ortoken_cnt >= 2 && token_cnt == 1)
	{
		int termcheck = 0;
		list<PostingData> in_list;
		list<PostingData>::iterator ini_list;
		for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
		{
			for (int i = 0; i < ortoken_cnt; i++)
			{
				if (pi_list->term == ortoken[i])
				{
					PostingData obj;
					termcheck++;
					obj.term = pi_list->term;
					obj.cnt = pi_list->cnt;
					for (int j = 0; j < obj.cnt; j++)
					{
						obj.list[j] = pi_list->list[j];
					}
					in_list.push_back(obj);
				}
			}
		}
		if (termcheck != ortoken_cnt)
		{
			MessageBox(_T("�˻� ����� �����ϴ�."));
			SetDlgItemText(IDC_EDIT1, _T(""));
		}
		in_list.sort(Posting_compare);

		int ini_check = 0;
		for (ini_list = in_list.begin(); ini_list != in_list.end(); ini_list++)
		{
			if (ini_check == in_list.size())
				break;

			if (ini_list == in_list.begin())
			{
				PostingData obj, obj1;
				obj.term = ini_list->term;
				obj.cnt = ini_list->cnt;
				for (int i = 0; i < obj.cnt; i++)
				{
					obj.list[i] = ini_list->list[i];
				}
				ini_list++;
				ini_check++;
				obj1.term = ini_list->term;
				obj1.cnt = ini_list->cnt;
				for (int i = 0; i < obj1.cnt; i++)
				{
					obj1.list[i] = ini_list->list[i];
				}
				orintersecting(obj, obj1);
			}
			else
			{
				PostingData obj;
				obj.term = ini_list->term;
				obj.cnt = ini_list->cnt;
				for (int i = 0; i < obj.cnt; i++)
				{
					obj.list[i] = ini_list->list[i];
				}

				if (intersecting_result.cnt >= obj.cnt)
				{
					orintersecting(intersecting_result, obj);
				}
				else if (intersecting_result.cnt < obj.cnt)
				{
					orintersecting(obj, intersecting_result);
				}
			}
			ini_check++;
		}

		if (intersecting_result.cnt == 0)
		{
			MessageBox(_T("�˻� ����� �����ϴ�."));
			SetDlgItemText(IDC_EDIT1, _T(""));
		}
		else if (intersecting_result.cnt != 0)
		{
			CString outlist, index;
			outlist += _T("Intersection:\r\n");
			for (int i = 0; i < intersecting_result.cnt; i++)
			{
				if (intersecting_result.list[i] != 0){
					index.Format(_T("%d"), intersecting_result.list[i]);
					outlist += index;
					if (i != intersecting_result.cnt - 1)
						outlist += _T(" -> ");
				}
			}
			outlist += _T("\r\n\r\nSearch Result :\r\n");
			CStdioFile File;
			for (int i = 0; i < intersecting_result.cnt; i++)
			{
				if (intersecting_result.list[i] != 0){
					CString str, display_str;
					CString filename, fileindex;
					fileindex.Format(_T("%d"), intersecting_result.list[i]);
					filename += fileindex;
					filename += _T(".txt");
					display_str += filename;
					display_str += _T("\r\n");
					if (!File.Open(filename, CFile::modeRead))
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
						File.Close();
					}
					outlist += display_str;
				}
				SetDlgItemText(IDC_EDIT1, _T(""));
				SetDlgItemText(IDC_EDIT1, outlist);
			}
		}
	}
	else if (token_cnt >= 2 && ortoken_cnt >= 2)
	{
		if (ortoken_cnt != 0)
		{
			int termcheck = 0;
			list<PostingData> in_list;
			list<PostingData>::iterator ini_list;
			for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
			{
				for (int i = 0; i < ortoken_cnt; i++)
				{
					if (pi_list->term == ortoken[i])
					{
						PostingData obj;
						termcheck++;
						obj.term = pi_list->term;
						obj.cnt = pi_list->cnt;
						for (int j = 0; j < obj.cnt; j++)
						{
							obj.list[j] = pi_list->list[j];
						}
						in_list.push_back(obj);
					}
				}
			}
			in_list.sort(Posting_compare);

			int ini_check = 0;
			for (ini_list = in_list.begin(); ini_list != in_list.end(); ini_list++)
			{
				if (ini_check == in_list.size())
					break;

				if (ini_list == in_list.begin())
				{
					PostingData obj, obj1;
					obj.term = ini_list->term;
					obj.cnt = ini_list->cnt;
					for (int i = 0; i < obj.cnt; i++)
					{
						obj.list[i] = ini_list->list[i];
					}
					ini_list++;
					ini_check++;
					obj1.term = ini_list->term;
					obj1.cnt = ini_list->cnt;
					for (int i = 0; i < obj1.cnt; i++)
					{
						obj1.list[i] = ini_list->list[i];
					}
					orintersecting(obj, obj1);
				}
				else
				{
					PostingData obj;
					obj.term = ini_list->term;
					obj.cnt = ini_list->cnt;
					for (int i = 0; i < obj.cnt; i++)
					{
						obj.list[i] = ini_list->list[i];
					}

					if (intersecting_result.cnt >= obj.cnt)
					{
						orintersecting(intersecting_result, obj);
					}
					else if (intersecting_result.cnt < obj.cnt)
					{
						orintersecting(obj, intersecting_result);
					}
				}
				ini_check++;
			}			
		}
		if (token_cnt != 0)
		{
			int termcheck = 0;
			list<PostingData> in_list;
			list<PostingData>::iterator ini_list;
			for (pi_list = p_list.begin(); pi_list != p_list.end(); pi_list++)
			{
				for (int i = 0; i < token_cnt; i++)
				{
					if (pi_list->term == token[i])
					{
						PostingData obj;
						termcheck++;
						obj.term = pi_list->term;
						obj.cnt = pi_list->cnt;
						for (int j = 0; j < obj.cnt; j++)
						{
							obj.list[j] = pi_list->list[j];
						}
						in_list.push_back(obj);
					}
				}
			}
			in_list.sort(Posting_compare);

			int ini_check = 0;
			for (ini_list = in_list.begin(); ini_list != in_list.end(); ini_list++)
			{
				if (ini_check == in_list.size())
					break;

				PostingData obj;
				obj.term = ini_list->term;
				obj.cnt = ini_list->cnt;
				for (int i = 0; i < obj.cnt; i++)
				{
					obj.list[i] = ini_list->list[i];
				}

				if (intersecting_result.cnt >= obj.cnt)
				{
					intersecting(intersecting_result, obj);
				}
				else if (intersecting_result.cnt < obj.cnt)
				{
					intersecting(obj, intersecting_result);
				}
				ini_check++;
			}

			if (intersecting_result.cnt == 0)
			{
				MessageBox(_T("�˻� ����� �����ϴ�."));
				SetDlgItemText(IDC_EDIT1, _T(""));
			}
			else if (intersecting_result.cnt != 0)
			{
				CString outlist, index;
				outlist += _T("Intersection:\r\n");
				for (int i = 0; i < intersecting_result.cnt; i++)
				{
					if (intersecting_result.list[i] != 0){
						index.Format(_T("%d"), intersecting_result.list[i]);
						outlist += index;
						if (i != intersecting_result.cnt - 1)
							outlist += _T(" -> ");
					}
				}
				outlist += _T("\r\n\r\nSearch Result :\r\n");
				CStdioFile File;
				for (int i = 0; i < intersecting_result.cnt; i++)
				{
					if (intersecting_result.list[i] != 0){
						CString str, display_str;
						CString filename, fileindex;
						fileindex.Format(_T("%d"), intersecting_result.list[i]);
						filename += fileindex;
						filename += _T(".txt");
						display_str += filename;
						display_str += _T("\r\n");
						if (!File.Open(filename, CFile::modeRead))
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
							File.Close();
						}
						outlist += display_str;
					}
					SetDlgItemText(IDC_EDIT1, _T(""));
					SetDlgItemText(IDC_EDIT1, outlist);
				}
			}
		}
	}
}

BOOL CinvertedindexDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
