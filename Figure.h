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
	void SetBrush();
	virtual void SetPen();
	virtual int GetNumberVertices();
	virtual void SetVertice(int nNumberVertice, CPoint point);
	void SetDlgAngle(int nAngle);
	void SetDlgColorValue(COLORREF crColor, bool bPenBrush);
	void SetDlgWidth(int nWidth);
	void SetDlgPenStyle(int nStyle);
	void SetDlgBrushStyle(int nStyle);
	void SetDlgName(CString strName);
	void SetDlgID(int nID);
	virtual void SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate);
	virtual void UpdateCoordinate(int nVertice);

	CString GetName();
	CString GetID();
	int GetWidth();
	int GetPenStyle();
	COLORREF GetPenColor();
	int GetBrushStyle();
	COLORREF GetBrushColor();
	virtual CString GetStrCenter();
	CPoint GetCenter();
	virtual CString GetStrCoordinates();
	virtual CPoint* GetCoordinates();
	virtual CPoint GetVertice(int nVertice);
	virtual CString GetAngle();
	CString CFigure::GetFigure();
	virtual CString GetFirstFigure();
	virtual CString GetSecondFigure();
	virtual void SetFigure(CString strFigure, bool bFirstSecond);
	virtual int GetDirection();
	virtual void SetDirection(int nDirection);

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
	CPen *m_ptrPen;
	CBrush *m_ptrBrush;
	//CGraphicalWindow *ptr;
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
	FIGURE_LINK,
	FIGURE_MOVE
};

enum RGB
{
	R_VALUE = 0,
	G_VALUE,
	B_VALUE
};

