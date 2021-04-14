#pragma once
#include "Figure.h"
class CLink : public CFigure
{
public:
	CLink(int nPenStyle, int nPenWidth, COLORREF crPenColor, CString strfirstFigure, CString strsecondFigure, int nDirection,
		CPoint nFirstPoint, CPoint nSecondPoint, CString strName, unsigned int id);
	~CLink();
	//void CLink::NewCoordinates(int xHalfLength, int yHalfLength);
	void PaintArrow(CPoint startPoint, CPoint endPoint, CDC* pDC);
	void DrawFigure(CDC* pDC);
	void SetVertice(int nNumberVertice, CPoint point);
	CString GetFirstFigure();
	CString GetSecondFigure();
	void SetFigure(CString strFigure, bool bFirstSecond);
	CPoint GetVertice(int nVertice);
	void SetPen();
	CString GetStrCoordinates();
	CString GetStrCenter();
	CString GetAngle();
	int GetDirection();
	void SetDirection(int nDirection);
	CPoint* CLink::GetCoordinates();

protected:
	int m_nVertices;
	CPoint m_vCoordinates[2];
	CString m_strFirstFigure;
	CString m_strSecondFigure;
	int m_nDirection;

	double GetArrowAngle(double fw, double fh);
};

