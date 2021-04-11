#pragma once
#include <afxwin.h>
#include <vector>
#include <set>
#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"

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
	void CGraphicalWindow::UpdateList();
	void CGraphicalWindow::SetFigureNameAndID();

	void CGraphicalWindow::MoveFigure(CPoint point);
protected:

	DECLARE_MESSAGE_MAP()
	//void CGraphicalWindow::GetCoordinates(CPoint point);
	//void CGraphicalWindow::DrawRectangle();
	
	
public: 
	std::vector<int> PenStyles;
	std::vector<int> BrushStyles;

	int m_nFigurePenStyles;
	int m_nFigureBrushStyles;
	int m_nFigurePenWidth;
	COLORREF m_crFigurePenColor;
	COLORREF m_crFigureBrushColor;
	std::vector <CFigure *> m_Figure;
	bool m_bLButtonUp;
	bool m_bFigureDone;
	int m_nSelectedFigure;

	std::set<CString> m_setNames;
	std::set<int> m_setID;
	CString m_FigureName;
	int m_FigureID;
protected:
	std::vector<CPoint> m_pRectCoordinates;
	bool m_bPaintNow;
	bool m_bLButtonDown;
	int m_nFigureType;

	
		
};

