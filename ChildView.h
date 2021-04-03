
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "GraphicalWindow.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();


protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// Implementation
public:
	virtual ~CChildView();
	int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void CChildView::OnButtonRect();
	afx_msg void CChildView::OnButtonEllipse();
	afx_msg void CChildView::OnCBoxPenStyles();
	afx_msg void CChildView::OnEditPenWidth();
	afx_msg void CChildView::OnButtonPenColor();
	afx_msg void CChildView::OnButtonBrushColor();
	afx_msg void CChildView::OnCBoxBrushStyles();
	afx_msg void CChildView::OnButtonNormalizeFigure();
	afx_msg void CChildView::OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void CChildView::OnEditFigureAngle();
	afx_msg void CChildView::OnButtonLeftRotate();
	afx_msg void CChildView::OnButtonRightRotate();
	afx_msg void CChildView::OnButtonMove();
	afx_msg void CChildView::OnButtonTriangle();
	COLORREF CChildView::GetColor();

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

};

