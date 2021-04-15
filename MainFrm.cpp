
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "GraphicalFigureEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_SAVE, OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	int nxSize = static_cast<int>(GetSystemMetrics(SM_CXMAXIMIZED) * 0.75);
	int nySize = static_cast<int>(GetSystemMetrics(SM_CYMAXIMIZED) * 0.75);

	cs.cx = nxSize;
	cs.cy = nySize;
	
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_MAXIMIZE
		 | WS_SYSMENU | WS_OVERLAPPEDWINDOW;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnFileSaveAs()
{
	CFileDialog dlgSaveAs(FALSE, L"gde", L"New picture", OFN_OVERWRITEPROMPT | OFN_NOVALIDATE,
		L"Graghical figure editor (*.gde)|*.gde|");
	int result = dlgSaveAs.DoModal();
	
	CString strFileName = dlgSaveAs.GetPathName();
	m_wndView.SaveFile(strFileName);
}

void CMainFrame::OnFileOpen()
{
	CFileDialog dlgOpen(TRUE, L"gde", NULL, OFN_OVERWRITEPROMPT | OFN_NOVALIDATE,
		L"Graghical figure editor (*.gde)|*.gde|");
	int result = dlgOpen.DoModal();

	CString strFileName = dlgOpen.GetPathName();
	m_wndView.OpenFile(strFileName);
}