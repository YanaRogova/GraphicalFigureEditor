
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
#define ID_FIGURE_LIST			1315
#define ID_BUT_DELETE			1316
#define ID_STATIC				1317
#define ID_ED_NAME				1318
#define ID_ED_ID				1319

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
	ON_WM_SIZE()
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
	ON_COMMAND(ID_BUT_DELETE, OnButtonDelete)
	ON_COMMAND(ID_BUT_TRIANGLE, OnButtonTriangle)
	ON_NOTIFY(NM_CLICK, ID_FIGURE_LIST, OnNotify)
	ON_EN_CHANGE(ID_ED_NAME, OnEditName)
	ON_EN_CHANGE(ID_ED_ID, OnEditID)
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
	LOGFONT lf{
		15,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_STROKE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE
	};
	CFont m_font;
	//m_font.DeleteObject();
	wcscpy_s(lf.lfFaceName, L"Verdana");
	m_font.CreateFontIndirectW(&lf);
	//dc.Ellipse(200, 200, 300, 350);
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	LOGFONT lf{
		15,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_STROKE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE
	};
	CFont m_font;
	//m_font.DeleteObject();
	wcscpy_s(lf.lfFaceName, L"Verdana");
	//m_font.CreateFont(10, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Verdana");
	m_font.CreateFontIndirectW(&lf);
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_GraphicalWindow.Create(L"", WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_NOTIFY /*| WS_VSCROLL | WS_HSCROLL | WS_SIZEBOX*/,
		CRect(), this, ID_OUTPUT_WINDOW);

	int x = 10, y = 10;
	CString str;
	str.LoadString(IDS_BUT_RECTANGLE);
	m_ButRect.Create(str, WS_VISIBLE | WS_CHILD | BS_FLAT,
		CRect(x, y, x + 100, y+25), this, ID_BUT_RECTANGLE);
	m_ButRect.SetFont(&m_font);

	x += 110;
	m_ButTriangle.Create(L"Triangle", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_TRIANGLE);

	x += 110;
	m_ButEllipse.Create(L"Ellipse", WS_VISIBLE | WS_CHILD ,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_ELLIPSE);

	y += 30;
	x = 10;
	m_StaticName.Create(L"Name:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y + 25), this, ID_STATIC);
	x += 110;
	m_EditName.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
		CRect(x, y, x+290, y + 25), this, ID_ED_NAME);
	x += 300;
	m_StaticNameWarning.Create(L"This name has already was used.", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 270, y + 25), this, ID_STATIC);
	m_StaticNameWarning.ShowWindow(SW_HIDE);

	y += 30;
	x = 10;
	m_StaticID.Create(L"ID:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x+100, y + 25), this, ID_STATIC);
	x += 110;
	m_EditID.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | ES_NUMBER,
		CRect(x, y, x+290, y+ 25), this, ID_ED_ID);
	x += 300;
	m_StaticIDWarning.Create(L"This ID has already was used.", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 250, y + 25), this, ID_STATIC);
	m_StaticIDWarning.ShowWindow(SW_HIDE);

	y += 30;
	x = 10;

	m_StaticPenType.Create(L"Pen type:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y+25), this, ID_STATIC);
	x += 110;
	m_CBoxPenStyles.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST | WS_VSCROLL,
		CRect(x, y, x+290, y+250), this, ID_CBOX_PEN_STYLES);
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
	x += 300;
	m_ButChousePenColor.Create(L"Pen color", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_PEN_COLOR);

	y += 30;
	x = 10;
	m_StaticBrush.Create(L"Brush type:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y+25), this, ID_STATIC);
	x += 110;
	m_CBoxBrushStyles.Create(WS_VISIBLE | WS_CHILD  | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(x, y, x+290, y+250), this, ID_CBOX_BRUSH_STYLES);
	for (int i = 0; i < BrushStylesNames.size(); i++)
	{
		m_CBoxBrushStyles.InsertString(i, BrushStylesNames[i]);
	}
	m_CBoxBrushStyles.SetCurSel(0);
	x += 300;
	m_ButChouseBrushColor.Create(L"Brush color", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_BRUSH_COLOR);

	y += 30;
	x = 10;

	m_StaticPenWidth.Create(L"Pen width:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y + 25), this, ID_STATIC);
	x += 110;
	m_EditPenWidth.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER | SS_RIGHT,
		CRect(x, y, x + 290, y + 25), this, ID_ED_PEN_WIDTH);
	m_EditPenWidth.SetWindowTextW(L"1");


	m_ButNormalizeFigure.Create(L"Normalize", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_NORM_FIGURE);

	m_ButMove.Create(L"Move", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_MOVE);

	m_ButDelete.Create(L"Delete", WS_VISIBLE | WS_CHILD,
		CRect(), this, ID_BUT_DELETE);

	m_StaticAngle.Create(L"Angle:", WS_VISIBLE | WS_CHILD | WS_TABSTOP | SS_CENTERIMAGE | SS_RIGHT,
		CRect(), this, ID_STATIC);

	m_EditFigureAngle.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER | SS_CENTERIMAGE | SS_RIGHT,
		CRect(), this, ID_ED_FIGURE_ANGLE);
	m_EditFigureAngle.SetWindowTextW(L"0");

	m_ButLeftRotate.Create(L"To left", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_LEFT_ROTATE);

	m_ButRightRotate.Create(L"To right", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_RIGHT_ROTATE);

	m_List.Create( LVS_REPORT | WS_VISIBLE | WS_BORDER, CRect(), this, ID_FIGURE_LIST);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	std::vector<CString> m_strColomns = {L"¹", L"Name", L"ID", L"Type", L"Center", L"Coordinates", L"Angle"};
	std::vector<int> m_strColomnsSize = { 30, 100, 30, 80, 80, 310, 70};
	for (int i = 0; i < 7; i++)
	{
		m_List.InsertColumn(i, m_strColomns[i], LVCFMT_LEFT, m_strColomnsSize[i]);
	}
	
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
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->Normalize();
		m_GraphicalWindow.OnPaint();
		UpdateListView();
	}
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
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_EditFigureAngle.GetWindowText(strEditText);
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetAngle(_wtoi(strEditText));
		m_GraphicalWindow.OnPaint();
		UpdateListView();
	}
}

