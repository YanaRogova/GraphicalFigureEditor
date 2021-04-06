#pragma once
#include <afxwin.h>
#include <array>
#include "NameID.h"

#define PI 3.14159265 
//
//
//class CConnectLine : public CLine
//{
//protected:
//	int m_nDirection;
//	CNameID m_connectLineNameID;
//public:
//	CConnectLine();
//	virtual ~CConnectLine();
//
//};



class CFigure
{
protected:
	CNameID m_figureNameID;
	CPoint RotatePoint(double x, double y);
	virtual void NewCoordinates(int xHalfLength, int yHalfLength);
public:
	
	CFigure(int nFigureType, int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CFigure();
	virtual void SetCoordinates(CPoint point);
	virtual void DrawFigure(CDC* pDC);
	int GetFigureType();
	bool GetCanDraw();
	void Move(CPoint point);
	virtual void Resize(bool bMoreLess);
	virtual void Normalize();
	virtual void Rotate();
	void SetAngle(int nAngle);
	void SetBrushAndPen();
	virtual int GetNumberVertices();
	virtual void SetVertice(int nNumberVertice, CPoint point);

	CString GetName();
	CString GetID();
	CString GetCenter();
	virtual CString GetCoordinates();
	CString GetAngle();
	CString CFigure::GetFigure();

protected:
	//int m_nVertices;
	int m_nFigureType;
	bool m_bCanDraw;
	int m_nPenStyle; 
	int m_nPenWidth; 
	COLORREF m_crPenColor;
	int m_nBrushStyle;
	COLORREF m_crBrushColor;
	int m_nAngle;
	bool bLeftRightRotate;
	CPen m_Pen;
	CBrush m_Brush;
public:
	CPoint m_vCoordinates[4];
	CPoint m_vAngleCoordinates[4];
	CPoint m_CenterCoordinates;
	double m_xHalfLength;
	double m_yHalfLength;
	
};


enum FigureType
{
	FIGURE_ELLIPSE = 0,
	FIGURE_RECTANGLE,
	FIGURE_TRIANGLE,
	FIGURE_MOVE
};

