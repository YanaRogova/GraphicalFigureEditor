#pragma once
#include "Figure.h"

#define TRIANGLE_VERTICES 3

class CTriangle : public CFigure
{
public:
	CTriangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CTriangle();

	void SetCoordinates(CPoint point) override;
	void DrawFigure(CDC* pDC) override;
	void Normalize() override;
	void Rotate() override;
	CString GetStrCoordinates();
	CPoint* GetCoordinates();
	CPoint GetVertice(int nVertice);

	void SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate);
	void UpdateCoordinate(int nVertice);

	void Resize(bool bMoreLess) override;
	int GetNumberVertices() override;
	void SetVertice(int nNumberVertice, CPoint point) override;

protected:
	virtual void NewCoordinates(int xHalfLength, int yHalfLength);

protected:
	int m_nVertices;
	int m_nEnableVertices;
	double m_dRadius;
	double m_dAngle[TRIANGLE_VERTICES];

public:
	CPoint m_vCoordinates[TRIANGLE_VERTICES];
	CPoint m_vAngleCoordinates[TRIANGLE_VERTICES];
};

