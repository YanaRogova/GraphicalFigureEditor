#include "pch.h"
#include "Ellipse.h"

CEllipse::CEllipse(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id):
	CFigure(FIGURE_ELLIPSE, nPenStyle, nPenWidth, crPenColor, nBrushStyle, crBrushColor, strName, id)
{
	m_nVertices = ELLIPSE_DRAW_VERTICES;
	bNormalised = FALSE;
}

CEllipse::~CEllipse()
{
}

void CEllipse::SetCoordinates(CPoint point)
{
	CFigure::SetCoordinates(point);
	m_xHalfLength = CFigure::m_xHalfLength * 4 / 3;
	NewCoordinates(m_xHalfLength, m_yHalfLength);
	m_bCanDraw = TRUE;
}

void CEllipse::DrawFigure(CDC* pDC)
{
	HDC hdc = static_cast<HDC>(*pDC);
	SetBkMode(hdc, TRANSPARENT);

	pDC->SelectObject(m_ptrBrush);
	pDC->SelectObject(m_ptrPen);
	CPoint tempCoordinates[ELLIPSE_DRAW_VERTICES];
	if (!bNormalised)
	{
		if (m_nAngle == 0)
		{
			for (int i = 0; i < m_nVertices; i++)
			{
				tempCoordinates[i].x = m_vDrawCoordinates[i].x + m_HScrollPosition;
				tempCoordinates[i].y = m_vDrawCoordinates[i].y + m_VScrollPosition;
			}
		}
		else
		{
			Rotate();
			for (int i = 0; i < m_nVertices; i++)
			{
				tempCoordinates[i].x = m_vAngleCoordinates[i].x + m_HScrollPosition;
				tempCoordinates[i].y = m_vAngleCoordinates[i].y + m_VScrollPosition;
			}
		}
		pDC->BeginPath();
		pDC->PolyBezier(tempCoordinates, ELLIPSE_DRAW_VERTICES);
		pDC->EndPath();
		pDC->FillPath();
		pDC->PolyBezier(tempCoordinates, ELLIPSE_DRAW_VERTICES);
	}
	else
	{
		pDC->Ellipse(m_vCoordinates[0].x + m_HScrollPosition, m_vCoordinates[0].y + m_VScrollPosition,
			m_vCoordinates[2].x + m_HScrollPosition, m_vCoordinates[2].y + m_VScrollPosition);
	}
}

void CEllipse::Normalize()
{
	m_yHalfLength = (m_xHalfLength * 3 / 4 + m_yHalfLength) / 2;
	m_xHalfLength = m_yHalfLength * 4 / 3;

	NewCoordinates(m_xHalfLength, m_yHalfLength);
	bNormalised = TRUE;
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
		m_vAngleCoordinates[i] = CPoint(m_CenterCoordinates.x + m_vAngleCoordinates[i].x,
			m_CenterCoordinates.y + m_vAngleCoordinates[i].y);
	}
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

CString CEllipse::GetStrCoordinates()
{
	CString str;
	if (m_nAngle == 0 || m_bReturnNotRotateCoordinates)
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d), (%d, %d)}", m_vCoordinates[0].x, m_vCoordinates[0].y, m_vCoordinates[1].x,
			m_vCoordinates[1].y, m_vCoordinates[2].x, m_vCoordinates[2].y, m_vCoordinates[3].x, m_vCoordinates[3].y);
	else
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d), (%d, %d)}", m_vAngleReturnCoordinates[0].x, m_vAngleReturnCoordinates[0].y,
			m_vAngleReturnCoordinates[1].x, m_vAngleReturnCoordinates[1].y, m_vAngleReturnCoordinates[2].x,
			m_vAngleReturnCoordinates[2].y, m_vAngleReturnCoordinates[3].x, m_vAngleReturnCoordinates[3].y);

	return str;
}

CPoint* CEllipse::GetCoordinates()
{
	if (m_nAngle == 0)
		return m_vCoordinates;
	else
		return m_vAngleReturnCoordinates;
}

CPoint CEllipse::GetVertice(int nVertice)
{
	if (m_nAngle == 0)
		return m_vCoordinates[nVertice];
	else
		return m_vAngleReturnCoordinates[nVertice];
}

void CEllipse::SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate)
{
	if (bXOrY)
	{
		m_vCoordinates[nVertice].x = nCoordinate;
	}
	else
	{
		m_vCoordinates[nVertice].y = nCoordinate;
	}
	if (m_nAngle != 0)
		UpdateCoordinate(nVertice);
}

void CEllipse::UpdateCoordinate(int nVertice)
{
	m_nAngle *= -1;
	m_vAngleReturnCoordinates[nVertice] = RotatePoint(-m_CenterCoordinates.x + m_vCoordinates[nVertice].x,
		-m_CenterCoordinates.y + m_vAngleCoordinates[nVertice].y);
	m_vAngleReturnCoordinates[nVertice] = CPoint(m_CenterCoordinates.x + m_vCoordinates[nVertice].x,
		m_CenterCoordinates.y + m_vCoordinates[nVertice].y);
	m_nAngle *= -1;
	SetCoordinates(CPoint());
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CEllipse::NewCoordinates(int xHalfLength, int yHalfLength)
{
	m_vCoordinates[0] = CPoint(m_CenterCoordinates.x - xHalfLength * 3 / 4, m_CenterCoordinates.y - yHalfLength);
	m_vCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength * 3 / 4, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[2] = CPoint(m_CenterCoordinates.x + xHalfLength * 3 / 4, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[3] = CPoint(m_CenterCoordinates.x + xHalfLength * 3 / 4, m_CenterCoordinates.y - yHalfLength);
	
	m_vAngleReturnCoordinates[0] = RotatePoint(-m_xHalfLength * 3 / 4, -m_yHalfLength);
	m_vAngleReturnCoordinates[1] = RotatePoint(-m_xHalfLength * 3 / 4, m_yHalfLength);
	m_vAngleReturnCoordinates[2] = RotatePoint(m_xHalfLength * 3 / 4, m_yHalfLength);
	m_vAngleReturnCoordinates[3] = RotatePoint(m_xHalfLength * 3 / 4, -m_yHalfLength);
	for (int i = 0; i < VERTICES; i++)
	{
		m_vAngleReturnCoordinates[i] = CPoint(m_CenterCoordinates.x + m_vAngleReturnCoordinates[i].x,
			m_CenterCoordinates.y + m_vAngleReturnCoordinates[i].y);
	}


	m_vDrawCoordinates[0] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[2] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[3] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[4] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vDrawCoordinates[5] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vDrawCoordinates[6] = CPoint(m_CenterCoordinates.x, m_CenterCoordinates.y - yHalfLength);
}