void CEditorView::OnButtonRightRotate()
{
	CString strEditText;
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_EditFigureAngle.GetWindowText(strEditText);
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetAngle(-_wtoi(strEditText));
		m_GraphicalWindow.OnPaint();
		UpdateListView();
	}
}

void CEditorView::OnButtonMove()
{
	m_GraphicalWindow.SetFigureType(FIGURE_MOVE);
	UpdateListView();
}

void CEditorView::OnButtonDelete()
{
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_GraphicalWindow.m_setID.erase(_wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID()));
		m_GraphicalWindow.m_setNames.erase(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName());
		m_GraphicalWindow.m_Figure.erase(m_GraphicalWindow.m_Figure.begin() + m_GraphicalWindow.m_nSelectedFigure);
		m_GraphicalWindow.m_nSelectedFigure = 0;
		UpdateListView();
		m_GraphicalWindow.OnPaint();
	}
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
	
	m_List.SetItemState(m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1,LVIS_SELECTED , LVIS_SELECTED);
	m_List.SetSelectionMark(0);
	m_List.SetFocus();
	//m_List.EnsureVisible(0, FALSE);
	/*else
		m_List.SetSelectionMark(m_GraphicalWindow.m_nSelectedFigure);*/
	//m_List.SetHotItem(m_GraphicalWindow.m_nSelectedFigure);
}

