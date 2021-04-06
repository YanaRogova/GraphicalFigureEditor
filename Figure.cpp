#include "pch.h"
#include "Figure.h"



CFigure::CFigure(int nFigureType, int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id) : 
	m_figureNameID(strName, id), m_Pen(), m_Brush()
{
	m_nFigureType = nFigureType;
	//m_nVertices = 0;
	m_bCanDraw = FALSE;
	m_nPenStyle = nPenStyle;
	m_nPenWidth = nPenWidth;
	m_crPenColor = crPenColor;
	m_nBrushStyle = nBrushStyle;
	m_crBrushColor = crBrushColor;
	m_nAngle = 0;
	m_xHalfLength = 0.0;
	m_yHalfLength = 0.0;
	SetBrushAndPen();
}

CFigure::~CFigure()
{

}


void CFigure::SetCoordinates(CPoint point)
{
	m_CenterCoordinates.x = (m_vCoordinates[0].x + point.x) / 2;
	m_CenterCoordinates.y = (m_vCoordinates[0].y + point.y) / 2;

	m_xHalfLength = (((m_vCoordinates[0].x - point.x) > 0) ?
		(m_vCoordinates[0].x - point.x) : (point.x - m_vCoordinates[0].x)) / 2.0;
	m_yHalfLength = (((m_vCoordinates[0].y - point.y) > 0) ?
		(m_vCoordinates[0].y - point.y) : (point.y - m_vCoordinates[0].y)) / 2.0;

	//m_bCanDraw = TRUE;
}

void CFigure::DrawFigure(CDC* pDC)
{
	CBrush brush;
	if (m_nBrushStyle == -1)
		brush.CreateSolidBrush(m_crBrushColor);
	else
		brush.CreateHatchBrush(m_nBrushStyle, m_crBrushColor);
	pDC->SelectObject(&brush);
	CPen pen(m_nPenStyle, m_nPenWidth, m_crPenColor);
	pDC->SelectObject(&pen);
	//if(m_nAngle == 0)
	//	pDC->Polygon(&m_vCoordinates[0], 4);
	//else
	//{
	//	Rotate();
	//	pDC->Polygon(&m_vAngleCoordinates[0], 4);
	//}
}

int CFigure::GetFigureType()
{
	return m_nFigureType;
}

bool CFigure::GetCanDraw()
{
	return m_bCanDraw;
}

void CFigure::Normalize()
{
	m_xHalfLength = (m_xHalfLength + m_yHalfLength) / 2;
	m_yHalfLength = m_xHalfLength;
	
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CFigure::Resize(bool bMoreLess)
{
	double nResizeCoefficient = 1.1;

	if (bMoreLess)
	{
		m_xHalfLength *= nResizeCoefficient;
		m_yHalfLength *= nResizeCoefficient;
	}
	else if (m_xHalfLength > nResizeCoefficient && m_yHalfLength > nResizeCoefficient)
	{
		m_xHalfLength /= nResizeCoefficient;
		m_yHalfLength /= nResizeCoefficient;
	}

	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CFigure::Rotate()
{
	CPoint buffer;
	
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

CPoint CFigure::RotatePoint(double x, double y)
{
	CPoint newPoint;
	if (m_nAngle == 90)
		return CPoint(y, -x);
	else if (m_nAngle == 180)
		return CPoint(-x, -y);
	else if (m_nAngle == 270)
		return CPoint(-y, x);
	else
	{
		newPoint.x = x * cos(m_nAngle * PI / 180) + y * sin(m_nAngle * PI / 180);
		newPoint.y = -x * sin(m_nAngle * PI / 180) + y * cos(m_nAngle * PI / 180);
	}
	return newPoint;
}

void CFigure::SetAngle(int nAngle)
{
	if (nAngle < 0)
		m_nAngle += (nAngle % 360) + 360;
	else
		m_nAngle += nAngle;
	m_nAngle = m_nAngle % 360;
}

void CFigure::Move(CPoint point)
{
	m_CenterCoordinates = point;
	NewCoordinates(m_xHalfLength, m_yHalfLength);
}

void CFigure::NewCoordinates(int xHalfLength, int yHalfLength)
{
	m_vCoordinates[0] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y - yHalfLength);
	m_vCoordinates[1] = CPoint(m_CenterCoordinates.x - xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[2] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y + yHalfLength);
	m_vCoordinates[3] = CPoint(m_CenterCoordinates.x + xHalfLength, m_CenterCoordinates.y - yHalfLength);
}

void CFigure::SetBrushAndPen()
{
	if (m_nBrushStyle == -1)
		m_Brush.CreateSolidBrush(m_crBrushColor);
	else
		m_Brush.CreateHatchBrush(m_nBrushStyle, m_crBrushColor);

	m_Pen.CreatePen(m_nPenStyle, m_nPenWidth, m_crPenColor);
}


int CFigure::GetNumberVertices()
{
	return -1;
}

void CFigure::SetVertice(int nNumberVertice, CPoint point)
{
}

CString CFigure::GetName()
{
	return m_figureNameID.GetName();
}

CString CFigure::GetID()
{
	CString str;
	str.Format(L"%d", m_figureNameID.GetID());
	return str;
}

CString CFigure::GetCenter()
{
	CString str;
	str.Format(L"(%d, %d)", m_CenterCoordinates.x, m_CenterCoordinates.y);
	return str;
}

CString CFigure::GetCoordinates()
{
	return L"";
}

CString CFigure::GetAngle()
{
	CString str;
	str.Format(L"%d", m_nAngle);
	return str;
}

CString CFigure::GetFigure()
{
	switch (m_nFigureType)
	{
	case FIGURE_ELLIPSE:
		return L"Ellipse";
	case FIGURE_RECTANGLE:
		return L"Rectangle";
	case FIGURE_TRIANGLE:
		return L"Triangle";
	default:
		break;
	}
	return L"";
}