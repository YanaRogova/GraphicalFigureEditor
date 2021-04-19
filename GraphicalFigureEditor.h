#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"   


class CGraphicalFigureEditorApp : public CWinApp
{
public:
	CGraphicalFigureEditorApp() noexcept;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicalFigureEditorApp theApp;
