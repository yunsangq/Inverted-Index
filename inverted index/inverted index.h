
// inverted index.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CinvertedindexApp:
// �� Ŭ������ ������ ���ؼ��� inverted index.cpp�� �����Ͻʽÿ�.
//

class CinvertedindexApp : public CWinApp
{
public:
	CinvertedindexApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CinvertedindexApp theApp;