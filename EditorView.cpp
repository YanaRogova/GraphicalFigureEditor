
// ChildView.cpp : implementation of the CChildView class
//
#include <stdlib.h>
#include "pch.h"
#include "framework.h"
#include "GraphicalFigureEditor.h"
#include "EditorView.h"
#include "resource.h"
//#include "Figure.h"
#include "GraphicalWindow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_BUT_RECTANGLE		1300
#define ID_OUTPUT_WINDOW		1301
#define ID_BUT_ELLIPSE			1302
#define ID_CBOX_PEN_STYLES		1303
#define ID_ED_PEN_WIDTH			1304
#define ID_BUT_PEN_COLOR		1305
#define ID_BUT_BRUSH_COLOR		1306
#define ID_CBOX_BRUSH_STYLES	1307
#define ID_BUT_NORM_FIGURE		1308
#define ID_ED_FIGURE_ANGLE		1309
#define ID_BUT_LEFT_ROTATE		1310
#define ID_BUT_RIGHT_ROTATE		1311
#define ID_BUT_MOVE				1312
#define ID_BUT_TRIANGLE			1313
#define ID_STATIC_DRAWING_SPACE		1314
#define ID_FIGURE_LIST			1315
// CChildView

CEditorView::CEditorView()
{
	PenStylesNames = { L"Solid", L"Null" };
	PenStylesNamesEx = { L"Dashed", L"Dotted", L"Alternating dashes and dots", L"Alternating dashes and double dots" };
	BrushStylesNames = { L"Solid", L"Vertical hatch", L"Horizontal hatch", L"Horizontal and vertical crosshatch",
		L"Downward hatch at 45 degrees", L"Upward hatch at 45 degrees", L"Crosshatch at 45 degrees" };
}

CEditorView::~CEditorView()
{
}


BEGIN_MESSAGE_MAP(CEditorView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(ID_BUT_RECTANGLE, OnButtonRect)
	ON_COMMAND(ID_BUT_ELLIPSE, OnButtonEllipse)
	ON_CBN_SELCHANGE(ID_CBOX_PEN_STYLES, OnCBoxPenStyles)
	ON_EN_CHANGE(ID_ED_PEN_WIDTH, OnEditPenWidth)
	ON_COMMAND(ID_BUT_PEN_COLOR, OnButtonPenColor)
	ON_COMMAND(ID_BUT_BRUSH_COLOR, OnButtonBrushColor)
	ON_CBN_SELCHANGE(ID_CBOX_BRUSH_STYLES, OnCBoxBrushStyles)
	ON_COMMAND(ID_BUT_NORM_FIGURE, OnButtonNormalizeFigure)
	ON_WM_LBUTTONUP()
	//ON_EN_CHANGE(ID_ED_FIGURE_ANGLE, OnEditFigureAngle)
	ON_COMMAND(ID_BUT_LEFT_ROTATE, OnButtonLeftRotate)
	ON_COMMAND(ID_BUT_RIGHT_ROTATE, OnButtonRightRotate)
	ON_COMMAND(ID_BUT_MOVE, OnButtonMove)
	ON_COMMAND(ID_BUT_TRIANGLE, OnButtonTriangle)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	HBRUSH hbrush;
	hbrush = CreateSolidBrush(RGB(145, 237, 253));
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style |= WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), hbrush, nullptr);
	return TRUE;
}

