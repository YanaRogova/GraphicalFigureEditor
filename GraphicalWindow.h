#pragma once
#include <afxwin.h>
#include <vector>
#include <set>
#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Link.h"


class CGraphicalWindow : public CStatic
{
protected:
	DECLARE_MESSAGE_MAP()
	void PreCreateFigure();

public:
	CGraphicalWindow();
	virtual ~CGraphicalWindow();

	void SetFigureType(int nFigureType);
	void UpdateList();
	void SetFigureNameAndID();
	void MoveFigure(CPoint point);
	bool PictureNotSaved();
	void SetPictureNotSaved(bool bNotSaved);
	void DeleteFigure();

	void SaveElement(int nNumberElement, CFile& file);
	void CStringToFile(CString& string, CFile& file);
	void NumberToFile(int& num, CFile& file);
	void NumberToFile(unsigned long& num, CFile& file);
	void SavePicture(CString strFileName);
	void OpenPicture(CString strFileName);
	bool CreateElement(CStdioFile& file);

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

public: 
	std::vector<int> PenStyles;
	std::vector<int> BrushStyles;
	std::vector <CFigure *> m_Figure;

	std::set<CString> m_setNames;
	std::set<int> m_setID;

	int m_nFigurePenStyles;
	int m_nFigureBrushStyles;
	int m_nFigurePenWidth;
	int m_nSelectedFigure;
	int m_nLinkFirstFigure;
	int m_nLinkSecondFigure;
	int m_FigureID;
	bool m_bLButtonUp;
	bool m_bFigureDone;

	CString m_FigureName;

	COLORREF m_crFigurePenColor;
	COLORREF m_crFigureBrushColor;
	
protected:
	std::vector<CPoint> m_pRectCoordinates;
	bool m_bPaintNow;
	bool m_bLButtonDown;
	bool m_bPictureNotSaved;
	int m_nFigureType;
};

