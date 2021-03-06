#include "pch.h"
#include "Triangle.h"

CTriangle::CTriangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id) :
	CFigure(FIGURE_TRIANGLE, nPenStyle, nPenWidth, crPenColor, nBrushStyle, crBrushColor, strName, id)
{
	m_nEnableVertices = 0;
	m_nVertices = 3;
}

CTriangle::~CTriangle()
{
}

void CTriangle::SetCoordinates(CPoint point)
{
	m_xHalfLength = 0;
	m_yHalfLength = 0;
	m_bCanDraw = TRUE;
	//y = k(x-x0)+y0, k = delta y / delta x
	CPoint buffer;
	if (m_vCoordinates[1].x - m_vCoordinates[0].x == 0)
	{
		buffer = m_vCoordinates[1];
		m_vCoordinates[1] = m_vCoordinates[2];
		m_vCoordinates[2] = buffer;
	}
	else if (m_vCoordinates[2].x - m_vCoordinates[1].x == 0)
	{
		buffer = m_vCoordinates[1];
		m_vCoordinates[1] = m_vCoordinates[0];
		m_vCoordinates[0] = buffer;
	}

	if (m_vCoordinates[1].y - m_vCoordinates[0].y == 0)
	{
		buffer = m_vCoordinates[2];
		m_vCoordinates[2] = m_vCoordinates[0];
		m_vCoordinates[0] = buffer;
	}

	double k1 = (static_cast<double>(m_vCoordinates[1].y) - m_vCoordinates[0].y) / (m_vCoordinates[1].x - m_vCoordinates[0].x);
	double k2 = (static_cast<double>(m_vCoordinates[2].y) - m_vCoordinates[1].y) / (m_vCoordinates[2].x - m_vCoordinates[1].x);

	m_CenterCoordinates.x = (k1 * k2 * (m_vCoordinates[0].y - m_vCoordinates[2].y) +
		k2 * (m_vCoordinates[0].x + m_vCoordinates[1].x) - k1 * (m_vCoordinates[1].x + m_vCoordinates[2].x)) / (2 * (k2 - k1));
	m_CenterCoordinates.y = -(m_CenterCoordinates.x - (m_vCoordinates[0].x + m_vCoordinates[1].x) / 2.0) / k1 +
		((m_vCoordinates[0].y + m_vCoordinates[1].y) / 2.0);

	m_dRadius = pow(pow((m_vCoordinates[0].x - m_CenterCoordinates.x), 2) + pow((m_vCoordinates[0].y - m_CenterCoordinates.y), 2), 0.5);
	for (int i = 0; i < m_nVertices; i++)
	{
		int deltaX = m_vCoordinates[i].x - m_CenterCoordinates.x;
		int deltaY = m_vCoordinates[i].y - m_CenterCoordinates.y;

		m_dAngle[i] = atan(static_cast<double>(deltaY) / deltaX);

		if (deltaX < 0)
		{
			m_dAngle[i] += PI;
		}
	}
}

void CTriangle::DrawFigure(CDC* pDC)
{
	pDC->SelectObject(m_ptrBrush);
	pDC->SelectObject(m_ptrPen);

	HDC hdc = static_cast<HDC>(*pDC);
	SetBkMode(hdc, TRANSPARENT);
	CPoint tempCoordinates[3];
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
	pDC->Polygon(&tempCoordinates[0], 3);
}

