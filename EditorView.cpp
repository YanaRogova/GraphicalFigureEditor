
// ChildView.cpp : implementation of the CChildView class
//
#include <stdlib.h>
#include "pch.h"
#include "framework.h"
#include "GraphicalFigureEditor.h"
#include "EditorView.h"
#include "resource.h"
//#include "Figure.h"
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
#define ID_DLG_FIGURE			1320
#define ID_BUT_LINK				1321
#define ID_BUT_CREATE			1322
#define ID_CBOX_FIRST_FIGURE	1323
#define ID_CBOX_SECOND_FIGURE	1324
#define ID_CBOX_LINK_DIRECTION	1325
#define ID_VSCROLLBAR			1326
#define ID_HSCROLLBAR			1327
	

// CChildView

CEditorView::CEditorView()
{
	PenStylesNames = { L"Solid", L"Null", L"Dashes", L"Dotted", L"Alternating dashes and dots", 
		L"Alternating dashes and two dots" };
	BrushStylesNames = { L"Solid", L"Null", L"Vertical hatch", L"Horizontal hatch", L"Horizontal and vertical crosshatch",
		L"Downward hatch at 45 degrees", L"Upward hatch at 45 degrees", L"Crosshatch at 45 degrees" };
	LinkDirection = { L"None", L"To first", L"To second", L"To first and second" };
	m_nHeight = 0;
	m_nWidth = 0;
	bNewGraphicalWindow = FALSE;
	m_HScrollPosition = 0;
	m_VScrollPosition = 0;
}

CEditorView::~CEditorView()
{
}


BEGIN_MESSAGE_MAP(CEditorView, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_BUT_RECTANGLE, OnButtonRect)
	ON_COMMAND(ID_BUT_ELLIPSE, OnButtonEllipse)
	ON_COMMAND(ID_BUT_LINK, OnButtonLink)
	ON_COMMAND(ID_BUT_CREATE, OnButtonCreate)
	ON_CBN_SELCHANGE(ID_CBOX_PEN_STYLES, OnCBoxPenStyles)
	ON_EN_CHANGE(ID_ED_PEN_WIDTH, OnEditPenWidth)
	ON_COMMAND(ID_BUT_PEN_COLOR, OnButtonPenColor)
	ON_COMMAND(ID_BUT_BRUSH_COLOR, OnButtonBrushColor)
	ON_CBN_SELCHANGE(ID_CBOX_BRUSH_STYLES, OnCBoxBrushStyles)
	ON_CBN_SELCHANGE(ID_CBOX_FIRST_FIGURE, OnCBoxFirstFigure)
	ON_CBN_SELCHANGE(ID_CBOX_SECOND_FIGURE, OnCBoxSecondFigure)
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

afx_msg void  CEditorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos);
	int curpos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LEFT:         //Scrolls to the lower right. 
		curpos = minpos;
		break;
	case SB_RIGHT:         //Scrolls to the lower right.
		curpos = maxpos;
		break;
	case SB_ENDSCROLL:      //Ends scroll. 
		break;
	case SB_LINEDOWN:       //Scrolls one line down. 
		curpos++;
		break;
	case SB_LINEUP:         //Scrolls one line up.
		curpos--;
		break;
	case SB_PAGEDOWN:       //Scrolls one page down.
		curpos += 5;
		break;
	case SB_PAGEUP:         //Scrolls one page up. 
		curpos -= 5;
		break;
	case SB_THUMBPOSITION:  //The user has dragged the scroll box (thumb) and released the mouse button. The nPos parameter indicates the position of the scroll box at the end of the drag operation. 
		curpos = nPos;
		break;
	case SB_THUMBTRACK:     //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The nPos parameter indicates the position that the scroll box has been dragged to. 
		curpos = nPos;
		break;
	}
	pScrollBar->SetScrollPos(curpos);
	m_HScrollPosition = curpos;
	m_GraphicalWindow.OnPaint();
}


afx_msg void  CEditorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos);
	int curpos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LEFT:         //Scrolls to the lower right. 
		curpos = minpos;
		break;
	case SB_RIGHT:         //Scrolls to the lower right.
		curpos = maxpos;
		break;
	case SB_ENDSCROLL:      //Ends scroll. 
		break;
	case SB_LINEDOWN:       //Scrolls one line down. 
		curpos++;
		break;
	case SB_LINEUP:         //Scrolls one line up.
		curpos--;
		break;
	case SB_PAGEDOWN:       //Scrolls one page down.
		curpos += 5;
		break;
	case SB_PAGEUP:         //Scrolls one page up. 
		curpos -= 5;
		break;
	case SB_THUMBPOSITION:  //The user has dragged the scroll box (thumb) and released the mouse button. The nPos parameter indicates the position of the scroll box at the end of the drag operation. 
		curpos = nPos;
		break;
	case SB_THUMBTRACK:     //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The nPos parameter indicates the position that the scroll box has been dragged to. 
		curpos = nPos;
		break;
	}
	pScrollBar->SetScrollPos(curpos);
	m_VScrollPosition = curpos;
	m_GraphicalWindow.OnPaint();
}


int CEditorView::GetHScrollPosition()
{
	return m_HScrollPosition;
}

int CEditorView::GetVScrollPosition()
{
	return m_VScrollPosition;
}