void CEditorView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//dc.Ellipse(200, 200, 300, 350);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_DrawingSpace.Create(L"", WS_VISIBLE | WS_CHILD | WS_BORDER  /*| WS_VSCROLL | WS_HSCROLL | WS_SIZEBOX*/,
		CRect(7, 7, 395, 500), this, ID_STATIC_DRAWING_SPACE);

	m_GraphicalWindow.Create(L"", WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_NOTIFY /*| WS_VSCROLL | WS_HSCROLL | WS_SIZEBOX*/,
		CRect(10, 10, 390, 390), this, ID_OUTPUT_WINDOW);

	CString str;
	str.LoadString(IDS_BUT_RECTANGLE);
	m_ButRect.Create(str, WS_VISIBLE | WS_CHILD,
		CRect(400, 20, 500, 50), this, ID_BUT_RECTANGLE);

	m_ButTriangle.Create(L"Triangle", WS_VISIBLE | WS_CHILD,
		CRect(510, 20, 600, 50), this, ID_BUT_TRIANGLE);

	m_ButEllipse.Create(L"Ellipse", WS_VISIBLE | WS_CHILD ,
		CRect(400, 70, 500, 100), this, ID_BUT_ELLIPSE);

	m_CBoxPenStyles.Create(WS_VISIBLE | WS_CHILD  | WS_VSCROLL | CBS_DROPDOWNLIST |WS_VSCROLL,
		CRect(400, 120, 710, 300), this, ID_CBOX_PEN_STYLES);
	for (int i = 0; i < PenStylesNames.size(); i++)
	{
		m_CBoxPenStyles.InsertString(i, PenStylesNames[i]);
	}
	if (m_GraphicalWindow.m_nFigurePenWidth <= 1)
	{
		for (int i = 0; i < PenStylesNamesEx.size(); i++)
		{
			m_CBoxPenStyles.InsertString(i+ PenStylesNames.size(), PenStylesNamesEx[i]);
		}
	}
	m_CBoxPenStyles.SetCurSel(0);

	m_CBoxBrushStyles.Create(WS_VISIBLE | WS_CHILD  | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(400, 170, 710, 350), this, ID_CBOX_BRUSH_STYLES);
	for (int i = 0; i < BrushStylesNames.size(); i++)
	{
		m_CBoxBrushStyles.InsertString(i, BrushStylesNames[i]);
	}
	m_CBoxBrushStyles.SetCurSel(0);

	m_EditPenWidth.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER,
		CRect(400, 220, 500, 250), this, ID_ED_PEN_WIDTH);
	m_EditPenWidth.SetWindowTextW(L"1");

	m_ButChousePenColor.Create(L"Pen", WS_VISIBLE | WS_CHILD ,
		CRect(400, 270, 440, 300), this, ID_BUT_PEN_COLOR);

	m_ButChouseBrushColor.Create(L"Brush", WS_VISIBLE | WS_CHILD ,
		CRect(450, 270, 500, 300), this, ID_BUT_BRUSH_COLOR);

	m_ButNormalizeFigure.Create(L"Normalize", WS_VISIBLE | WS_CHILD ,
		CRect(400, 320, 500, 350), this, ID_BUT_NORM_FIGURE);

	m_ButMove.Create(L"Move", WS_VISIBLE | WS_CHILD ,
		CRect(510, 320, 560, 350), this, ID_BUT_MOVE);

	m_EditFigureAngle.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER,
		CRect(400, 370, 450, 400), this, ID_ED_FIGURE_ANGLE);
	m_EditFigureAngle.SetWindowTextW(L"0");

	m_ButLeftRotate.Create(L"Left", WS_VISIBLE | WS_CHILD ,
		CRect(460, 370, 500, 400), this, ID_BUT_LEFT_ROTATE);

	m_ButRigthRotate.Create(L"Right", WS_VISIBLE | WS_CHILD ,
		CRect(510, 370, 560, 400), this, ID_BUT_RIGHT_ROTATE);

	/*m_FigureList.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, ,
		this, ID_FIGURE_LIST);
	m_FigureList.InsertColumn(0, L"�", LVCFMT_LEFT, 40);*/
	CRect rect(750, 10, 1400, 400);
	m_List.Create( LVS_REPORT | WS_VISIBLE| LVS_EX_GRIDLINES , rect, this, 100);
	//m_List.Create(L"", L"", WS_VISIBLE | WS_CHILD, rect, this, ID_FIGURE_LIST);
	//m_List.OnInitialUpdate();
	std::vector<CString> m_strColomns = {L"�", L"Name", L"ID", L"Figure type", L"Center", L"Coordinates", L"Angle"};
	m_List.InsertColumn(0, m_strColomns[0], LVCFMT_LEFT, 30);
	m_List.InsertColumn(1, m_strColomns[1], LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, m_strColomns[2], LVCFMT_LEFT, 30);
	m_List.InsertColumn(3, m_strColomns[3], LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, m_strColomns[4], LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, m_strColomns[5], LVCFMT_LEFT, 270);
	m_List.InsertColumn(6, m_strColomns[6], LVCFMT_LEFT, 70);
	
	/*for (int i = 0; i < m_strColomns.size(); i++)
	{
		m_List.InsertColumn(i, m_strColomns[i], LVCFMT_LEFT, rect.Width() / m_strColomns.size());
	}*/
	UpdateListView();
	/*LV_ITEM item;
	item.iItem = 0;
	item.iImage = 0;
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	item.iSubItem = 0;*/
	

	return 0;

}

void CEditorView::OnButtonRect()
{
	m_GraphicalWindow.SetFigureType(FIGURE_RECTANGLE);
}

void CEditorView::OnButtonEllipse()
{
	m_GraphicalWindow.SetFigureType(FIGURE_ELLIPSE);
}

void CEditorView::OnCBoxPenStyles()
{
	m_GraphicalWindow.m_nFigurePenStyles = m_CBoxPenStyles.GetCurSel();
}