void CTriangle::Normalize()
{
	double nSize[3];
	nSize[0] = hypot(m_vCoordinates[0].x - m_vCoordinates[1].x, m_vCoordinates[0].y - m_vCoordinates[1].y);
	nSize[1] = hypot(m_vCoordinates[1].x - m_vCoordinates[2].x, m_vCoordinates[1].y - m_vCoordinates[2].y);
	nSize[2] = hypot(m_vCoordinates[2].x - m_vCoordinates[0].x, m_vCoordinates[2].y - m_vCoordinates[0].y);

	m_dAngle[0] = -PI / 2;
	m_dAngle[1] = m_dAngle[0] + 2 * PI / 3;
	m_dAngle[2] = m_dAngle[1] + 2 * PI / 3;

	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CTriangle::Rotate()
{
	CPoint buffer;

	m_vAngleCoordinates[0] = RotatePoint(-(m_CenterCoordinates.x - m_vCoordinates[0].x), -(m_CenterCoordinates.y - m_vCoordinates[0].y));
	m_vAngleCoordinates[1] = RotatePoint(-(m_CenterCoordinates.x - m_vCoordinates[1].x), -(m_CenterCoordinates.y - m_vCoordinates[1].y));
	m_vAngleCoordinates[2] = RotatePoint(-(m_CenterCoordinates.x - m_vCoordinates[2].x), -(m_CenterCoordinates.y - m_vCoordinates[2].y));

	for (int i = 0; i < 3; i++)
	{
		m_vAngleCoordinates[i] = CPoint(m_CenterCoordinates.x + m_vAngleCoordinates[i].x,
			m_CenterCoordinates.y + m_vAngleCoordinates[i].y);
	}
}

CString CTriangle::GetStrCoordinates()
{
	CString str;
	if (m_nAngle == 0 || m_bReturnNotRotateCoordinates)
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d)}", m_vCoordinates[0].x, m_vCoordinates[0].y, m_vCoordinates[1].x,
			m_vCoordinates[1].y, m_vCoordinates[2].x, m_vCoordinates[2].y);
	else
		str.Format(L"{(%d, %d), (%d, %d), (%d, %d)}", m_vAngleCoordinates[0].x, m_vAngleCoordinates[0].y, m_vAngleCoordinates[1].x,
			m_vAngleCoordinates[1].y, m_vAngleCoordinates[2].x, m_vAngleCoordinates[2].y);
	return str;
}

CPoint* CTriangle::GetCoordinates()
{
	if (m_nAngle == 0)
		return m_vCoordinates;
	else
		return m_vAngleCoordinates;
}

CPoint CTriangle::GetVertice(int nVertice)
{
	if (m_nAngle == 0)
		return m_vCoordinates[nVertice];
	else
		return m_vAngleCoordinates[nVertice];
}

void CTriangle::SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate)
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

void CTriangle::UpdateCoordinate(int nVertice)
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

void CTriangle::Resize(bool bMoreLess)
{
	double nResizeCoefficient = 1.1;
	for (int i = 0; i < m_nVertices; i++)
	{
		if (bMoreLess)
		{
			m_dRadius *= nResizeCoefficient;
		}
		else if (m_dRadius > nResizeCoefficient)
		{
			m_dRadius /= nResizeCoefficient;
		}
	}
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

int CTriangle::GetNumberVertices()
{
	return m_nEnableVertices;
}

void CTriangle::SetVertice(int nNumberVertice, CPoint point)
{
	switch (nNumberVertice)
	{
	case 0:
		m_vCoordinates[nNumberVertice] = point;
		m_nEnableVertices++;
		break;
	case 1:
		if (m_vCoordinates[0] != point)
		{
			m_vCoordinates[nNumberVertice] = point;
			m_nEnableVertices++;
		}
		break;
	case 2:
		if (m_vCoordinates[0] != point && m_vCoordinates[1] != point &&
			!(m_vCoordinates[0].x == m_vCoordinates[1].x && m_vCoordinates[0].x == point.x) &&
			!(m_vCoordinates[0].y == m_vCoordinates[1].y && m_vCoordinates[0].y == point.y))
		{
			m_vCoordinates[nNumberVertice] = point;
			m_nEnableVertices++;
		}
		break;
	}
}

void CTriangle::NewCoordinates(int xHalfLength, int yHalfLength)
{
	CPoint buffer;
	for (int i = 0; i < m_nVertices; i++)
	{
		buffer.x = (m_dRadius) * cos(m_dAngle[i]);
		buffer.y = (m_dRadius) * sin(m_dAngle[i]);
		m_vCoordinates[i] = CPoint(m_CenterCoordinates.x + buffer.x, m_CenterCoordinates.y + buffer.y);
	}
}