// CChildView message handlers

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	HBRUSH hbrush;
	hbrush = CreateSolidBrush(RGB(227, 251, 255));
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
		20,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET | DEFAULT_CHARSET | RUSSIAN_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE,
		L"Times New Roman"
	};
	//CFont m_Font;
	//m_Font.DeleteObject();
	wcscpy_s(lf.lfFaceName, L"Verdana");
	//m_Font.CreateFontIndirectW(&lf);
	//dc.Ellipse(200, 200, 300, 350);
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

HBRUSH CEditorView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		hBrush = CreateSolidBrush(RGB(227, 251, 255));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}
	
	/*if (nCtlColor == CTLCOLOR_DLG)
	{
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SetBkMode(OPAQUE );
		return hBrush;
	}*/

	return hBrush;
}

int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	LOGFONT lf{
		20,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET | DEFAULT_CHARSET | RUSSIAN_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE,
		L"Georgia"
	};
	//wcscpy_s(lf.lfFaceName, L"Verdana");
	m_Font.CreateFontIndirect(&lf);
	m_ListFont.CreateFontW(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET | DEFAULT_CHARSET | RUSSIAN_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"Georgia");


	m_GraphicalWindow.Create(L"", WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_NOTIFY,
		CRect(), this, ID_OUTPUT_WINDOW);
	/*m_GraphicalWindow.Create(L"", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_NOTIFY,
		CRect(), this, ID_OUTPUT_WINDOW);*/
	/*m_GraphicalWindow.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_NOTIFY,
		CRect(), this, ID_OUTPUT_WINDOW);*/
	//m_GraphicalWindow.ModifyStyle();
	m_dlgFigureProperties.Create(IDD_DLG_PROPERTIES, this);
	m_dlgFigureProperties.ShowWindow(SW_HIDE);
	//m_dlgFigureProperties.ShowWindow(SW_SHOW);

	int x = 10, y = 10;
	
	m_ButRect.Create(L"Rectangle", WS_VISIBLE | WS_CHILD ,
		CRect(x, y, x + 100, y+25), this, ID_BUT_RECTANGLE);
	m_ButRect.SetFont(&m_Font);

	x += 110;
	m_ButTriangle.Create(L"Triangle", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_TRIANGLE);
	m_ButTriangle.SetFont(&m_Font);

	x += 110;
	m_ButEllipse.Create(L"Ellipse", WS_VISIBLE | WS_CHILD ,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_ELLIPSE);
	m_ButEllipse.SetFont(&m_Font);

	x += 110;
	m_ButLink.Create(L"Link", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_LINK);
	m_ButLink.ShowWindow(SW_HIDE);
	m_ButLink.SetFont(&m_Font);

	x += 110;
	m_ButCreate.Create(L"Create", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_CREATE);
	m_ButCreate.ShowWindow(SW_HIDE);
	m_ButCreate.SetFont(&m_Font);
	y += 30;
	x = 10;
	m_StaticName.Create(L"Name:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y + 25), this, ID_STATIC);
	m_StaticName.SetFont(&m_Font);
	x += 105;
	m_EditName.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT,
		CRect(x, y, x+290, y + 25), this, ID_ED_NAME);
	m_EditName.SetFont(&m_Font);
	x += 300;
	

	//y += 30;
	m_StaticID.Create(L"ID:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x+25, y + 25), this, ID_STATIC);
	m_StaticID.SetFont(&m_Font);
	x += 26;
	m_EditID.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER,
		CRect(x, y, x+100, y+ 25), this, ID_ED_ID);
	m_EditID.SetFont(&m_Font);
	//m_EditID.SetWindowTextW(L"1");
	

	//y += 30;
	x += 110;

	m_StaticPenWidth.Create(L"Pen width:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 75, y + 25), this, ID_STATIC);
	m_StaticPenWidth.SetFont(&m_Font);
	x += 80;
	m_EditPenWidth.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER,
		CRect(x, y, x + 50, y + 25), this, ID_ED_PEN_WIDTH);
	m_EditPenWidth.SetFont(&m_Font);
	m_EditPenWidth.SetWindowTextW(L"5");

	y += 30;
	x = 10;

	m_StaticNameWarning.Create(L"This name has already was used.", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 270, y + 25), this, ID_STATIC);
	m_StaticNameWarning.SetFont(&m_Font);
	m_StaticNameWarning.ShowWindow(SW_HIDE);
	x += 405;
	m_StaticIDWarning.Create(L"This ID has already was used.", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 250, y + 25), this, ID_STATIC);
	m_StaticIDWarning.SetFont(&m_Font);
	m_StaticIDWarning.ShowWindow(SW_HIDE);
	y += 30;
	x = 10;

	m_StaticPenType.Create(L"Pen type:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y+25), this, ID_STATIC);
	m_StaticPenType.SetFont(&m_Font);
	x += 105;



	m_CBoxPenStyles.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST | WS_VSCROLL,
		CRect(x, y, x+290, y+250), this, ID_CBOX_PEN_STYLES);
	FillComboBox(PenStylesNames, m_CBoxPenStyles);
	m_CBoxPenStyles.SetFont(&m_Font);

	//m_CBoxPenStyles.
	/*for (int i = 0; i < PenStylesNames.size(); i++)
	{
		m_CBoxPenStyles.InsertString(i, PenStylesNames[i]);
	}
	m_CBoxPenStyles.SetCurSel(0);*/
	x += 300;
	m_ButChousePenColor.Create(L"Pen color", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_PEN_COLOR);
	m_ButChousePenColor.SetFont(&m_Font);

	y += 30;
	x = 10;
	m_StaticBrush.Create(L"Brush type:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y+25), this, ID_STATIC);
	m_StaticBrush.SetFont(&m_Font);
	m_StaticDirection.Create(L"Direction:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y + 25), this, ID_STATIC);
	m_StaticDirection.SetFont(&m_Font);
	m_StaticDirection.ShowWindow(SW_HIDE);

	x += 105;
	m_CBoxBrushStyles.Create(WS_VISIBLE | WS_CHILD  | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(x, y, x+290, y+250), this, ID_CBOX_BRUSH_STYLES);
	m_CBoxBrushStyles.SetFont(&m_Font);
	FillComboBox(BrushStylesNames, m_CBoxBrushStyles);

	m_CBoxLinkDirection.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(x, y, x + 290, y + 250), this, ID_CBOX_LINK_DIRECTION);
	m_CBoxLinkDirection.SetFont(&m_Font);
	FillComboBox(LinkDirection, m_CBoxLinkDirection);
	m_CBoxLinkDirection.ShowWindow(SW_HIDE);
	/*for (int i = 0; i < BrushStylesNames.size(); i++)
	{
		m_CBoxBrushStyles.InsertString(i, BrushStylesNames[i]);
	}
	m_CBoxBrushStyles.SetCurSel(0);*/
	x += 300;
	m_ButChouseBrushColor.Create(L"Brush color", WS_VISIBLE | WS_CHILD,
		CRect(x, y, x + 100, y + 25), this, ID_BUT_BRUSH_COLOR);
	m_ButChouseBrushColor.SetFont(&m_Font);

	x = 10;
	y += 30;
	m_StaticFirstFigure.Create(L"First figure:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 100, y + 25), this, ID_STATIC);
	m_StaticFirstFigure.SetFont(&m_Font);
	m_StaticFirstFigure.ShowWindow(SW_HIDE);
	x += 105;
	m_CBoxFirstFigure.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(x, y, x + 290, y + 250), this, ID_CBOX_FIRST_FIGURE);
	m_CBoxFirstFigure.SetFont(&m_Font);
	m_CBoxFirstFigure.ShowWindow(SW_HIDE);
	x += 300;
	m_StaticSecondFigure.Create(L"Second figure:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT,
		CRect(x, y, x + 115, y + 25), this, ID_STATIC);
	m_StaticSecondFigure.SetFont(&m_Font);
	m_StaticSecondFigure.ShowWindow(SW_HIDE);
	x += 120;
	m_CBoxSecondFigure.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(x, y, x + 290, y + 250), this, ID_CBOX_SECOND_FIGURE);
	m_CBoxSecondFigure.SetFont(&m_Font);
	m_CBoxSecondFigure.ShowWindow(SW_HIDE);
	


	m_ButNormalizeFigure.Create(L"Normalize", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_NORM_FIGURE);
	m_ButNormalizeFigure.SetFont(&m_Font);

	m_ButMove.Create(L"Move", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_MOVE);
	m_ButMove.SetFont(&m_Font);

	m_ButDelete.Create(L"Delete", WS_VISIBLE | WS_CHILD,
		CRect(), this, ID_BUT_DELETE);
	m_ButDelete.SetFont(&m_Font);

	m_StaticAngle.Create(L"Angle:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_RIGHT,
		CRect(), this, ID_STATIC);
	m_StaticAngle.SetFont(&m_Font);

	m_EditFigureAngle.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_BORDER | SS_CENTERIMAGE | SS_RIGHT,
		CRect(), this, ID_ED_FIGURE_ANGLE);
	m_EditFigureAngle.SetFont(&m_Font);
	m_EditFigureAngle.SetWindowTextW(L"0");

	m_ButLeftRotate.Create(L"To left", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_LEFT_ROTATE);
	m_ButLeftRotate.SetFont(&m_Font);

	m_ButRightRotate.Create(L"To right", WS_VISIBLE | WS_CHILD ,
		CRect(), this, ID_BUT_RIGHT_ROTATE);
	m_ButRightRotate.SetFont(&m_Font);

	m_VScrollbar.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_NOTIFY | SBS_VERT,
		CRect(), this, ID_VSCROLLBAR);

	m_HScrollbar.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | SS_NOTIFY | SBS_HORZ,
		CRect(), this, ID_HSCROLLBAR);
	
	//SendMessageToDescendants(WM_SETFONT,
	//	(WPARAM)m_Font.m_hObject,  //handle to font
	//	MAKELONG((WORD)FALSE, 0),
	//	FALSE);

	m_List.Create( LVS_REPORT | WS_VISIBLE | WS_BORDER, CRect(), this, ID_FIGURE_LIST);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List.SetFont(&m_ListFont);
	
	std::vector<CString> m_strColomns = {L"¹", L"Name", L"ID", L"Type", L"Center", L"Coordinates", L"Angle"};
	std::vector<int> m_strColomnsSize = { 30, 115, 30, 80, 80, 310, 55};
	for (int i = 0; i < 7; i++)
	{
		m_List.InsertColumn(i, m_strColomns[i], LVCFMT_LEFT, m_strColomnsSize[i]);
	}
	
	FigureOrLink(TRUE);

	return 0;
}

