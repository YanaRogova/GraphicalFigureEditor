#include "pch.h"
#include "GraphicalWindow.h"
#include "EditorView.h"
#include <string>


BEGIN_MESSAGE_MAP(CGraphicalWindow, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	/*ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SETCURSOR()*/
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
	m_bPictureNotSaved = FALSE;
}

CGraphicalWindow::~CGraphicalWindow()
{
}

//void CGraphicalWindow::OnDraw(CDC* pDC)
//{}

void CGraphicalWindow::OnPaint()
{
	CWnd::OnPaint();
	CDC* pDCPaint = GetDC();
	CMemDC memDC(*pDCPaint, this);
	CDC* pDC = &memDC.GetDC();
	
	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
	
	for (int i = 0; i < m_Figure.size(); i++)
	{
		if (m_Figure[i]->GetCanDraw())
		{
			m_Figure[i]->DrawFigure(pDC);
		}
	}
}

void CGraphicalWindow::PreCreateFigure()
{
	SetFigureNameAndID();
	m_setNames.insert(m_FigureName);
	m_setID.insert(m_FigureID);
	m_bPictureNotSaved = TRUE;
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
				PreCreateFigure();
				m_Figure.push_back(new CEllipse(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				m_bFigureDone = FALSE;
				break;

			case FIGURE_RECTANGLE:
				PreCreateFigure();
				m_Figure.push_back(new CRectangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
					BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				m_bFigureDone = FALSE;
				break;

			case FIGURE_TRIANGLE:
				if (m_Figure.empty())
				{
					PreCreateFigure();
					m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
						BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));
				}
					
				else
				{
					nNumberVertice = m_Figure[m_Figure.size() - 1]->GetNumberVertices();
					if (nNumberVertice == 3 || nNumberVertice == -1)
					{
						PreCreateFigure();
						m_Figure.push_back(new CTriangle(PenStyles[m_nFigurePenStyles], m_nFigurePenWidth, m_crFigurePenColor,
							BrushStyles[m_nFigureBrushStyles], m_crFigureBrushColor, m_FigureName, m_FigureID));

					}
						
				}

				m_bFigureDone = FALSE;
				break;
			}
		}
		
		m_bPaintNow = FALSE;
		switch (m_nFigureType) 
		{
		case FIGURE_ELLIPSE:
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

void CGraphicalWindow::CStringToFile(CString &string, CFile& file)
{
	std::wstring wstrNewString = string;
	std::string strNewString(wstrNewString.begin(), wstrNewString.end());
	strNewString += "\n";
	file.Write(strNewString.c_str(), strNewString.length());
}

void CGraphicalWindow::NumberToFile(int& num, CFile& file)
{
	std::string strNewString = std::to_string(num);
	strNewString += "\n";
	file.Write(strNewString.c_str(), strNewString.length());
}

void CGraphicalWindow::NumberToFile(unsigned long& num, CFile& file)
{
	std::string strNewString = std::to_string(num);
	strNewString += "\n";
	file.Write(strNewString.c_str(), strNewString.length());
}

void CGraphicalWindow::SaveElement(int nNumberElement, CFile &file)
{
	int strFigure = m_Figure[nNumberElement]->GetFigureType();
	NumberToFile(strFigure, file);
	CString string = m_Figure[nNumberElement]->GetName();
	CStringToFile(string, file);
	string = m_Figure[nNumberElement]->GetID();
	CStringToFile(string, file);
	int num = m_Figure[nNumberElement]->GetWidth();
	NumberToFile(num, file);
	num = m_Figure[nNumberElement]->GetPenStyle();
	NumberToFile(num, file);
	COLORREF color = m_Figure[nNumberElement]->GetPenColor();
	NumberToFile(color, file);
	if (strFigure == FIGURE_RECTANGLE || strFigure == FIGURE_TRIANGLE || strFigure == FIGURE_ELLIPSE)
	{
		num = m_Figure[nNumberElement]->GetBrushStyle();
		NumberToFile(num, file);
		color = m_Figure[nNumberElement]->GetBrushColor();
		NumberToFile(color, file);
		string = m_Figure[nNumberElement]->GetAngle();
		CStringToFile(string, file);
	}
	else if (strFigure == FIGURE_LINK)
	{
		string = m_Figure[nNumberElement]->GetFirstFigure();
		CStringToFile(string, file);
		string = m_Figure[nNumberElement]->GetSecondFigure();
		CStringToFile(string, file);
		num = m_Figure[nNumberElement]->GetDirection();
		NumberToFile(num, file);
	}

	m_Figure[nNumberElement]->SetReturnCoordinates(TRUE);
	string = m_Figure[nNumberElement]->GetStrCoordinates();
	m_Figure[nNumberElement]->SetReturnCoordinates(FALSE);
	std::wstring wstrNewString = string;
	std::string strNewString(wstrNewString.begin(), wstrNewString.end());
	int nEndIndex = 0;
	while (strNewString.find("(", nEndIndex) != std::string::npos)
	{
		std::string strCoordinate;
		int nStartIndex = strNewString.find("(", nEndIndex) + 1;
		nEndIndex = strNewString.find(", ", nStartIndex);
		strCoordinate = strNewString.substr(nStartIndex, nEndIndex - nStartIndex) + "\n";
		file.Write(strCoordinate.c_str(), strCoordinate.length());

		nStartIndex = nEndIndex + 2;
		nEndIndex = strNewString.find(")", nStartIndex);
		strCoordinate = strNewString.substr(nStartIndex, nEndIndex - nStartIndex) + "\n";
		file.Write(strCoordinate.c_str(), strCoordinate.length());

		if (strFigure == FIGURE_RECTANGLE || strFigure == FIGURE_ELLIPSE)
			nEndIndex = strNewString.find("(", nEndIndex) + 1;
	}	
}

void CGraphicalWindow::SavePicture(CString strFileName)
{
	CFile FilePicture;
	FilePicture.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
	for (int i = 0; i < m_Figure.size(); i++)
	{
		SaveElement(i, FilePicture);
	}
	FilePicture.Close();
	m_bPictureNotSaved = FALSE;
}

bool CGraphicalWindow::CreateElement(CStdioFile& file)
{
	CString string;
	int nFigure, nID, nAngle = 0, nPenWidth, nPenType, nBrushType, nDirection;
	COLORREF crPenColor, crBrushColor;
	CPoint point0, point1, point2;
	CString strName, strFirstFigure, strSecondFigure;

	int nEnd = file.ReadString(string);
	if (nEnd == 0)
		return TRUE;

	nFigure = _wtoi(string);
	file.ReadString(strName);
	file.ReadString(string);
	nID = _wtoi(string);
	file.ReadString(string);
	nPenWidth = _wtoi(string);
	file.ReadString(string);
	nPenType = _wtoi(string);
	file.ReadString(string);
	crPenColor = wcstoul(string, NULL, 10);
	if (nFigure == FIGURE_RECTANGLE || nFigure == FIGURE_TRIANGLE || nFigure == FIGURE_ELLIPSE)
	{
		file.ReadString(string);
		nBrushType = _wtoi(string);
		file.ReadString(string);
		crBrushColor = wcstoul(string, NULL, 10);
		file.ReadString(string);
		nAngle = _wtoi(string);
	}
	else if (nFigure == FIGURE_LINK)
	{
		file.ReadString(strFirstFigure);
		file.ReadString(strSecondFigure);
		file.ReadString(string);
		nDirection = _wtoi(string);
	}
	file.ReadString(string);
	point0.x = _wtoi(string);
	file.ReadString(string);
	point0.y = _wtoi(string);
	file.ReadString(string);
	point1.x = _wtoi(string);
	file.ReadString(string);
	point1.y = _wtoi(string);
	if (nFigure == FIGURE_TRIANGLE)
	{
		file.ReadString(string);
		point2.x = _wtoi(string);
		file.ReadString(string);
		point2.y = _wtoi(string);
	}
	
	SetFigureNameAndID();
	m_setNames.insert(strName);
	m_setID.insert(nID);
	m_nSelectedFigure++;
	switch (nFigure)
	{
	case FIGURE_RECTANGLE:
		m_Figure.push_back(new CRectangle(nPenType, nPenWidth, crPenColor, nBrushType, crBrushColor, strName, nID));
		m_Figure[m_nSelectedFigure]->m_vCoordinates[0] = point0;
		m_bFigureDone = TRUE;
		m_Figure[m_nSelectedFigure]->SetCoordinates(point1);
		break;
		
	case FIGURE_ELLIPSE:
		m_Figure.push_back(new CEllipse(nPenType, nPenWidth, crPenColor, nBrushType, crBrushColor, strName, nID));
		m_Figure[m_nSelectedFigure]->m_vCoordinates[0] = point0;
		m_bFigureDone = TRUE;
		m_Figure[m_nSelectedFigure]->SetCoordinates(point1);
		break;

	case FIGURE_TRIANGLE:
		m_Figure.push_back(new CTriangle(nPenType, nPenWidth, crPenColor, nBrushType, crBrushColor, strName, nID));
		m_Figure[m_nSelectedFigure]->SetVertice(0, point0);
		m_Figure[m_nSelectedFigure]->SetVertice(1, point1);
		m_Figure[m_nSelectedFigure]->SetVertice(2, point2);
		m_Figure[m_nSelectedFigure]->SetCoordinates(point0);
		m_bFigureDone = TRUE;
		break;

	case FIGURE_LINK:
		m_Figure.push_back(new CLink(nPenType, nPenWidth, crPenColor, strFirstFigure, strFirstFigure,
			nDirection, point0, point1, strName, nID));
		break;
	}

	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateAngle(nAngle);
}

void CGraphicalWindow::OpenPicture(CString strFileName)
{
	m_nSelectedFigure = -1;
	CStdioFile FilePicture;
	FilePicture.Open(strFileName, CFile::modeRead);
	std::string string;
	bool bEndFile = FALSE;

	m_setID.clear();
	m_setNames.clear();
	m_Figure.clear();
	while (!bEndFile)
	{
		bEndFile = CreateElement(FilePicture);
	}
	FilePicture.Close();
	m_nSelectedFigure = m_Figure.size() - 1;
	OnPaint();
	UpdateList();

}

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
		m_bPictureNotSaved = TRUE;
	}
}

