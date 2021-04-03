#include "pch.h"
#include "Rectangle.h"

CRectangle::CRectangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id): 
	CFigure(FIGURE_RECTANGLE, nPenStyle, nPenWidth, crPenColor,	nBrushStyle, crBrushColor, strName, id)
{
	m_nVertices = 4;
	/*m_nPenStyle = nPenStyle;
	m_nPenWidth = nPenWidth;
	m_crPenColor = crPenColor;
	m_nBrushStyle = nBrushStyle;
	m_crBrushColor = crBrushColor;*/
}

CRectangle::~CRectangle()
{
}

void CRectangle::NewCoordinates(int xHalfLength, int yHalfLength)
{
	m_vCoordinates[0] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[2] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[3] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y - yHalfLength);
}

void CRectangle::DrawFigure(CDC* pDC)
{
	pDC->SelectObject(&m_Brush);
	pDC->SelectObject(&m_Pen);

	if (m_nAngle == 0)
		pDC->Polygon(&m_vCoordinates[0], 4);
	else
	{
		Rotate();
		pDC->Polygon(&m_vAngleCoordinates[0], 4);
	}
}

void CRectangle::Rotate()
{
	m_vAngleCoordinates[0] = RotatePoint(-m_xHalfLength, -m_yHalfLength);
	m_vAngleCoordinates[1] = RotatePoint(-m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[2] = RotatePoint(m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[3] = RotatePoint(m_xHalfLength, -m_yHalfLength);

	for (int i = 0; i < 4; i++)
	{
		m_vAngleCoordinates[i] = CPoint(m_CenterCoordinates.x - m_vAngleCoordinates[i].x,
			m_CenterCoordinates.y - m_vAngleCoordinates[i].y);
	}
}

void CRectangle::SetCoordinates(CPoint point)
{
	m_vCoordinates[0] = CFigure::m_vCoordinates[0];
	m_vCoordinates[1] = CPoint(m_vCoordinates[0].x, point.y);
	m_vCoordinates[2] = point;
	m_vCoordinates[3] = CPoint(point.x, m_vCoordinates[0].y);
	m_CenterCoordinates.x = (m_vCoordinates[0].x + point.x) / 2;
	m_CenterCoordinates.y = (m_vCoordinates[0].y + point.y) / 2;

	m_xHalfLength = (((m_vCoordinates[0].x - m_vCoordinates[2].x) > 0) ?
		(m_vCoordinates[0].x - m_vCoordinates[2].x) : (m_vCoordinates[2].x - m_vCoordinates[0].x)) / 2.0;
	m_yHalfLength = (((m_vCoordinates[0].y - m_vCoordinates[2].y) > 0) ?
		(m_vCoordinates[0].y - m_vCoordinates[2].y) : (m_vCoordinates[2].y - m_vCoordinates[0].y)) / 2.0;

	m_bCanDraw = TRUE;
}