void CEditorView::OnButtonRect()
{
	m_GraphicalWindow.SetFigureType(FIGURE_RECTANGLE);

	FigureOrLink(TRUE);
}
void CEditorView::FigureOrLink(bool bFigureLink)
{
	int nFigure, nLink;
	if (bFigureLink)
	{
		nFigure = SW_SHOW;
		nLink = SW_HIDE;
	}
	else
	{
		nFigure = SW_HIDE;
		nLink = SW_SHOW;
	}

	m_ButCreate.ShowWindow(nLink);
	m_StaticFirstFigure.ShowWindow(nLink);
	m_CBoxFirstFigure.ShowWindow(nLink);
	m_StaticSecondFigure.ShowWindow(nLink);
	m_CBoxSecondFigure.ShowWindow(nLink);
	m_CBoxLinkDirection.ShowWindow(nLink);
	m_StaticDirection.ShowWindow(nLink);

	m_StaticBrush.ShowWindow(nFigure);
	m_ButChouseBrushColor.ShowWindow(nFigure);
	m_CBoxBrushStyles.ShowWindow(nFigure);
	m_StaticBrush.ShowWindow(nFigure);
	m_CBoxBrushStyles.ShowWindow(nFigure);
}

void CEditorView::OnButtonLink()
{
	m_GraphicalWindow.SetFigureType(FIGURE_LINK);

	FillLinkComboBox(m_GraphicalWindow.m_Figure, m_CBoxFirstFigure, TRUE);
	FillLinkComboBox(m_GraphicalWindow.m_Figure, m_CBoxSecondFigure, FALSE);

	FigureOrLink(FALSE);
}

