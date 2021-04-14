#include "pch.h"
#include "GraphicalWindow.h"
#include "EditorView.h"
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
	PenStyles = { PS_SOLID | PS_GEOMETRIC, PS_NULL, PS_DASH | PS_GEOMETRIC, PS_DOT | PS_GEOMETRIC, PS_DASHDOT | PS_GEOMETRIC,
		PS_DASHDOTDOT | PS_GEOMETRIC };
	m_nFigurePenStyles = 0;
	m_nFigureType = -1;
	m_crFigurePenColor = RGB(0, 0, 0);
	m_crFigureBrushColor = RGB(255, 255, 255);
	BrushStyles = { -1, -2, HS_VERTICAL, HS_HORIZONTAL, HS_CROSS, HS_BDIAGONAL, HS_FDIAGONAL, HS_DIAGCROSS };
	m_nFigureBrushStyles = 0;
	m_bFigureDone = TRUE;
	m_nSelectedFigure = -1;
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
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	//pDC->Ellipse(20,20,300,80);
	
	//delete[] pointArray;
	
	for (int i = 0; i < m_Figure.size(); i++)
	{
		if (m_Figure[i]->GetCanDraw())
		{
			m_Figure[i]->DrawFigure(pDC);
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
				SetFigureNameAndID();
				m_setNames.insert(m_FigureName);
				m_setID.insert(m_FigureID);
				m_Figure.push_back(new CEllipse(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				m_bFigureDone = FALSE;
				break;

			case FIGURE_RECTANGLE:
				SetFigureNameAndID();
				m_setNames.insert(m_FigureName);
				m_setID.insert(m_FigureID);
				m_Figure.push_back(new CRectangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				m_bFigureDone = FALSE;
				break;

			case FIGURE_TRIANGLE:
				if (m_Figure.empty())
				{
					SetFigureNameAndID();
					m_setNames.insert(m_FigureName);
					m_setID.insert(m_FigureID);
					m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
						BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				}
					
				else
				{
					nNumberVertice = m_Figure[m_Figure.size() - 1]->GetNumberVertices();
					if (nNumberVertice == 3 || nNumberVertice == -1)
					{
						SetFigureNameAndID();
						m_setNames.insert(m_FigureName);
						m_setID.insert(m_FigureID);
						m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
							BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
					}
						
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
			/*m_Figure[m_Figure.size() - 1]->m_vCoordinates[0] = point;
			m_bFigureDone = TRUE;
			break;*/

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
				m_setID.erase(_wtoi(m_Figure[m_Figure.size() - 1]->GetID()));
				m_setNames.erase(m_Figure[m_Figure.size() - 1]->GetName());
				m_Figure.pop_back();
				m_bFigureDone = TRUE;
			}
			MoveFigure(point);
			CEditorView* pView = static_cast<CEditorView*>(GetParent());
			pView->UpdateLinks(m_nSelectedFigure);
			UpdateList();
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
			if (point != m_Figure[m_Figure.size() - 1]->m_vCoordinates[0])
			{
				m_nSelectedFigure = m_Figure.size() - 1;
				m_Figure[m_nSelectedFigure]->SetCoordinates(point);
				//SetFigureNameAndID();
			}
			else
			{
				m_setID.erase(_wtoi(m_Figure[m_Figure.size() - 1]->GetID()));
				m_setNames.erase(m_Figure[m_Figure.size() - 1]->GetName());
				m_Figure.pop_back();
			}
				
			UpdateList();
			//m_nFigureType = -1;
			break;
		case FIGURE_TRIANGLE:
			if (m_Figure[m_Figure.size() - 1]->GetNumberVertices() == 3)
			{
				m_nSelectedFigure = m_Figure.size() - 1;
				m_Figure[m_nSelectedFigure]->SetCoordinates(point);
				UpdateList();
				m_bFigureDone = TRUE;
				//SetFigureNameAndID();
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
			m_Figure[m_nSelectedFigure]->Resize(true);
		else
			m_Figure[m_nSelectedFigure]->Resize(false);
		CEditorView* pView = static_cast<CEditorView*>(GetParent());
		pView->UpdateListView(TRUE, FALSE);
		pView->m_dlgFigureProperties.SetData();
		pView->UpdateLinks(m_nSelectedFigure);
		OnPaint();
	}
	return 1;

}

void CGraphicalWindow::UpdateList()
{
	//CWnd* = GetParent();
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateListView(TRUE);
	pView->m_dlgFigureProperties.SetData();
}

void CGraphicalWindow::SetFigureNameAndID()
{
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->OnEditName();
	pView->OnEditID();
}

void CGraphicalWindow::MoveFigure(CPoint point)
{
	if (!m_Figure.empty())
	{
		m_Figure[m_nSelectedFigure]->Move(point);
		CEditorView* pView = static_cast<CEditorView*>(GetParent());
		pView->m_dlgFigureProperties.SetData();
	}
}