void CEditorView::MoveFigureElement(int nCurrentPosition, int nNewPosition)
{
	CFigure* figure = m_GraphicalWindow.m_Figure[nCurrentPosition];
	m_GraphicalWindow.m_Figure.erase(m_GraphicalWindow.m_Figure.begin() + nCurrentPosition);
	m_GraphicalWindow.m_Figure.insert(m_GraphicalWindow.m_Figure.begin() + nNewPosition, figure);
}

void CEditorView::OnSize(UINT nType, int cx, int cy)
{
	CRect EditorViewRect;
	GetWindowRect(EditorViewRect);
	ScreenToClient(EditorViewRect);

	m_List.MoveWindow(CRect(cx - 710, 400, cx - 10, cy - 10));

	m_ButDelete.MoveWindow(CRect(cx - 710, 370, cx - 610, 395));
	m_ButNormalizeFigure.MoveWindow(CRect(cx - 600, 370, cx - 500, 395));
	m_ButMove.MoveWindow(CRect(cx - 490, 370, cx - 390, 395));
	m_StaticAngle.MoveWindow(CRect(cx - 380, 370, cx - 280, 395));
	m_EditFigureAngle.MoveWindow(CRect(cx - 270, 370, cx - 230, 395));
	m_ButLeftRotate.MoveWindow(CRect(cx - 220, 370, cx - 120, 395));
	m_ButRightRotate.MoveWindow(CRect(cx - 110, 370, cx - 10, 395));

	m_GraphicalWindow.MoveWindow(CRect(10, 400, cx - 720, cy - 10));


}

void CEditorView::OnEditName()
{
	CString strName, buffer = L"";
	m_EditName.GetWindowText(strName);
	int i = 1;
	if (m_GraphicalWindow.m_setNames.find(strName) != m_GraphicalWindow.m_setNames.end())
	{
		/*while(m_GraphicalWindow.m_setNames.find(buffer.Format(L"%s %d", strName, i)) == m_GraphicalWindow.m_setNames.end())
		{
			i++;
		} */
		do
		{
			buffer.Format(L"%s(%d)", strName, i);
			i++;
		} while (m_GraphicalWindow.m_setNames.find(buffer) != m_GraphicalWindow.m_setNames.end());

		m_StaticNameWarning.ShowWindow(SW_SHOW);
		m_GraphicalWindow.m_FigureName = buffer;
	}
	else
	{
		m_StaticNameWarning.ShowWindow(SW_HIDE);
		m_GraphicalWindow.m_FigureName = strName;
	}
	
}

void CEditorView::OnEditID()
{
	CString strEditText;
	m_EditID.GetWindowText(strEditText);
	int id = _wtoi(strEditText);
	if (m_GraphicalWindow.m_setID.find(id) != m_GraphicalWindow.m_setID.end())
	{
		m_StaticIDWarning.ShowWindow(SW_SHOW);
		do 
		{
			id++;
		} while (m_GraphicalWindow.m_setID.find(id) != m_GraphicalWindow.m_setID.end());
	}
	else
	{
		m_StaticIDWarning.ShowWindow(SW_HIDE);
	}
	m_GraphicalWindow.m_FigureID = id;
}

void CEditorView::OnNotify(NMHDR* pNotifyStruct, LRESULT* result)
{
	m_GraphicalWindow.m_nSelectedFigure = m_GraphicalWindow.m_Figure.size() - m_List.GetSelectionMark() - 1;
}











































































































CMyListView::CMyListView() {

}

CMyListView::~CMyListView() {

}

void CMyListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// this code only works for a report-mode list view
	//ASSERT(GetStyle() & LVS_REPORT);

	CListCtrl& listCtrl = GetListCtrl();

	// Insert a column. This override is the most convenient.
	listCtrl.InsertColumn(0, _T("Player Name"), LVCFMT_LEFT);

	// The other InsertColumn() override requires an initialized
	// LVCOLUMN structure.
	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT;
	col.pszText = _T("Jersey Number");
	col.fmt = LVCFMT_LEFT;
	listCtrl.InsertColumn(1, &col);

	// Set reasonable widths for our columns
	listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
}