void CEditorView::OnButtonCreate()
{
	m_GraphicalWindow.SetFigureNameAndID();
	m_GraphicalWindow.m_setNames.insert(m_GraphicalWindow.m_FigureName);
	m_GraphicalWindow.m_setID.insert(m_GraphicalWindow.m_FigureID);
	int nFirstCurSel = m_CBoxFirstFigure.GetCurSel();
	//if (m_CBoxSecondFigure.GetCurSel() < m_CBoxFirstFigure.GetCurSel())
	int nSecondCurSel = m_CBoxSecondFigure.GetCurSel();
	/*else
		nSecondCurSel = m_CBoxSecondFigure.GetCurSel() + 1;*/
	
	CString stdFirstName, stdSecondName;
	m_CBoxFirstFigure.GetLBText(nFirstCurSel, stdFirstName);
	m_CBoxSecondFigure.GetLBText(nSecondCurSel, stdSecondName);

	for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
	{
		if (m_GraphicalWindow.m_Figure[i]->GetName() == stdFirstName)
		{
			nFirstCurSel = i;
			break;
		}
	}

	for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
	{
		if (m_GraphicalWindow.m_Figure[i]->GetName() == stdSecondName)
		{
			nSecondCurSel = i;
			break;
		}
	}

	m_GraphicalWindow.m_Figure.push_back(new CLink(m_GraphicalWindow.PenStyles[m_GraphicalWindow.m_nFigurePenStyles],
		m_GraphicalWindow.m_nFigurePenWidth, m_GraphicalWindow.m_crFigurePenColor, stdFirstName, stdSecondName, 
		m_CBoxLinkDirection.GetCurSel(), m_GraphicalWindow.m_Figure[nFirstCurSel]->GetCenter(),
		m_GraphicalWindow.m_Figure[nSecondCurSel]->GetCenter(),	m_GraphicalWindow.m_FigureName, 
		m_GraphicalWindow.m_FigureID));

	m_GraphicalWindow.m_nSelectedFigure = m_GraphicalWindow.m_Figure.size() - 1;
	m_GraphicalWindow.OnPaint();
	UpdateListView(TRUE);
	m_dlgFigureProperties.SetData();
}


void CEditorView::OnButtonEllipse()
{
	m_GraphicalWindow.SetFigureType(FIGURE_ELLIPSE);
	FigureOrLink(TRUE);
}

void CEditorView::SaveFile(CString strFileName)
{
	m_GraphicalWindow.SavePicture(strFileName);
}

void CEditorView::OpenFile(CString strFileName)
{
	m_GraphicalWindow.OpenPicture(strFileName);
}

void CEditorView::NewFile(bool bChangePictureSize)
{
	m_GraphicalWindow.m_setID.clear();
	m_GraphicalWindow.m_setNames.clear();
	m_GraphicalWindow.m_Figure.clear();
	UpdateListView(TRUE);
	CRect EditorViewRect;
	GetClientRect(EditorViewRect);
	//ScreenToClient(EditorViewRect);
	if (bChangePictureSize)
	{
		m_nWidth = EditorViewRect.Width() - 730;
		m_nHeight = EditorViewRect.Height() - 207;
	}
	int nCenterX = (EditorViewRect.Width() - 720 + 10) / 2;
	int nCenterY = (EditorViewRect.Height() - 10 + 197) / 2;

	bNewGraphicalWindow = FALSE;
	CPoint SecondCoordinate;
	if (m_nWidth % 2 == 1)
		SecondCoordinate.x = nCenterX + (m_nWidth / 2 + 1);
	else
		SecondCoordinate.x = nCenterX + m_nWidth / 2;

	if (m_nHeight % 2 == 1)
		SecondCoordinate.y = nCenterY + (m_nHeight / 2 + 1);
	else
		SecondCoordinate.y = nCenterY + m_nHeight / 2;

	m_GraphicalWindow.MoveWindow(CRect(nCenterX - m_nWidth / 2, nCenterY - m_nHeight / 2, SecondCoordinate.x, SecondCoordinate.y));
	Invalidate();
}

