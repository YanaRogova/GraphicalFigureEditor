#pragma once
#include "Figure.h"

#define ELLIPSE_DRAW_VERTICES 7

class CEllipse : public CFigure
{
public:
	CEllipse(int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CEllipse();

	void SetCoordinates(CPoint point) override;
	void DrawFigure(CDC* pDC) override;
	void Normalize() override;
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
	bool bNormalised;

public:
	CPoint m_vCoordinates[VERTICES];
	CPoint m_vAngleReturnCoordinates[VERTICES];
	CPoint m_vDrawCoordinates[ELLIPSE_DRAW_VERTICES];
	CPoint m_vAngleCoordinates[ELLIPSE_DRAW_VERTICES];
};

