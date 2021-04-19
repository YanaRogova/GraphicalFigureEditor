#pragma once
#include <afxwin.h>
#include <array>
#include "NameID.h"

#define PI 3.14159265 

class CFigure
{
public:
	
	CFigure(int nFigureType, int nPenStyle, int nPenWidth, COLORREF crPenColor,
		int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id);
	virtual ~CFigure();

	void SetAngle(int nAngle);
	void SetBrush();
	void SetDlgAngle(int nAngle);
	void SetDlgColorValue(COLORREF crColor, bool bPenBrush);
	void SetDlgWidth(int nWidth);
	void SetDlgPenStyle(int nStyle);
	void SetDlgBrushStyle(int nStyle);
	void SetDlgName(CString strName);
	void SetDlgID(int nID);
	void SetReturnCoordinates(bool bZeroAngle);
	CString GetName();
	CString GetID();
	int GetWidth();
	int GetPenStyle();
	COLORREF GetPenColor();
	int GetBrushStyle();
	COLORREF GetBrushColor();
	CString GetFigure();
	CPoint GetCenter();
	int GetFigureType();
	bool GetCanDraw();
	void Move(CPoint point);

	virtual void DrawFigure(CDC* pDC);
	virtual void Resize(bool bMoreLess);
	virtual void Normalize();
	virtual void Rotate();
	virtual void UpdateCoordinate(int nVertice);	

	virtual CString GetStrCenter();
	virtual int GetNumberVertices();
	virtual CString GetStrCoordinates();
	virtual CPoint* GetCoordinates();
	virtual CPoint GetVertice(int nVertice);
	virtual CString GetAngle();
	virtual CString GetFirstFigure();
	virtual CString GetSecondFigure();
	virtual int GetDirection();

	virtual void SetDirection(int nDirection);
	virtual void SetCoordinates(CPoint point);
	virtual void SetVertice(int nNumberVertice, CPoint point);
	virtual void SetDlgCoordinate(int nVertice, bool bXOrY, int nCoordinate);
	virtual void SetFigure(CString strFigure, bool bFirstSecond);
	virtual void SetPen();

protected:
	CPoint RotatePoint(double x, double y);
	virtual void NewCoordinates(int xHalfLength, int yHalfLength);

protected:
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
	bool m_bReturnNotRotateCoordinates;
	int m_HScrollPosition;
	int m_VScrollPosition;

	CNameID m_figureNameID;

public:
	CPoint m_vCoordinates[4];
	CPoint m_vAngleCoordinates[4];
	CPoint m_CenterCoordinates;
	double m_xHalfLength;
	double m_yHalfLength;
	void SetHScrollPosition(int nPosition);
	void SetVScrollPosition(int nPosition);
	
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

