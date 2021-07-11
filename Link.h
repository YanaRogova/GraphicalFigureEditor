#pragma once
#include "Figure.h"

#define LINK_VERTICES 2

class CLink : public CFigure
{
public:
	CLink(int nPenStyle, int nPenWidth, COLORREF crPenColor, CString strfirstFigure, CString strsecondFigure, int nDirection,
		CPoint nFirstPoint, CPoint nSecondPoint, CString strName, unsigned int id);
	~CLink();

	void DrawFigure(CDC* pDC);

	void SetVertice(int nNumberVertice, CPoint point);
	void SetFigure(CString strFigure, bool bFirstSecond);
	void SetPen();
	void SetDirection(int nDirection);

	CPoint GetVertice(int nVertice);
	CString GetFirstFigure();
	CString GetSecondFigure();
	CPoint* CLink::GetCoordinates();
	CString GetStrCoordinates();
	CString GetStrCenter();
	CString GetAngle();
	int GetDirection();

protected:
	int m_nVertices;
	CPoint m_vCoordinates[LINK_VERTICES];
	CString m_strFirstFigure;
	CString m_strSecondFigure;
	int m_nDirection;

	double GetArrowAngle(double fw, double fh);
	void PaintArrow(CPoint startPoint, CPoint endPoint, CDC* pDC);
};

