#pragma once
#include "Figure.h"
class CRectangle : public CFigure
{
protected:
	virtual void NewCoordinates(int xHalfLength, int yHalfLength);
public:

	CRectangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CRectangle();
	virtual void SetCoordinates(CPoint point);
	virtual void DrawFigure(CDC* pDC);
	//virtual void Resize(bool bMoreLess);
	//virtual void Normalize();
	virtual void Rotate();
	CString GetCoordinates();

protected:
	int m_nVertices;
	//bool m_bCanDraw;

	//int m_nAngle;
	//bool bLeftRightRotate;
public:
	CPoint m_vCoordinates[4];
	CPoint m_vAngleCoordinates[4];
	//CPoint m_CenterCoordinates;
	//double m_xHalfLength;
	//double m_yHalfLength;
};

