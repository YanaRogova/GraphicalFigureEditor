#include "pch.h"
#include "Triangle.h"

CTriangle::CTriangle(int nPenStyle, int nPenWidth, COLORREF crPenColor,
	int nBrushStyle, COLORREF crBrushColor, CString strName, unsigned int id) :
	CFigure(FIGURE_RECTANGLE, nPenStyle, nPenWidth, crPenColor, nBrushStyle, crBrushColor, strName, id)
{
	m_nVertices = 3;
	/*m_nPenStyle = nPenStyle;
	m_nPenWidth = nPenWidth;
	m_crPenColor = crPenColor;
	m_nBrushStyle = nBrushStyle;
	m_crBrushColor = crBrushColor;*/
}