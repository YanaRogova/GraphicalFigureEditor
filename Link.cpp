#include "pch.h"
#include "Link.h"

#include "GraphicalWindow.h"

CLink::CLink(int nPenStyle, int nPenWidth, COLORREF crPenColor, CString strfirstFigure, CString strsecondFigure, 
	int nDirection,	CPoint nFirstPoint, CPoint nSecondPoint, CString strName, unsigned int id) : 
	CFigure(FIGURE_LINK, nPenStyle, nPenWidth, crPenColor, -1, crPenColor, strName, id)
{
	m_strFirstFigure = strfirstFigure;
	m_strSecondFigure = strsecondFigure;

	m_nVertices = 2;
	m_vCoordinates[0] = nFirstPoint;
	m_vCoordinates[1] = nSecondPoint;
	m_bCanDraw = TRUE;
	m_nDirection = nDirection;
}

CLink::~CLink()
{

}

double CLink::GetArrowAngle(double fw, double fh)
{
	double fg = sqrt(fw * fw + fh * fh), fs, fc;
	if (fg == 0) return 0;
	fs = fh / fg; fc = fw / fg;
	if (fs >= 0) return 180.0 * acos(fc) / PI;
	else return 360.0 - 180.0 * acos(fc) / PI;
}

void CLink::PaintArrow(CPoint startPoint, CPoint endPoint, CDC* pDC)
{
	double deltaAngle = 170;
	double length = m_nPenWidth * 8;
	double angle;
	POINT poly[3];

	angle = GetArrowAngle(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
	angle = angle - deltaAngle;
	poly[0] = endPoint;
	poly[2].x = (long)(endPoint.x + length * cos(angle * PI / 180));
	poly[2].y = (long)(endPoint.y + length * sin(angle * PI / 180));
	angle = angle + 2 * deltaAngle;
	poly[1].x = (long)(endPoint.x + length * cos(angle * PI / 180));
	poly[1].y = (long)(endPoint.y + length * sin(angle * PI / 180));
	pDC->Polygon(poly, 3);
}

void CLink::DrawFigure(CDC* pDC)
{
	pDC->SelectObject(m_ptrBrush);
	pDC->SelectObject(m_ptrPen);
	CPoint tempCoordinates[2];
	for (int i = 0; i < m_nVertices; i++)
	{
		tempCoordinates[i].x = m_vCoordinates[i].x + m_HScrollPosition;
		tempCoordinates[i].y = m_vCoordinates[i].y + m_VScrollPosition;
	}

	pDC->MoveTo(tempCoordinates[0]);
	pDC->LineTo(tempCoordinates[1]);

	CPen ArrowPen;
	ArrowPen.CreatePen(PS_SOLID | PS_GEOMETRIC, m_nPenWidth, m_crPenColor);
	pDC->SelectObject(&ArrowPen);
	if(m_nDirection == 2 || m_nDirection == 3)
		PaintArrow(tempCoordinates[0], tempCoordinates[1], pDC);
	if (m_nDirection == 1 || m_nDirection == 3)
		PaintArrow(tempCoordinates[1], tempCoordinates[0], pDC);
	pDC->SelectObject(m_ptrPen);
}

CString CLink::GetFirstFigure()
{
	return m_strFirstFigure;
}

CString CLink::GetSecondFigure()
{
	return m_strSecondFigure;
}

void CLink::SetVertice(int nNumberVertice, CPoint point)
{
	m_vCoordinates[nNumberVertice] = point;
}

CPoint CLink::GetVertice(int nVertice)
{
	return m_vCoordinates[nVertice];
}

void CLink::SetFigure(CString strFigure, bool bFirstSecond)
{
	if (bFirstSecond)
		m_strFirstFigure = strFigure;
	else
		m_strSecondFigure = strFigure;
}

void CLink::SetPen()
{
	CFigure::SetPen();
	m_crBrushColor = m_crPenColor;
	delete m_ptrBrush;
	m_ptrBrush = nullptr;
	SetBrush();
}

CString CLink::GetStrCoordinates()
{
	CString str;
	str.Format(L"{(%d, %d), (%d, %d)}", m_vCoordinates[0].x, m_vCoordinates[0].y, m_vCoordinates[1].x,
		m_vCoordinates[1].y);
	return str;
}

CString CLink::GetStrCenter()
{
	return L"-";
}

CString CLink::GetAngle()
{
	return L"-";
}

int CLink::GetDirection()
{
	return m_nDirection;
}

CPoint* CLink::GetCoordinates()
{
	return m_vCoordinates;
}

void CLink::SetDirection(int nDirection)
{
	m_nDirection = nDirection;
}