void CEditorView::OnCBoxPenStyles()
{
	m_GraphicalWindow.m_nFigurePenStyles = m_CBoxPenStyles.GetCurSel();
}

void CEditorView::OnCBoxBrushStyles()
{
	m_GraphicalWindow.m_nFigureBrushStyles = m_CBoxBrushStyles.GetCurSel();
}

void CEditorView::OnCBoxFirstFigure()
{
	m_GraphicalWindow.m_nLinkFirstFigure = m_CBoxFirstFigure.GetCurSel();
	FillLinkComboBox(m_GraphicalWindow.m_Figure, m_CBoxSecondFigure, FALSE, m_CBoxFirstFigure.GetCurSel());
}

void CEditorView::OnCBoxSecondFigure()
{
	m_GraphicalWindow.m_nLinkSecondFigure = m_CBoxSecondFigure.GetCurSel();
}

void CEditorView::OnEditPenWidth()
{
	int nOldEditState = m_GraphicalWindow.m_nFigurePenWidth;
	CString strEditText;
	m_EditPenWidth.GetWindowText(strEditText);
	m_GraphicalWindow.m_nFigurePenWidth = _wtoi(strEditText);

	//OnCBoxPenStyles();	//to update ComboBox state
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
		UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
		m_GraphicalWindow.SetPictureNotSaved(TRUE);
		m_GraphicalWindow.OnPaint();
		UpdateListView(TRUE, FALSE);
		m_dlgFigureProperties.SetData();
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
		m_GraphicalWindow.SetPictureNotSaved(TRUE);
		UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
		m_GraphicalWindow.OnPaint();
		UpdateListView(TRUE, FALSE);
		m_dlgFigureProperties.SetData();
	}
}

void CEditorView::OnButtonRightRotate()
{
	CString strEditText;
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_EditFigureAngle.GetWindowText(strEditText);
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetAngle(-_wtoi(strEditText));
		m_GraphicalWindow.SetPictureNotSaved(TRUE);
		UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
		m_GraphicalWindow.OnPaint();
		UpdateListView(TRUE, FALSE); 
		m_dlgFigureProperties.SetData();
	}
}

void CEditorView::OnButtonMove()
{
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		m_GraphicalWindow.SetFigureType(FIGURE_MOVE);
		UpdateListView(TRUE, FALSE);
	}	
}




void CEditorView::OnButtonDelete()
{
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		
		m_GraphicalWindow.DeleteFigure();
		
		UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
		UpdateListView(TRUE);
		m_dlgFigureProperties.SetData();
		m_GraphicalWindow.OnPaint();
	}
}

void CEditorView::OnButtonTriangle()
{
	m_GraphicalWindow.SetFigureType(FIGURE_TRIANGLE);
	FigureOrLink(TRUE);
}

