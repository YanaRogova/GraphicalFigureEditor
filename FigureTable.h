#pragma once
#include <afxcview.h>

#include "EditorView.h"

class CEditorView;

class CFigureTable : public CListCtrl
{
	// DECLARE_DYNAMIC virtual is OK here - CWnd has DECLARE_DYNAMIC
	DECLARE_DYNAMIC(CFigureTable)
public:
	CFigureTable();
	virtual ~CFigureTable();

	//friend class CEditorView;
	void UpdateListView(CEditorView* pView);

private:
	CListCtrl m_List2;
};