void CEditorView::OnCBoxBrushStyles()
{
	m_GraphicalWindow.m_nFigureBrushStyles = m_CBoxBrushStyles.GetCurSel();
}

void CEditorView::OnEditPenWidth()
{
	int nOldEditState = m_GraphicalWindow.m_nFigurePenWidth;
	CString strEditText;
	m_EditPenWidth.GetWindowText(strEditText);
	m_GraphicalWindow.m_nFigurePenWidth = _wtoi(strEditText);

	if ((nOldEditState > 1 && m_GraphicalWindow.m_nFigurePenWidth <= 1) ||
		(nOldEditState <= 1 && m_GraphicalWindow.m_nFigurePenWidth > 1))
	{
		m_CBoxPenStyles.ResetContent();

		for (int i = 0; i < PenStylesNames.size(); i++)
		{
			m_CBoxPenStyles.InsertString(i, PenStylesNames[i]);
		}

		if (m_GraphicalWindow.m_nFigurePenWidth <= 1)
		{
			for (int i = 0; i < PenStylesNamesEx.size(); i++)
			{
				m_CBoxPenStyles.InsertString(i + PenStylesNames.size(), PenStylesNamesEx[i]);
			}
		}
		m_CBoxPenStyles.SetCurSel(0);
	}
	OnCBoxPenStyles();	//to update ComboBox state
}

void CEditorView::OnButtonPenColor()
{
	COLORREF crColor = GetColor();
	if (crColor != -1)
	{
		m_GraphicalWindow.m_crFigurePenColor = crColor;
	}
}

void CEditorView::OnButtonBrushColor()
{
	COLORREF crColor = GetColor();
	if (crColor != -1)
	{
		m_GraphicalWindow.m_crFigureBrushColor = crColor;
	}
}

COLORREF CEditorView::GetColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		return dlg.GetColor();
	return -1;
}

void CEditorView::OnButtonNormalizeFigure()
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->Normalize();
	m_GraphicalWindow.OnPaint();
	UpdateListView();
}

void CEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_GraphicalWindow.m_bLButtonUp = TRUE;
}

void CEditorView::OnEditFigureAngle()
{
	
	
}

void CEditorView::OnButtonLeftRotate()
{
	CString strEditText;
	m_EditFigureAngle.GetWindowText(strEditText);
	if (!m_GraphicalWindow.m_Figure.empty())
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->SetAngle(_wtoi(strEditText));
	m_GraphicalWindow.OnPaint();
	UpdateListView();
}

void CEditorView::OnButtonRightRotate()
{
	CString strEditText;
	m_EditFigureAngle.GetWindowText(strEditText);
	if (!m_GraphicalWindow.m_Figure.empty())
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->SetAngle(-_wtoi(strEditText));
	m_GraphicalWindow.OnPaint();
	UpdateListView();
}

void CEditorView::OnButtonMove()
{
	m_GraphicalWindow.SetFigureType(FIGURE_MOVE);
	UpdateListView();
}

void CEditorView::OnButtonTriangle()
{
	m_GraphicalWindow.SetFigureType(FIGURE_TRIANGLE);
	//MoveFigureElement(m_GraphicalWindow.m_Figure.size() - 1, 0);
	UpdateListView();
}

void CEditorView::UpdateListView()
{
	m_List.DeleteAllItems();
	CString str;
	for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
	{
		str.Format(L"%d", i+1);
		int Index = m_List.InsertItem(0, str);
		m_List.SetItemText(Index, 1, m_GraphicalWindow.m_Figure[i]->GetName());
		m_List.SetItemText(Index, 2, m_GraphicalWindow.m_Figure[i]->GetID());
		m_List.SetItemText(Index, 3, m_GraphicalWindow.m_Figure[i]->GetFigure());
		m_List.SetItemText(Index, 4, m_GraphicalWindow.m_Figure[i]->GetCenter());
		m_List.SetItemText(Index, 5, m_GraphicalWindow.m_Figure[i]->GetCoordinates());
		m_List.SetItemText(Index, 6, m_GraphicalWindow.m_Figure[i]->GetAngle());
	}
}

void CEditorView::MoveFigureElement(int nCurrentPosition, int nNewPosition)
{
	CFigure* figure = m_GraphicalWindow.m_Figure[nCurrentPosition];
	m_GraphicalWindow.m_Figure.erase(m_GraphicalWindow.m_Figure.begin() + nCurrentPosition);
	m_GraphicalWindow.m_Figure.insert(m_GraphicalWindow.m_Figure.begin() + nNewPosition, figure);
}