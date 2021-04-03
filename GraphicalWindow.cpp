#include "pch.h"
#include "GraphicalWindow.h"

#define ID_TIMER	2000


BEGIN_MESSAGE_MAP(CGraphicalWindow, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	//ON_WM_MOUSEMOVE()
	//ON_WM_TIMER()
END_MESSAGE_MAP()

CGraphicalWindow::CGraphicalWindow()
{
	m_bPaintNow = FALSE;
	m_bLButtonDown = FALSE;
	m_bLButtonUp = TRUE;
	PenStyles = { PS_SOLID, PS_NULL, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT};
	m_nFigurePenStyles = 0;
	m_nFigureType = -1;
	m_crFigurePenColor = RGB(0, 0, 0);
	m_crFigureBrushColor = RGB(255, 255, 255);
	BrushStyles = { -1, HS_VERTICAL, HS_HORIZONTAL, HS_CROSS, HS_BDIAGONAL, HS_FDIAGONAL, HS_DIAGCROSS };
	m_nFigureBrushStyles = 0;
}

CGraphicalWindow::~CGraphicalWindow()
{
}

void CGraphicalWindow::OnPaint()
{
	CWnd::OnPaint(); //for work with CColorDialog
	CDC* pDCPaint = GetDC();
	CMemDC memDC(*pDCPaint, this);
	CDC* pDC = &memDC.GetDC();
	//CDC* pDC = GetDC();
	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rect, RGB(180, 243, 254));
	//pDC->Ellipse(20,20,300,80);
	POINT* pointArray;
	BYTE* pointType;
	/*pointArray = new POINT[4 * 3 + 1];
	long x[] = {70,80,90,100,110,120,130,120,110,100,90,80,70};
	long y[] = {100,107,109,110,109,107,100,93,91,90,91,93,100};
	for (int i = 0; i < (4 * 3 + 1); i++)
	{
		pointArray[i].x = x[i];
		pointArray[i].y = y[i];
	}
	pDC->PolyBezier(pointArray, 4 * 3 + 1);*/
	pointArray = new POINT[2 * 3 + 1];
	long x[] = { 60,20,100,140,180,100,60 };
	long y[] = { 100,180,220,140,60,20,100 };
	for (int i = 0; i < (2 * 3 + 1); i++)
	{
		pointArray[i].x = x[i];
		pointArray[i].y = y[i];
	}
	pointType = new BYTE[2 * 3 + 1];
	for (int i = 0; i < (2 * 3 + 1); i++)
	{
		if (i == 0)
			pointType[i] = PT_MOVETO;
		else if (i == 2 * 3)
			pointType[i] = PT_BEZIERTO | PT_CLOSEFIGURE;
		else
			pointType[i] = PT_BEZIERTO;
	}
	CBrush b;
	b.CreateHatchBrush(1, RGB(255,0,0));
	pDC->SelectObject(&b);
	pDC->BeginPath();
	pDC->PolyBezier(pointArray, 2 * 3 + 1);
	//pDC->PolyDraw(pointArray, pointType, 2 * 3 + 1);
	//pDC->CloseFigure();
	pDC->EndPath();
	pDC->FillPath();
	pDC->PolyBezier(pointArray, 2 * 3 + 1);

	//delete[] pointArray;
	
	for (int i = 0; i < m_Figure.size(); i++)
	{
		if (m_Figure[i]->GetCanDraw())
		{
			
			switch (m_Figure[i]->GetFigureType())
			{
			case FIGURE_ELLIPSE:
				//if (m_Figure[i].m_vCoordinates.size() == 2)
				//{
				pDC->Ellipse(m_Figure[i]->m_vCoordinates[0].x, m_Figure[i]->m_vCoordinates[0].y,
					m_Figure[i]->m_vCoordinates[1].x, m_Figure[i]->m_vCoordinates[1].y);

				//m_bPaintNow = FALSE;
			//}
				break;
			case FIGURE_RECTANGLE:
				//if (m_Figure[i].m_vCoordinates.size() == 2)
				//{
				m_Figure[i]->DrawFigure(pDC);

				//m_bPaintNow = FALSE;
			//}
			//m_nFigureType = -1;
				break;
			case FIGURE_TRIANGLE:
				break;
			}
		}
		
	}
	//m_bLButtonDown = FALSE;
	//m_bLButtonUp = FALSE;

	
	
	
}


void CGraphicalWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bLButtonUp == TRUE)
	{
		if (m_bLButtonDown == FALSE || m_Figure.empty())
		{
			switch (m_nFigureType)
			{
			case FIGURE_ELLIPSE:
				break;
			case FIGURE_RECTANGLE:
				m_Figure.push_back(new CRectangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));
				//m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
				break;
			/*case FIGURE_TRIANGLE:
				m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));*/
			}
		}
		
		m_bPaintNow = FALSE;
		//if(!m_Figure.empty())
		switch (m_nFigureType) 
		{
		case FIGURE_ELLIPSE:
			m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
			break;

		case FIGURE_RECTANGLE:
			m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
			break;
		case FIGURE_MOVE:
			if (!m_Figure.empty())
				m_Figure[0]->Move(point);
			break;
		}
			//SetTimer(ID_TIMER, 10000, NULL);
	}

	m_bLButtonDown = TRUE;
	m_bLButtonUp = FALSE;
}

void CGraphicalWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nFigureType >= 0 && m_bLButtonUp == FALSE && m_bLButtonDown == TRUE)
	{
		m_bLButtonUp = TRUE;
		m_bPaintNow = TRUE;
		switch (m_nFigureType) {
		case FIGURE_ELLIPSE:
		case FIGURE_RECTANGLE:
			m_Figure[m_Figure.size() - 1]->SetCoordinates(point);
			//m_nFigureType = -1;
			break;
		}
		Invalidate();
		//KillTimer(ID_TIMER);
		//m_bPaintNow = FALSE;
		m_bLButtonDown = FALSE;

		//else
			//m_Figure.pop_back();
	}
}

void CGraphicalWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	//
	//m_bPaintNow = TRUE;
	//switch (m_nFigureType) {
	//case FIGURE_ELLIPSE:
	//case FIGURE_RECTANGLE:
	//	m_Figure[m_Figure.size() - 1].SetCoordinates(point);
	//	//m_nFigureType = -1;
	//	break;
	//}
	
}

//void CGraphicalWindow::OnTimer(UINT_PTR time)
//{
//	m_bPaintNow = TRUE;
//	CPoint point;
//	GetCursorPos(&point);
//	m_Figure[m_Figure.size() - 1].SetCoordinates(point);
//	Invalidate();
//}




void CGraphicalWindow::SetFigureType(int nFigureType)
{
	m_nFigureType = nFigureType;
}

BOOL CGraphicalWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	
	if (!m_Figure.empty())
	{
		if(zDelta > 0)
			m_Figure[0]->Resize(true);
		else
			m_Figure[0]->Resize(false);
		OnPaint();
	}
	return 1;

}