void CEditorView::UpdateListView(bool bSetFokus, bool bUpdateAll)
{

	CString str;
	if (bUpdateAll)
	{
		m_List.DeleteAllItems();

		for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
		{
			str.Format(L"%d", i+1);
			int Index = m_List.InsertItem(0, str);
			m_List.SetItemText(Index, 1, m_GraphicalWindow.m_Figure[i]->GetName());
			m_List.SetItemText(Index, 2, m_GraphicalWindow.m_Figure[i]->GetID());
			m_List.SetItemText(Index, 3, m_GraphicalWindow.m_Figure[i]->GetFigure());
			m_List.SetItemText(Index, 4, m_GraphicalWindow.m_Figure[i]->GetStrCenter());
			m_List.SetItemText(Index, 5, m_GraphicalWindow.m_Figure[i]->GetStrCoordinates());
			m_List.SetItemText(Index, 6, m_GraphicalWindow.m_Figure[i]->GetAngle());
		}
	}
	else
	{
		int i = m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1;
		str.Format(L"%d", m_GraphicalWindow.m_nSelectedFigure + 1);
		m_List.SetItemText(i, 1, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName());
		m_List.SetItemText(i, 2, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID());
		m_List.SetItemText(i, 3, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetFigure());
		m_List.SetItemText(i, 4, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetStrCenter());
		m_List.SetItemText(i, 5, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetStrCoordinates());
		m_List.SetItemText(i, 6, m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetAngle());
	}
	
	m_List.SetItemState(m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1, LVIS_SELECTED , LVIS_SELECTED);
	//m_List.SetHotItem(m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1);
	m_List.SetSelectionMark(m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1);
	if (!m_GraphicalWindow.m_Figure.empty())
		m_dlgFigureProperties.ShowWindow(SW_SHOW);
	else
		m_dlgFigureProperties.ShowWindow(SW_HIDE);

	if(bSetFokus)
		m_List.SetFocus();

	if (m_GraphicalWindow.m_Figure.size() >= 2)
		m_ButLink.ShowWindow(SW_SHOW);
	else
		m_ButLink.ShowWindow(SW_HIDE);

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
	m_List.MoveWindow(CRect(cx - 710, 400, cx - 10, cy - 10));
	m_dlgFigureProperties.MoveWindow(CRect(cx - 710 , 10, cx - 10, 360));
	/*if(!m_GraphicalWindow.m_Figure.empty())
		m_dlgFigureProperties.ShowWindow(SW_SHOW);*/

	m_ButDelete.MoveWindow(CRect(cx - 710, 370, cx - 610, 395));
	m_ButNormalizeFigure.MoveWindow(CRect(cx - 600, 370, cx - 500, 395));
	m_ButMove.MoveWindow(CRect(cx - 490, 370, cx - 390, 395));
	m_StaticAngle.MoveWindow(CRect(cx - 380, 370, cx - 280, 395));
	m_EditFigureAngle.MoveWindow(CRect(cx - 276, 370, cx - 230, 395));
	m_ButLeftRotate.MoveWindow(CRect(cx - 220, 370, cx - 120, 395));
	m_ButRightRotate.MoveWindow(CRect(cx - 110, 370, cx - 10, 395));

	int nCenterX = (cx - 720 + 10) / 2;
	int nCenterY = (cy - 10 + 197) / 2;
	int VScrollWidth = 0;
	int HScrollHeight = 0;
	int TempWidth = m_nWidth;
	int TempHeight = m_nHeight;
	if (m_nWidth > cx - 720)
	{
		HScrollHeight = 20;
	}
	else
		m_HScrollbar.ShowWindow(SW_HIDE);

	if (m_nHeight + HScrollHeight > cy - 207)
	{
		m_VScrollbar.ShowWindow(SW_SHOW);
		VScrollWidth = 20;
	}
	else
		m_VScrollbar.ShowWindow(SW_HIDE);

	if (m_nWidth + VScrollWidth > cx - 720)
	{
		m_HScrollbar.ShowWindow(SW_SHOW);
		HScrollHeight = 20;
	}
	else
		m_HScrollbar.ShowWindow(SW_HIDE);

	TempWidth -= VScrollWidth;
	TempHeight -= HScrollHeight;
	nCenterX -= VScrollWidth ;
	nCenterY -= HScrollHeight ;

	CPoint Coordinate[2];
	


	if (VScrollWidth != 0)
	{
		//nCenterX -= 10;
		if (HScrollHeight != 0)
		{
			Coordinate[1].y = cy - 30;
		}
		else
		{
			Coordinate[1].y = cy - 10;
		}
		Coordinate[0].y = 197;
		
	}
	else
	{
		Coordinate[0].y = nCenterY - m_nHeight / 2;
		if (m_nHeight % 2 == 1)
			Coordinate[1].y = nCenterY + (m_nHeight / 2 + 1);
		else
			Coordinate[1].y = nCenterY + m_nHeight / 2;
	}

	if (HScrollHeight != 0)
	{
		//nCenterY -= 20;
		if (VScrollWidth != 0)
		{
			Coordinate[1].x = cx - 740;
		}
		else
		{
			Coordinate[1].x = cx - 720;
		}
		Coordinate[0].x = 10;


	}
	else
	{
		Coordinate[0].x = nCenterX - m_nWidth / 2;
		if (m_nWidth % 2 == 1)
			Coordinate[1].x = nCenterX + (m_nWidth / 2 + 1);
		else
			Coordinate[1].x = nCenterX + m_nWidth / 2;
	}
	
	m_HScrollbar.MoveWindow(CRect(Coordinate[0].x, Coordinate[1].y, Coordinate[1].x, Coordinate[1].y + 20));
	m_VScrollbar.MoveWindow(CRect(Coordinate[1].x, Coordinate[0].y, Coordinate[1].x + 20, Coordinate[1].y));
	m_GraphicalWindow.MoveWindow(CRect(Coordinate[0].x, Coordinate[0].y, Coordinate[1].x, Coordinate[1].y));

	m_HScrollbar.SetScrollRange(0, m_nWidth-(Coordinate[1].x - Coordinate[0].x));
	m_VScrollbar.SetScrollRange(0, m_nHeight-(Coordinate[1].y - Coordinate[0].y));
	m_HScrollPosition = 0;
	m_VScrollPosition = 0;
}

bool CEditorView::FigureListNotEmpty()
{
	return (!m_GraphicalWindow.m_Figure.empty());
}

void CEditorView::OnEditName()
{
	CString strEditText;
	m_EditName.GetWindowText(strEditText);
	m_GraphicalWindow.m_FigureName = SetUniqueName(strEditText);
}

void CEditorView::OnEditID()
{
	CString strEditText;
	m_EditID.GetWindowText(strEditText);
	int id = _wtoi(strEditText);
	m_GraphicalWindow.m_FigureID = SetUniqueID(id);
}

void CEditorView::OnNotify(NMHDR* pNotifyStruct, LRESULT* result)
{
	if (m_List.GetSelectionMark() != -1)
	{
		m_GraphicalWindow.m_nSelectedFigure = m_GraphicalWindow.m_Figure.size() - m_List.GetSelectionMark() - 1;
		m_List.SetHotItem(m_GraphicalWindow.m_Figure.size() - m_GraphicalWindow.m_nSelectedFigure - 1);
		m_dlgFigureProperties.SetData();
	}
	
}

