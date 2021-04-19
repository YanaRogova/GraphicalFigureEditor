#pragma once
#include "Figure.h"
class CRectangle : public CFigure
{

public:
	CRectangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CRectangle();

	void SetCoordinates(CPoint point) override;
	void DrawFigure(CDC* pDC) override;
	void Rotate() override;
	CString GetStrCoordinates() override;
	CPoint* GetCoordinates() override;
	CPoint GetVertice(int nVertice) override;
	void SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate) override;
	void UpdateCoordinate(int nVertice) override;

protected:
	void NewCoordinates(int xHalfLength, int yHalfLength) override;

protected:
	int m_nVertices;

public:
	CPoint m_vCoordinates[4];
	CPoint m_vAngleCoordinates[4];
};

