#pragma once
#include "Figure.h"
class CTriangle : public CFigure
{
protected:
	virtual void NewCoordinates(int xHalfLength, int yHalfLength);
public:

	CTriangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CTriangle();
	void SetCoordinates(CPoint point) override;
	void DrawFigure(CDC* pDC) override;
	void Resize(bool bMoreLess) override;
	void Normalize() override;
	void Rotate() override;
	int GetNumberVertices() override;
	void SetVertice(int nNumberVertice, CPoint point) override;

protected:
	int m_nVertices;
	//bool m_bCanDraw;
	int m_nEnableVertices;
	double m_dRadius;
	double m_dAngle[3];
	//int m_nAngle;
	//bool bLeftRightRotate;
public:
	CPoint m_vCoordinates[3];
	CPoint m_vAngleCoordinates[3];
	//CPoint m_CenterCoordinates;
	//double m_xHalfLength;
	//double m_yHalfLength;
};