int CEditorView::SetUniqueID(int id)
{
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
	return id;
}

CString CEditorView::SetUniqueName(CString strEditText)
{
	CString buffer = L"";
	int i = 1;
	if (m_GraphicalWindow.m_setNames.find(strEditText) != m_GraphicalWindow.m_setNames.end())
	{
		do
		{
			buffer.Format(L"%s(%d)", strEditText, i);
			i++;
		} while (m_GraphicalWindow.m_setNames.find(buffer) != m_GraphicalWindow.m_setNames.end());
		m_StaticNameWarning.ShowWindow(SW_SHOW);
		return buffer;
	}
	else
	{
		m_StaticNameWarning.ShowWindow(SW_HIDE);
		return strEditText;
	}
}

void CEditorView::UpdateAngle(int nAngle)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgAngle(nAngle);
	//UpdateListView();
	UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
	UpdateListView(FALSE, FALSE);
	m_GraphicalWindow.OnPaint();
	//m_dlgFigureProperties.SetFocus();
}

void CEditorView::SetColorValue(COLORREF crColor, bool bPenBrush)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgColorValue(crColor, bPenBrush);
	m_GraphicalWindow.OnPaint();
}

void CEditorView::FillComboBox(std::vector<CString> vItems, CComboBox &cbox)
{
	for (int i = 0; i < vItems.size(); i++)
	{
		cbox.InsertString(i, vItems[i]);
	}
	cbox.SetCurSel(0);
}

void CEditorView::FillLinkComboBox(std::vector<CFigure*>& vItems, CComboBox& cbox, bool bFirstSecond, int nFirstSelected)
{
	cbox.ResetContent();
	
	int counter = 0;
	CString strName;
	for (int i = vItems.size() - 1; i >= 0; i--)
	{
		if (vItems[i]->GetFigureType() == FIGURE_RECTANGLE ||
			vItems[i]->GetFigureType() == FIGURE_TRIANGLE ||
			vItems[i]->GetFigureType() == FIGURE_ELLIPSE)
		{
			cbox.InsertString(counter, vItems[i]->GetName());
		}
	}
	if (bFirstSecond == FALSE)
		cbox.DeleteString(nFirstSelected);
	cbox.SetCurSel(0);
}

void CEditorView::MoveFigureWithDlg(CPoint point)
{
	m_GraphicalWindow.MoveFigure(point);
	UpdateListView(FALSE, FALSE);
	UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
	m_GraphicalWindow.OnPaint();
}

CString CEditorView::GetFigureType()
{
	if (!m_GraphicalWindow.m_Figure.empty())
		return m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetFigure();
	return L"Figure";
}

void CEditorView::UpdateWidth(int nWidth)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgWidth(nWidth);
	m_GraphicalWindow.OnPaint();
}

void CEditorView::UpdatePenType(int nType)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgPenStyle(m_GraphicalWindow.PenStyles[nType]);
	m_GraphicalWindow.OnPaint();
}

void CEditorView::UpdateBrushType(int nType)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgBrushStyle(m_GraphicalWindow.BrushStyles[nType]);
	m_GraphicalWindow.OnPaint();
}

void CEditorView::UpdateName(CString strName)
{
	CString strOldName = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName();
	if (strOldName != strName)
	{
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgName(SetUniqueName(strName));
		m_GraphicalWindow.m_setNames.insert(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName());
		m_GraphicalWindow.m_setNames.erase(strOldName);
	}

	for(int links = m_GraphicalWindow.m_nSelectedFigure; links < m_GraphicalWindow.m_Figure.size(); links++)
		if (m_GraphicalWindow.m_Figure[links]->GetFigureType() == FIGURE_LINK)
		{
			if (m_GraphicalWindow.m_Figure[links]->GetFirstFigure() == strOldName)
				m_GraphicalWindow.m_Figure[links]->SetFigure(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->
					GetName(), TRUE);
			if (m_GraphicalWindow.m_Figure[links]->GetSecondFigure() == strOldName)
				m_GraphicalWindow.m_Figure[links]->SetFigure(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->
					GetName(), FALSE);
		}

	UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
	UpdateListView(FALSE, FALSE);
	//m_GraphicalWindow.OnPaint();
}

void CEditorView::UpdateID(int nID)
{
	int strOldID = _wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID());
	if (strOldID != nID)
	{
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgID(SetUniqueID(nID));
		m_GraphicalWindow.m_setID.insert(_wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID()));
		m_GraphicalWindow.m_setID.erase(strOldID);
	}
	UpdateListView(FALSE, FALSE);
	//m_GraphicalWindow.OnPaint();
}

void CEditorView::UpdateCoordinate(int nVertice, bool bXOrY, int nCoordinate)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDlgCoordinate(nVertice, bXOrY, nCoordinate);
	UpdateLinks(m_GraphicalWindow.m_nSelectedFigure);
	UpdateListView(FALSE, FALSE);
	m_GraphicalWindow.OnPaint();
}

