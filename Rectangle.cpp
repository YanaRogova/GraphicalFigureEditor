#include "pch.h"
#include "Rectangle.h"

CRectangle::CRectangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id): 
	CFigure(FIGURE_RECTANGLE, nPenStyle, nPenWidth, crPenColor,	nBrushStyle, crBrushColor, strName, id)
{
	m_nVertices = 4;
}

CRectangle::~CRectangle()
{
}

void CRectangle::SetCoordinates(CPoint point)
{
	CFigure::SetCoordinates(point);

	NewCoordinates(m_xHalfLength, m_yHalfLength);
	m_bCanDraw = TRUE;
}

void CRectangle::DrawFigure(CDC* pDC)
{
	pDC->SelectObject(m_ptrBrush);
	pDC->SelectObject(m_ptrPen);

	HDC hdc = static_cast<HDC>(*pDC);
	SetBkMode(hdc, TRANSPARENT);
	CPoint tempCoordinates[4];

	if (m_nAngle == 0)
	{
		for (int i = 0; i < m_nVertices; i++)
		{
			tempCoordinates[i].x = m_vCoordinates[i].x + m_HScrollPosition;
			tempCoordinates[i].y = m_vCoordinates[i].y + m_VScrollPosition;
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
	pDC->Polygon(&tempCoordinates[0], 4);
}

void CRectangle::Rotate()
{
	m_vAngleCoordinates[0] = RotatePoint(-m_xHalfLength, -m_yHalfLength);
	m_vAngleCoordinates[1] = RotatePoint(-m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[2] = RotatePoint(m_xHalfLength, m_yHalfLength);
	m_vAngleCoordinates[3] = RotatePoint(m_xHalfLength, -m_yHalfLength);

	for (int i = 0; i < m_nVertices; i++)
	{
		m_vAngleCoordinates[i] = CPoint(m_CenterCoordinates.x + m_vAngleCoordinates[i].x,
			m_CenterCoordinates.y + m_vAngleCoordinates[i].y);
	}
}

CString CRectangle::GetStrCoordinates()
{
	CString str;
	if (m_nAngle == 0 || m_bReturnNotRotateCoordinates)
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d), (%d, %d)}", m_vCoordinates[0].x, m_vCoordinates[0].y, m_vCoordinates[1].x,
			m_vCoordinates[1].y, m_vCoordinates[2].x, m_vCoordinates[2].y, m_vCoordinates[3].x, m_vCoordinates[3].y);
	else
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d), (%d, %d)}", m_vAngleCoordinates[0].x, m_vAngleCoordinates[0].y,
			m_vAngleCoordinates[1].x, m_vAngleCoordinates[1].y, m_vAngleCoordinates[2].x, m_vAngleCoordinates[2].y,
			m_vAngleCoordinates[3].x, m_vAngleCoordinates[3].y);
	return str;
}

CPoint* CRectangle::GetCoordinates()
{
	if (m_nAngle == 0)
		return m_vCoordinates;
	else
		return m_vAngleCoordinates;
}

CPoint CRectangle::GetVertice(int nVertice)
{
	if (m_nAngle == 0)
		return m_vCoordinates[nVertice];
	else
		return m_vAngleCoordinates[nVertice];
}

void CRectangle::SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate)
{
	if (bXOrY)
	{
		switch (nVertice)
		{
		case 0:
		case 1:
			m_vCoordinates[0].x = nCoordinate;
			m_vCoordinates[1].x = nCoordinate;
			if (m_nAngle != 0)
			{
				UpdateCoordinate(0);
				UpdateCoordinate(1);
			}
			break;
		case 3:
		case 2:
			m_vCoordinates[3].x = nCoordinate;
			m_vCoordinates[2].x = nCoordinate;
			if (m_nAngle != 0)
			{
				UpdateCoordinate(3);
				UpdateCoordinate(2);
			}			
			break;
		}
	}
	else
	{
		switch (nVertice)
		{
		case 0:
		case 3:
			m_vCoordinates[0].y = nCoordinate;
			m_vCoordinates[3].y = nCoordinate;

			if (m_nAngle != 0)
			{
				UpdateCoordinate(0);
				UpdateCoordinate(3);
			}
			break;
		case 2:
		case 1:
			m_vCoordinates[2].y = nCoordinate;
			m_vCoordinates[1].y = nCoordinate;

			if (m_nAngle != 0)
			{
				UpdateCoordinate(2);
				UpdateCoordinate(1);
			}
			break;
		}
	}
}

void CRectangle::UpdateCoordinate(int nVertice)
{
	m_nAngle *= -1;
	
	m_vCoordinates[nVertice] = RotatePoint(-m_CenterCoordinates.x + m_vCoordinates[nVertice].x,
		-m_CenterCoordinates.y + m_vAngleCoordinates[nVertice].y);
	m_vCoordinates[nVertice] = CPoint(m_CenterCoordinates.x + m_vCoordinates[nVertice].x,
		m_CenterCoordinates.y + m_vCoordinates[nVertice].y);
	m_nAngle *= -1;
	SetCoordinates(CPoint());
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CRectangle::NewCoordinates(int xHalfLength, int yHalfLength)
{
	m_vCoordinates[0] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[2] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[3] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y - yHalfLength);
}