
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "afxcview.h"
#include "GraphicalWindow.h"

// CChildView window
class CMyListView : public CListView
{
public:
	CMyListView();
	virtual ~CMyListView();
	void OnInitialUpdate() override;
};




class CEditorView : public CWnd
{
// Construction
public:
	CEditorView();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// Implementation
public:
	virtual ~CEditorView();
	afx_msg int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void CEditorView::OnSize(UINT nType, int cx, int cy);
	afx_msg void CEditorView::OnButtonRect();
	afx_msg void CEditorView::OnButtonEllipse();
	afx_msg void CEditorView::OnCBoxPenStyles();
	afx_msg void CEditorView::OnEditPenWidth();
	afx_msg void CEditorView::OnButtonPenColor();
	afx_msg void CEditorView::OnButtonBrushColor();
	afx_msg void CEditorView::OnCBoxBrushStyles();
	afx_msg void CEditorView::OnButtonNormalizeFigure();
	afx_msg void CEditorView::OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void CEditorView::OnEditFigureAngle();
	afx_msg void CEditorView::OnEditName();
	afx_msg void CEditorView::OnEditID();
	afx_msg void CEditorView::OnButtonLeftRotate();
	afx_msg void CEditorView::OnButtonRightRotate();
	afx_msg void CEditorView::OnButtonMove();
	afx_msg void CEditorView::OnButtonDelete();
	afx_msg void CEditorView::OnButtonTriangle();
	afx_msg void OnNotify(NMHDR* pNotifyStruct, LRESULT* result);
	COLORREF CEditorView::GetColor();
	void UpdateListView();
	void MoveFigureElement(int nCurrentPosition, int nNewPosition);
	void CEditorView::OnInitialUpdate();

	int CEditorView::SetName();


	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	CButton m_ButRect;
	CButton m_ButEllipse;
	CGraphicalWindow m_GraphicalWindow;
	CComboBox m_CBoxPenStyles;
	CComboBox m_CBoxBrushStyles;
	CEdit m_EditPenWidth;
	CEdit m_EditFigureAngle;
	CEdit m_EditName;
	CEdit m_EditID;
	CButton m_ButChousePenColor;
	CButton m_ButChouseBrushColor;
	CButton m_ButNormalizeFigure;
	CButton m_ButLeftRotate;
	CButton m_ButRightRotate;
	CButton m_ButMove;
	CButton m_ButDelete;
	CButton m_ButTriangle;
	std::vector<CString> PenStylesNames;
	std::vector<CString> PenStylesNamesEx;
	std::vector<CString> BrushStylesNames;
	CListCtrl m_List;
	CStatic m_StaticAngle;
	CStatic m_StaticPenType;
	CStatic m_StaticPenWidth;
	CStatic m_StaticBrush;
	CStatic m_StaticName;
	CStatic m_StaticNameWarning;
	CStatic m_StaticID;
	CStatic m_StaticIDWarning;

	//CMyListView m_List;
	//CListView m;
};



