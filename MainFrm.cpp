
#include "pch.h"
#include "framework.h"
#include "GraphicalFigureEditor.h"
#include "MainFrm.h"
#include "DlgResize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WINDOW_SIZE 0.75
#define ERROR_RESULT -1
#define SUCCESS_RESULT 0


IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnNew)
	ON_COMMAND(ID_PICTURE_RESIZE, OnResize)
	ON_COMMAND(ID_APP_EXIT, OnClose)
	ON_COMMAND(IDD_ABOUTBOX, OnAppAbout)
END_MESSAGE_MAP()

CMainFrame::CMainFrame() noexcept
{
	m_bFileExist = false;
	m_bDeletePicture = false;
	m_bCloseProgram = false;
	m_sFileName = L"New picture";
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	int nxSize = static_cast<int>(GetSystemMetrics(SM_CXMAXIMIZED) * WINDOW_SIZE);
	int nySize = static_cast<int>(GetSystemMetrics(SM_CYMAXIMIZED) * WINDOW_SIZE);
	cs.cx = nxSize;
	cs.cy = nySize;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_MAXIMIZE
		| WS_SYSMENU | WS_OVERLAPPEDWINDOW;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == ERROR_RESULT)
		return ERROR_RESULT;

	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW,
		CRect(), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Failed to create view window\n");
		return ERROR_RESULT;
	}

	HICON hIcon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	
	SetIcon(hIcon, FALSE);
	SetIcon(hIcon, TRUE);
	return SUCCESS_RESULT;
}

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndView.SetFocus();
}

void CMainFrame::OnFileSaveAs()
{
	m_bFileExist = false;
	OnFileSave();
}

void CMainFrame::OnFileSave()
{
	CFileDialog dlgSaveAs(FALSE, L"gfe", m_sFileName, OFN_OVERWRITEPROMPT | OFN_NOVALIDATE,
		L"Graghical figure editor (*.gfe)|*.gfe|");

	if (m_bFileExist == false)
	{
		if (dlgSaveAs.DoModal() == IDOK)
		{
			if (!m_bFileExist)
			{
				m_bFileExist = true;
			}
			m_sFileName = dlgSaveAs.GetPathName();
			m_wndView.SaveFile(m_sFileName);

			if (m_bDeletePicture == true)
			{
				m_wndView.NewFile();
			}

			if (m_bCloseProgram == true)
			{
				CFrameWnd::OnClose();
			}
		}
	}
	else
	{
		m_sFileName = dlgSaveAs.GetPathName();
		m_wndView.SaveFile(m_sFileName);
	}
	
	m_bDeletePicture = false;
	m_bCloseProgram = false;
}

void CMainFrame::OnFileOpen()
{
	int result;
	if (m_wndView.PictureNotSaved())
	{
		result = AfxMessageBox(L"Do you want to save changes to the current file?", MB_YESNO);
		if (result == IDYES)
		{
			m_bFileExist = true;
			OnFileSave();
		}
	}

	CFileDialog dlgOpen(TRUE, L"gfe", NULL, OFN_OVERWRITEPROMPT | OFN_NOVALIDATE,
		L"Graghical figure editor (*.gfe)|*.gfe|");

	result = dlgOpen.DoModal();
	if (result == IDOK)
	{
		CString strFileName = dlgOpen.GetPathName();
		m_wndView.OpenFile(strFileName);
	}
}

void CMainFrame::OnNew()
{
	int result;
	if (m_wndView.PictureNotSaved())
	{
		result = AfxMessageBox(L"Do you want to save changes to the current file?", MB_YESNO);
		if (result == IDYES)
		{
			m_bDeletePicture = true;
			OnFileSave();
			m_bFileExist = false;
		}
		else
			m_wndView.NewFile();
	}
	else
		m_wndView.NewFile();
}

void CMainFrame::OnResize()
{
	CDlgResize dlgResize(m_wndView.GetWidth(), m_wndView.GetHeight());
	int result = dlgResize.DoModal();
	if (result == IDOK)
	{
		m_wndView.SetWidthAndHeight(dlgResize.m_nWidth, dlgResize.m_nHeight);
		CRect rect;
		m_wndView.GetWindowRect(rect);
		m_wndView.OnSize(NULL, rect.Width(), rect.Height());
	}
}

void CMainFrame::OnClose()
{
	int result;
	if (m_wndView.PictureNotSaved())
	{
		result = AfxMessageBox(L"Do you want to save changes to the current file?", MB_YESNO);
		if (result == IDYES)
		{
			m_bCloseProgram = true;
			OnFileSave();
		}
		else
			CFrameWnd::OnClose();
	}
	else
		CFrameWnd::OnClose();
}

void CMainFrame::OnAppAbout()
{
	CDialogEx aboutDlg(IDD_ABOUTBOX);
	aboutDlg.DoModal();
}

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

