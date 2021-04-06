
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "afxcview.h"
#include "GraphicalWindow.h"

// CChildView window

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
	int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct);
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
	afx_msg void CEditorView::OnButtonLeftRotate();
	afx_msg void CEditorView::OnButtonRightRotate();
	afx_msg void CEditorView::OnButtonMove();
	afx_msg void CEditorView::OnButtonTriangle();
	COLORREF CEditorView::GetColor();
	void UpdateListView();
	void MoveFigureElement(int nCurrentPosition, int nNewPosition);
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
	CButton m_ButChousePenColor;
	CButton m_ButChouseBrushColor;
	CButton m_ButNormalizeFigure;
	CButton m_ButLeftRotate;
	CButton m_ButRigthRotate;
	CButton m_ButMove;
	CButton m_ButTriangle;
	std::vector<CString> PenStylesNames;
	std::vector<CString> PenStylesNamesEx;
	std::vector<CString> BrushStylesNames;
	CStatic m_DrawingSpace;
	CListCtrl m_List;
	//CListView m;
};