void CEditorView::SetDlgFigureData(CString& strName, int& nID, int& nAngle, int& nWidth, int& nPenStyle, int& nBrushStyle, CPoint& Center,
	CPoint* Vertices, int* nPenColor, int* nBrushColor)
{
	strName = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName();
	nID = _wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID());
	nAngle = _wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetAngle());
	nWidth = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetWidth();
	int i = 0;
	while (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetPenStyle() != m_GraphicalWindow.PenStyles[i])
	{
		i++;
	}
	nPenStyle = i;

	i = 0;
	while (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetBrushStyle() != m_GraphicalWindow.BrushStyles[i])
	{
		i++;
	}
	nBrushStyle = i;

	Center = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetCenter();

	//Vertices = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetCoordinates();
	COLORREF buf= m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetPenColor();
	nPenColor[0] = GetRValue(buf);
	nPenColor[1] = GetGValue(buf);
	nPenColor[2] = GetBValue(buf);

	buf = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetBrushColor();
	nBrushColor[0] = GetRValue(buf);
	nBrushColor[1] = GetGValue(buf);
	nBrushColor[2] = GetBValue(buf);

	for(int i = 0; i < 4; i++)
		Vertices[i] = (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetCoordinates())[i];


}

void CEditorView::SetDlgLinkData(CString& strName, int& nID, int& nWidth, int& nPenStyle,
	CPoint* Vertices, int* nPenColor, int& nDirection, CComboBox& firstFigure, CComboBox& secondFigure)
{
	strName = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetName();
	nID = _wtoi(m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetID());
	nWidth = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetWidth();

	int i = 0;
	while (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetPenStyle() != m_GraphicalWindow.PenStyles[i])
	{
		i++;
	}
	nPenStyle = i;	

	COLORREF buf = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetPenColor();
	nPenColor[0] = GetRValue(buf);
	nPenColor[1] = GetGValue(buf);
	nPenColor[2] = GetBValue(buf);

	for (int i = 0; i < 2; i++)
		Vertices[i] = (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetCoordinates())[i];

	nDirection = m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetDirection();

	while (m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetPenStyle() != m_GraphicalWindow.PenStyles[i])
	{
		i++;
	}


	FillLinkComboBox(m_GraphicalWindow.m_Figure, firstFigure, TRUE);
	i = FindCurSelCBox(firstFigure, TRUE);

	FillLinkComboBox(m_GraphicalWindow.m_Figure, secondFigure, FALSE, i);
	FindCurSelCBox(secondFigure, FALSE);

}

void CEditorView::UpdateLinks(int nItem)
{
	for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
	{
		if (m_GraphicalWindow.m_Figure[i]->GetFigureType() == FIGURE_LINK)
		{
			if (m_GraphicalWindow.m_Figure[i]->GetFirstFigure() == m_GraphicalWindow.m_Figure[nItem]->GetName())
				m_GraphicalWindow.m_Figure[i]->SetVertice(0, m_GraphicalWindow.m_Figure[nItem]->GetCenter());

			if (m_GraphicalWindow.m_Figure[i]->GetSecondFigure() == m_GraphicalWindow.m_Figure[nItem]->GetName())
				m_GraphicalWindow.m_Figure[i]->SetVertice(1, m_GraphicalWindow.m_Figure[nItem]->GetCenter());
		}
	}
}

void CEditorView::UpdateDlgLinkComboBox(CComboBox& cbox, bool bFirstSecond, int nFirstSelected)
{
	if (!m_GraphicalWindow.m_Figure.empty())
	{
		if (bFirstSecond)
			FillLinkComboBox(m_GraphicalWindow.m_Figure, cbox, TRUE);
		else
			FillLinkComboBox(m_GraphicalWindow.m_Figure, cbox, FALSE, nFirstSelected);
	}
}

int CEditorView::FindCurSelCBox(CComboBox& cbox, bool bFirstSecond)
{
	for (int i = 0; i < cbox.GetCount(); i++)
	{
		CString str;
		cbox.GetLBText(i, str);
		if (bFirstSecond)
		{
			if (str == m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetFirstFigure())
			{
				cbox.SetCurSel(i);
				return i;
			}
		}
		else
		{
			if (str == m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->GetSecondFigure())
			{
				cbox.SetCurSel(i);
				return i;
			}
		}
		
	}

	return -1;
}

void CEditorView::UpdateDirection(int nDirection)
{
	m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetDirection(nDirection);
	m_GraphicalWindow.OnPaint();
}
bool CEditorView::PictureNotSaved()
{
	return m_GraphicalWindow.PictureNotSaved();
}

void CEditorView::UpdateLinkFigures(CString strName, bool bFirstSecond)
{
	int nCurSel = 0;
	for (int i = 0; i < m_GraphicalWindow.m_Figure.size(); i++)
	{
		if (m_GraphicalWindow.m_Figure[i]->GetName() == strName)
		{
			nCurSel = i;
			break;
		}
	}
	if (bFirstSecond)
	{
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetFigure(strName, TRUE);
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->
			SetVertice(0, m_GraphicalWindow.m_Figure[nCurSel]->GetCenter());
	}
	else
	{
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->SetFigure(strName, FALSE);
		m_GraphicalWindow.m_Figure[m_GraphicalWindow.m_nSelectedFigure]->
			SetVertice(1, m_GraphicalWindow.m_Figure[nCurSel]->GetCenter());
	}
	m_GraphicalWindow.OnPaint();
}

int CEditorView::GetWidth()
{
	return m_nWidth;
}
int CEditorView::GetHeight()
{
	return m_nHeight;
}

void CEditorView::SetWidthAndHeight(int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}