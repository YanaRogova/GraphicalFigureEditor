#pragma once
#include <afxwin.h>
#include <vector>
#include "Figure.h"
#include "Rectangle.h"
//#include "Triangle.h"
//class CGraphicalWindow : public CWnd
//{
//protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//
//	DECLARE_MESSAGE_MAP()
//public:
//	CGraphicalWindow();
//	virtual ~CGraphicalWindow();
//	afx_msg void OnPaint();
//};




class CGraphicalWindow : public CStatic
{
public:

	CGraphicalWindow();
	afx_msg void CGraphicalWindow::OnPaint();
	virtual CGraphicalWindow::~CGraphicalWindow();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR time);
	afx_msg BOOL CGraphicalWindow::OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void CGraphicalWindow::SetFigureType(int nFigureType);
protected:

	DECLARE_MESSAGE_MAP()
	//void CGraphicalWindow::GetCoordinates(CPoint point);
	//void CGraphicalWindow::DrawRectangle();
	
	std::vector<int> PenStyles;
	std::vector<int> BrushStyles;
public: 
	int m_nFigurePenStyles;
	int m_nFigureBrushStyles;
	int m_nFigurePenWidth;
	COLORREF m_crFigurePenColor;
	COLORREF m_crFigureBrushColor;
	std::vector <CFigure *> m_Figure;
	bool m_bLButtonUp;

protected:
	std::vector<CPoint> m_pRectCoordinates;
	bool m_bPaintNow;
	bool m_bLButtonDown;
	int m_nFigureType;
		
};

