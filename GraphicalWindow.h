#pragma once
#include <afxwin.h>
#include <vector>
#include <set>
#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Link.h"


class CGraphicalWindow : public CStatic//View
{
public:
	//virtual void OnDraw(CDC* pDC);
	CGraphicalWindow();
	afx_msg void OnPaint();
	virtual ~CGraphicalWindow();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	/*afx_msg void OnVScroll(UINT SBCode, UINT Pos, CScrollBar* SB);
	afx_msg void OnHScroll(UINT SBCode, UINT Pos, CScrollBar* SB);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);*/
	void SetFigureType(int nFigureType);
	void UpdateList();
	void SetFigureNameAndID();

	void MoveFigure(CPoint point);
	bool PictureNotSaved();
	void SetPictureNotSaved(bool bNotSaved);
	void DeleteFigure();
	/*void CreateVerticalScrollbar(int nStartX, int nStartY, int m_nWidth, int m_nHeight);
	void CreateHorizontalScrollbar(int m_nWidth, int m_nHeight);*/
protected:

	DECLARE_MESSAGE_MAP()	
	
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

	int m_nLinkFirstFigure;
	int m_nLinkSecondFigure;

	std::set<CString> m_setNames;
	std::set<int> m_setID;
	CString m_FigureName;
	int m_FigureID;

	
	void SaveElement(int nNumberElement, CFile& file);
	void CStringToFile(CString &string, CFile& file);
	void NumberToFile(int &num, CFile& file);
	void NumberToFile(unsigned long &num, CFile& file);
	void SavePicture(CString strFileName);
	void OpenPicture(CString strFileName);
	bool CreateElement(CStdioFile& file);
protected:
	std::vector<CPoint> m_pRectCoordinates;
	bool m_bPaintNow;
	bool m_bLButtonDown;
	int m_nFigureType;
	bool m_bPictureNotSaved;

	void CGraphicalWindow::PreCreateFigure();
	//int pos = 0;
	//int pos1 = 0;
};

