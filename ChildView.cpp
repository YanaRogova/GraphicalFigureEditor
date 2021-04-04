
// ChildView.cpp : implementation of the CChildView class
//
#include <stdlib.h>
#include "pch.h"
#include "framework.h"
#include "GraphicalFigureEditor.h"
#include "ChildView.h"
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
// CChildView

CChildView::CChildView()
{
	PenStylesNames = { L"Solid", L"Null" };
	PenStylesNamesEx = { L"Dashed", L"Dotted", L"Alternating dashes and dots", L"Alternating dashes and double dots" };
	BrushStylesNames = { L"Solid", L"Vertical hatch", L"Horizontal hatch", L"Horizontal and vertical crosshatch",
		L"Downward hatch at 45 degrees", L"Upward hatch at 45 degrees", L"Crosshatch at 45 degrees" };
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
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

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
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

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//dc.Ellipse(200, 200, 300, 350);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_GraphicalWindow.Create(L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | SS_NOTIFY /*| WS_VSCROLL | WS_HSCROLL | WS_SIZEBOX*/,
		CRect(10, 10, 390, 390), this, ID_OUTPUT_WINDOW);

	CString str;
	str.LoadString(IDS_BUT_RECTANGLE);
	m_ButRect.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(400, 20, 500, 50), this, ID_BUT_RECTANGLE);

	m_ButTriangle.Create(L"Triangle", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(510, 20, 600, 50), this, ID_BUT_TRIANGLE);

	m_ButEllipse.Create(L"Ellipse", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(400, 70, 500, 100), this, ID_BUT_ELLIPSE);

	m_CBoxPenStyles.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST |WS_VSCROLL,
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

	m_CBoxBrushStyles.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(400, 170, 710, 350), this, ID_CBOX_BRUSH_STYLES);
	for (int i = 0; i < BrushStylesNames.size(); i++)
	{
		m_CBoxBrushStyles.InsertString(i, BrushStylesNames[i]);
	}
	m_CBoxBrushStyles.SetCurSel(0);

	m_EditPenWidth.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER, 
		CRect(400, 220, 500, 250), this, ID_ED_PEN_WIDTH);
	m_EditPenWidth.SetWindowTextW(L"1");

	m_ButChousePenColor.Create(L"Pen", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(400, 270, 440, 300), this, ID_BUT_PEN_COLOR);

	m_ButChouseBrushColor.Create(L"Brush", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(450, 270, 500, 300), this, ID_BUT_BRUSH_COLOR);

	m_ButNormalizeFigure.Create(L"Normalize", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(400, 320, 500, 350), this, ID_BUT_NORM_FIGURE);

	m_ButMove.Create(L"Move", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(510, 320, 560, 350), this, ID_BUT_MOVE);

	m_EditFigureAngle.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER,
		CRect(400, 370, 450, 400), this, ID_ED_FIGURE_ANGLE);
	m_EditFigureAngle.SetWindowTextW(L"0");

	m_ButLeftRotate.Create(L"Left", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(460, 370, 500, 400), this, ID_BUT_LEFT_ROTATE);

	m_ButRigthRotate.Create(L"Right", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(510, 370, 560, 400), this, ID_BUT_RIGHT_ROTATE);

	return 0;

}

void CChildView::OnButtonRect()
{
	m_GraphicalWindow.SetFigureType(FIGURE_RECTANGLE);
}

void CChildView::OnButtonEllipse()
{
	m_GraphicalWindow.SetFigureType(FIGURE_ELLIPSE);
}

void CChildView::OnCBoxPenStyles()
{
	m_GraphicalWindow.m_nFigurePenStyles = m_CBoxPenStyles.GetCurSel();
}

void CChildView::OnCBoxBrushStyles()
{
	m_GraphicalWindow.m_nFigureBrushStyles = m_CBoxBrushStyles.GetCurSel();
}

void CChildView::OnEditPenWidth()
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

void CChildView::OnButtonPenColor()
{
	COLORREF crColor = GetColor();
	if (crColor != -1)
	{
		m_GraphicalWindow.m_crFigurePenColor = crColor;
	}
}

void CChildView::OnButtonBrushColor()
{
	COLORREF crColor = GetColor();
	if (crColor != -1)
	{
		m_GraphicalWindow.m_crFigureBrushColor = crColor;
	}
}

COLORREF CChildView::GetColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		return dlg.GetColor();
	return -1;
}

void CChildView::OnButtonNormalizeFigure()
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->Normalize();
	m_GraphicalWindow.OnPaint();
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_GraphicalWindow.m_bLButtonUp = TRUE;
}

void CChildView::OnEditFigureAngle()
{
	
	
}

void CChildView::OnButtonLeftRotate()
{
	CString strEditText;
	m_EditFigureAngle.GetWindowText(strEditText);
	if (!m_GraphicalWindow.m_Figure.empty())
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->SetAngle(_wtoi(strEditText));
	m_GraphicalWindow.OnPaint();
}

void CChildView::OnButtonRightRotate()
{
	CString strEditText;
	m_EditFigureAngle.GetWindowText(strEditText);
	if (!m_GraphicalWindow.m_Figure.empty())
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_Figure.size() - 1]->SetAngle(-_wtoi(strEditText));
	m_GraphicalWindow.OnPaint();
}

void CChildView::OnButtonMove()
{
	m_GraphicalWindow.SetFigureType(FIGURE_MOVE);
}

void CChildView::OnButtonTriangle()
{
	m_GraphicalWindow.SetFigureType(FIGURE_TRIANGLE);
}