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
	m_bFigureDone = TRUE;
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
	CRect rect(15, 15, 200, 200);
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rect, RGB(180, 243, 254));
	//pDC->Ellipse(20,20,300,80);
	
	//delete[] pointArray;
	
	for (int i = 0; i < m_Figure.size(); i++)
	{
		if (m_Figure[i]->GetCanDraw())
		{
			
			//switch (m_Figure[i]->GetFigureType())
			//{
			//case FIGURE_ELLIPSE:
			//	//if (m_Figure[i].m_vCoordinates.size() == 2)
			//	//{
			//	//pDC->Ellipse(m_Figure[i]->m_vCoordinates[0].x, m_Figure[i]->m_vCoordinates[0].y,
			//		//m_Figure[i]->m_vCoordinates[1].x, m_Figure[i]->m_vCoordinates[1].y);

			//	//m_bPaintNow = FALSE;
			////}
			//	//break;
			//case FIGURE_RECTANGLE:
			//	//if (m_Figure[i].m_vCoordinates.size() == 2)
			//	//{
			//	

			//	//m_bPaintNow = FALSE;
			////}
			////m_nFigureType = -1;
			//case FIGURE_TRIANGLE:
				m_Figure[i]->DrawFigure(pDC);
			/*	break;
			}*/
		}
		
	}
	//m_bLButtonDown = FALSE;
	//m_bLButtonUp = FALSE;
}


void CGraphicalWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nNumberVertice;
	if (m_bLButtonUp == TRUE)
	{
		if (m_bLButtonDown == FALSE || m_Figure.empty())
		{
			switch (m_nFigureType)
			{
			case FIGURE_ELLIPSE:
				m_Figure.push_back(new CEllipse(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));

				m_bFigureDone = FALSE;
				break;

			case FIGURE_RECTANGLE:
				m_Figure.push_back(new CRectangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));
				m_bFigureDone = FALSE;
				break;

			case FIGURE_TRIANGLE:
				if(m_Figure.empty())
					m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
						BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));
				else
				{
					nNumberVertice = m_Figure[m_Figure.size() - 1]->GetNumberVertices();
					if (nNumberVertice == 3 || nNumberVertice == -1)
						m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
							BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, L"", 0));
				}

				m_bFigureDone = FALSE;
				break;
			}
		}
		
		m_bPaintNow = FALSE;
		//if(!m_Figure.empty())
		switch (m_nFigureType) 
		{
		case FIGURE_ELLIPSE:
			m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
			m_bFigureDone = TRUE;
			break;

		case FIGURE_RECTANGLE:
			m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
			m_bFigureDone = TRUE;
			break;

		case FIGURE_TRIANGLE:
			nNumberVertice = m_Figure[m_Figure.size() - 1]->GetNumberVertices();
			if (nNumberVertice < 3)
			{
				m_Figure[m_Figure.size() - 1]->SetVertice(nNumberVertice, point);

			}
			break;

		case FIGURE_MOVE:
			if (!m_bFigureDone)
			{
				m_Figure.pop_back();
				m_bFigureDone = TRUE;
			}
				
			if (!m_Figure.empty())
				m_Figure[m_Figure.size() - 1]->Move(point);
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
		switch (m_nFigureType) {
		case FIGURE_ELLIPSE:
		case FIGURE_RECTANGLE:
			m_Figure[m_Figure.size() - 1]->SetCoordinates(point);
			//m_nFigureType = -1;
			break;
		case FIGURE_TRIANGLE:
			if (m_Figure[m_Figure.size() - 1]->GetNumberVertices() == 3)
			{
				m_Figure[m_Figure.size() - 1]->SetCoordinates(point);
				m_bFigureDone = TRUE;
			}
				
			break;
		}
		Invalidate();
		//KillTimer(ID_TIMER);
		//m_bPaintNow = FALSE;
		m_bLButtonDown = FALSE;
	}

	m_bLButtonUp = TRUE;
	m_bPaintNow = TRUE;
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
			m_Figure[m_Figure.size() - 1]->Resize(true);
		else
			m_Figure[m_Figure.size() - 1]->Resize(false);
		OnPaint();
	}
	return 1;

}