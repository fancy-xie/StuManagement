
// StuManagement.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStuManagementApp: 
// �йش����ʵ�֣������ StuManagement.cpp
//

class CStuManagementApp : public CWinApp
{
public:
	CStuManagementApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStuManagementApp theApp;