bool CGraphicalWindow::PictureNotSaved()
{
	return m_bPictureNotSaved;
}

void CGraphicalWindow::SetPictureNotSaved(bool bNotSaved)
{
	m_bPictureNotSaved = bNotSaved;
}


void CGraphicalWindow::DeleteFigure()
{
	m_setID.erase(_wtoi(m_Figure[m_nSelectedFigure]->GetID()));
	m_setNames.erase(m_Figure[m_nSelectedFigure]->GetName());
	for (int i = 0; i < m_Figure.size(); i++)
	{
		if (m_Figure[i]->GetFigureType() == FIGURE_LINK)
			if (m_Figure[i]->GetFirstFigure() == m_Figure[m_nSelectedFigure]->GetName() ||
				m_Figure[i]->GetSecondFigure() == m_Figure[m_nSelectedFigure]->GetName())
			{
				m_setID.erase(_wtoi(m_Figure[i]->GetID()));
				m_setNames.erase(m_Figure[i]->GetName());
				m_Figure.erase(m_Figure.begin() + i);
				i--;
			}
	}
	m_Figure.erase(m_Figure.begin() + m_nSelectedFigure);

	m_nSelectedFigure = 0;

	m_bPictureNotSaved = TRUE;
}

//
//void CGraphicalWindow::CreateVerticalScrollbar(int nStartX, int nStartY, int m_nWidth, int m_nHeight)
//{
//	ModifyStyle(NULL, WS_VSCROLL | WS_HSCROLL);
//	SetScrollRange(SB_VERT, nStartY, nStartY + m_nHeight, TRUE);
//	SetScrollRange(SB_HORZ, nStartX, nStartX + m_nWidth, TRUE);
//	pos = nStartY;
//	/*SetScrollPos(SB_VERT, nStartY);
//	SetScrollPos(SB_HORZ, nStartX);*/
//	//SetScrollInfo(SB_VERT, )
//}
//
//void CGraphicalWindow::CreateHorizontalScrollbar(int m_nWidth, int m_nHeight)
//{
//	ModifyStyle(NULL, WS_VSCROLL | WS_HSCROLL);
//	SetScrollRange(SB_VERT, 0, m_nHeight, TRUE);
//	SetScrollRange(SB_HORZ, 0, m_nWidth, TRUE);
//}
//
//void CGraphicalWindow::OnVScroll(UINT SBCode, UINT Pos, CScrollBar* SB)
//{
//	//CWnd::OnVScroll(SBCode, Pos, SB);
//	SB->SetScrollPos(SB_VERT, 40);
//	pos = Pos;
//}
//
//
//void CGraphicalWindow::OnHScroll(UINT SBCode, UINT Pos, CScrollBar* SB)
//{
//	//CWnd::OnHScroll(SBCode, Pos, SB);
//}
//
//BOOL CGraphicalWindow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
//	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW)); // установить курсор, который взять из системы
//	return TRUE;
//}