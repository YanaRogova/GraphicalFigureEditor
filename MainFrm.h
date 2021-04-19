
#pragma once
#include "EditorView.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame() noexcept;
	virtual ~CMainFrame();

protected: 
	DECLARE_DYNAMIC(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnNew();
	afx_msg void OnResize();
	DECLARE_MESSAGE_MAP()

public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CEditorView    m_wndView;
};


