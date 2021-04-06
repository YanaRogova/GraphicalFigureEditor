#include "pch.h"
#include "Ellipse.h"

CEllipse::CEllipse(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id):
	CFigure(FIGURE_ELLIPSE, nPenStyle, nPenWidth, crPenColor, nBrushStyle, crBrushColor, strName, id)
{
	m_nVertices = 7;
}

CEllipse::~CEllipse()
{
}

void CEllipse::NewCoordinates(int xHalfLength, int yHalfLength)
{
	m_vCoordinates[0] = CPoint(m_CenterCoordinates.x - xHalfLength * 3 / 4, m_CenterCoordinates.y - yHalfLength);
	m_vCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength * 3 / 4, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[2] = CPoint(m_CenterCoordinates.x + xHalfLength * 3 / 4, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[3] = CPoint(m_CenterCoordinates.x + xHalfLength * 3 / 4, m_CenterCoordinates.y - yHalfLength);

	m_vDrawCoordinates[0] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[2] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[3] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[4] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[5] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[6] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y - yHalfLength);
}

void CEllipse::DrawFigure(CDC* pDC)
{
	pDC->SelectObject(&m_Brush);
	pDC->SelectObject(&m_Pen);

	if (m_nAngle == 0)
	{
		//pDC->Rectangle(m_vCoordinates[0].x, m_vCoordinates[0].y, m_vCoordinates[2].x, m_vCoordinates[2].y);
		pDC->BeginPath();
		pDC->PolyBezier(m_vDrawCoordinates, 7);
		pDC->EndPath();
		pDC->FillPath();
		pDC->PolyBezier(m_vDrawCoordinates, 7);
		
	}
	else
	{
		Rotate();
		pDC->BeginPath();
		pDC->PolyBezier(m_vAngleCoordinates, 7);
		pDC->EndPath();
		pDC->FillPath();
		pDC->PolyBezier(m_vAngleCoordinates, 7);
	}
}

void CEllipse::Rotate()
{
	m_vAngleCoordinates[0] = RotatePoint(0, -m_yHalfLength);
	m_vAngleCoordinates[1] = RotatePoint(-m_xHalfLength, -m_yHalfLength);
	m_vAngleCoordinates[2] = RotatePoint(-m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[3] = RotatePoint(0, m_yHalfLength);
	m_vAngleCoordinates[4] = RotatePoint(m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[5] = RotatePoint(m_xHalfLength, -m_yHalfLength);
	m_vAngleCoordinates[6] = RotatePoint(0, -m_yHalfLength);

	for (int i = 0; i < m_nVertices; i++)
	{
		m_vAngleCoordinates[i] = CPoint(m_CenterCoordinates.x - m_vAngleCoordinates[i].x,
			m_CenterCoordinates.y - m_vAngleCoordinates[i].y);
	}
}

void CEllipse::SetCoordinates(CPoint point)
{
	CFigure::SetCoordinates(point);
	m_xHalfLength = CFigure::m_xHalfLength * 4 / 3;
	NewCoordinates(m_xHalfLength, m_yHalfLength);
	m_bCanDraw = TRUE;
}

void CEllipse::Normalize()
{
	m_yHalfLength = (m_xHalfLength * 3 / 4 + m_yHalfLength) / 2;
	m_xHalfLength = m_yHalfLength * 4 / 3;
	//CFigure::m_xHalfLength = m_yHalfLength;
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

CString CEllipse::GetCoordinates()
{
	CString str;
	str.Format(L"{(%d, %d), (%d, %d), (%d, %d), (%d, %d)}", m_vCoordinates[1].x, m_vCoordinates[1].y, m_vCoordinates[2].x,
		m_vCoordinates[2].y, m_vCoordinates[4].x, m_vCoordinates[4].y, m_vCoordinates[5].x, m_vCoordinates[5].y);
	return str;
}