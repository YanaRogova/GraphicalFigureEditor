#pragma once
#include "Figure.h"
class CTriangle : public CFigure
{
protected:
	//virtual void NewCoordinates(int xHalfLength, int yHalfLength);
public:

	CTriangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	//virtual ~CTriangle();
	//virtual void SetCoordinates(CPoint point);
	//virtual void DrawFigure(CDC* pDC);
	////virtual void Resize(bool bMoreLess);
	////virtual void Normalize();
	//virtual void Rotate();

protected:
	int m_nVertices;
	//bool m_bCanDraw;
	int m_nPenStyle;
	int m_nPenWidth;
	COLORREF m_crPenColor;
	int m_nBrushStyle;
	COLORREF m_crBrushColor;
	//int m_nAngle;
	//bool bLeftRightRotate;
public:
	CPoint m_vCoordinates[3];
	CPoint m_vAngleCoordinates[3];
	//CPoint m_CenterCoordinates;
	//double m_xHalfLength;
	//double m_yHalfLength;
};

