// DlgProperties.cpp : implementation file
//

#include "pch.h"
#include "GraphicalFigureEditor.h"
#include "DlgProperties.h"
#include "EditorView.h"


// CDlgProperties dialog

IMPLEMENT_DYNAMIC(CDlgProperties, CDialog)



BOOL CDlgProperties::OnInitDialog()
{
	CDialog::OnInitDialog();
	LOGFONT lf{
		30,
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
	this->SetFont(&m_Font);
	MoveDLgItems();
	CEditorView* pView = static_cast<CEditorView*>(GetParent());

	m_ptrCBoxPenStyles = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_PEN_TYPE));
	pView->FillComboBox(pView->PenStylesNames, *m_ptrCBoxPenStyles);

	m_ptrCBoxBrushStyles = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE));
	pView->FillComboBox(pView->BrushStylesNames, *m_ptrCBoxBrushStyles);
	
	m_ptrCBoxLinkDirection = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_DIRECTION));
	pView->FillComboBox(pView->LinkDirection, *m_ptrCBoxLinkDirection);

	m_strFigure = pView->GetFigureType();
	
	return 0;
}

HBRUSH CDlgProperties::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	/*if (nCtlColor == CTLCOLOR_STATIC)
	{
		hBrush = CreateSolidBrush(RGB(145, 237, 253));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}*/

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}

	return hBrush;
}

CDlgProperties::CDlgProperties(CWnd* pParent /*=nullptr*/) : CDialog(IDD_DLG_PROPERTIES, pParent)
{
	m_ptrCBoxPenStyles = nullptr;
	m_ptrCBoxBrushStyles = nullptr;

	LinkElements = { IDC_STATIC_LINK , IDC_STATIC_DIRECTION , IDC_COMBO_DIRECTION , IDC_STATIC_FIGURE1 ,
	IDC_COMBO_FIRST_FIGURE , IDC_STATIC_FIGURE2 , IDC_COMBO_SECOND_FIGURE };

	FigureElements = { IDC_STATIC_ANGLE , IDC_STATIC_X , IDC_STATIC_Y , IDC_STATIC_X3 , IDC_STATIC_Y3 , IDC_STATIC_BRUSH ,
		IDC_STATIC_BR_TYPE, IDC_STATIC_BR_COLOR , IDC_STATIC_BR_R , IDC_STATIC_BR_G ,IDC_STATIC_BR_B, IDC_CENTER_X ,
		IDC_CENTER_Y, IDC_STATIC_CENTER ,IDC_VERTICES_X3 , IDC_VERTICES_Y3 , IDC_BRUSH_COLOR_R , IDC_BRUSH_COLOR_G ,
		IDC_BRUSH_COLOR_B , IDC_EDIT_ANGLE , IDC_COMBO_BRUSH_TYPE , IDC_BUT_SET_BRUSH };

}



CDlgProperties::~CDlgProperties()
{

}

void CDlgProperties::SetData()
{
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	//m_strFigure = pView->GetFigureType();
	if (pView->FigureListNotEmpty())
	{
		m_strFigure = pView->GetFigureType();
		if (m_strFigure == "Link")
		{
			pView->SetDlgLinkData(m_strName, m_nID, m_nWidth, m_nPenStyles, m_Vertices,
				m_nPenColor, m_nDirection, *static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE)), 
				*static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE)));
			static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetLBText(
				static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetCurSel(), m_strFirstFigure);
			static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetLBText(
				static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetCurSel(), m_strSecondFigure);
		}
		else
		{
			pView->SetDlgFigureData(m_strName, m_nID, m_nAngle, m_nWidth, m_nPenStyles, m_nBrushStyles, m_Center,
				m_Vertices, m_nPenColor, m_nBrushColor);
		}
	}
		
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_PEN_TYPE))->SetCurSel(m_nPenStyles);
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE))->SetCurSel(m_nBrushStyles);
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE))->SetCurSel(m_nDirection);

	int nStateLink, nStateFigure;
	

	if (m_strFigure == L"Link")
	{
		GetDlgItem(IDC_STATIC_VERTICLES)->MoveWindow(350, 28, 70, 20);
		GetDlgItem(IDC_STATIC_X1)->MoveWindow(360, 50, 20, 20);
		GetDlgItem(IDC_STATIC_Y1)->MoveWindow(440, 50, 20, 20);
		GetDlgItem(IDC_VERTICES_X1)->MoveWindow(385, 49, 43, 25);
		GetDlgItem(IDC_VERTICES_Y1)->MoveWindow(465, 49, 43, 25);

		GetDlgItem(IDC_STATIC_X2)->MoveWindow(530, 50, 20, 20);
		GetDlgItem(IDC_STATIC_Y2)->MoveWindow(610, 50, 20, 20);
		GetDlgItem(IDC_VERTICES_X2)->MoveWindow(555, 49, 43, 25);
		GetDlgItem(IDC_VERTICES_Y2)->MoveWindow(635, 49, 43, 25);

		nStateLink = SW_SHOW;
		nStateFigure = SW_HIDE;
	}
	else
	{
		GetDlgItem(IDC_STATIC_VERTICLES)->MoveWindow(350, 78, 70, 20);
		GetDlgItem(IDC_STATIC_X1)->MoveWindow(360, 100, 20, 20);
		GetDlgItem(IDC_STATIC_Y1)->MoveWindow(440, 100, 20, 20);
		GetDlgItem(IDC_VERTICES_X1)->MoveWindow(385, 99, 43, 25);
		GetDlgItem(IDC_VERTICES_Y1)->MoveWindow(465, 99, 43, 25);

		GetDlgItem(IDC_STATIC_X2)->MoveWindow(530, 100, 20, 20);
		GetDlgItem(IDC_STATIC_Y2)->MoveWindow(610, 100, 20, 20);
		GetDlgItem(IDC_VERTICES_X2)->MoveWindow(555, 99, 43, 25);
		GetDlgItem(IDC_VERTICES_Y2)->MoveWindow(635, 99, 43, 25);

		nStateLink = SW_HIDE;
		nStateFigure = SW_SHOW;
	}
	
	for (int i = 0; i < FigureElements.size(); i++)
		GetDlgItem(FigureElements[i])->ShowWindow(nStateFigure);
	
	
	for (int i = 0; i < LinkElements.size(); i++)
		GetDlgItem(LinkElements[i])->ShowWindow(nStateLink);




	if (m_strFigure == L"Triangle" || m_strFigure == L"Link")
		nStateLink = SW_HIDE;
	else
		nStateLink = SW_SHOW;
	static_cast<CEdit*>(GetDlgItem(IDC_VERTICES_X4))->ShowWindow(nStateLink);
	static_cast<CEdit*>(GetDlgItem(IDC_VERTICES_Y4))->ShowWindow(nStateLink);
	static_cast<CStatic*>(GetDlgItem(IDC_STATIC_X4))->ShowWindow(nStateLink);
	static_cast<CStatic*>(GetDlgItem(IDC_STATIC_Y4))->ShowWindow(nStateLink);
	//static_cast<CStatic*>(GetDlgItem(IDC_STATIC_FIGURES))->ShowWindow(nState);


	UpdateData(false);
}

//int CDlgProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CWnd::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//
//
//	return 0;
//}

void CDlgProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ID, m_nID);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_nAngle);
	DDX_Text(pDX, IDC_EDIT_PEN_WIDTH, m_nWidth);

	DDX_Text(pDX, IDC_STATIC_OBJECT, m_strFigure);

	DDX_Text(pDX, IDC_PEN_COLOR_R, m_nPenColor[0]);
	DDX_Text(pDX, IDC_PEN_COLOR_G, m_nPenColor[1]);
	DDX_Text(pDX, IDC_PEN_COLOR_B, m_nPenColor[2]);
	DDX_Text(pDX, IDC_BRUSH_COLOR_R, m_nBrushColor[0]);
	DDX_Text(pDX, IDC_BRUSH_COLOR_G, m_nBrushColor[1]);
	DDX_Text(pDX, IDC_BRUSH_COLOR_B, m_nBrushColor[2]);

	DDX_Text(pDX, IDC_CENTER_X, m_Center.x);
	DDX_Text(pDX, IDC_CENTER_Y, m_Center.y);
	
	DDX_Text(pDX, IDC_VERTICES_X1, m_Vertices[0].x);
	DDX_Text(pDX, IDC_VERTICES_Y1, m_Vertices[0].y);
	DDX_Text(pDX, IDC_VERTICES_X2, m_Vertices[1].x);
	DDX_Text(pDX, IDC_VERTICES_Y2, m_Vertices[1].y);
	DDX_Text(pDX, IDC_VERTICES_X3, m_Vertices[2].x);
	DDX_Text(pDX, IDC_VERTICES_Y3, m_Vertices[2].y);
	DDX_Text(pDX, IDC_VERTICES_X4, m_Vertices[3].x);
	DDX_Text(pDX, IDC_VERTICES_Y4, m_Vertices[3].y);

	//DDX_Text(pDX, IDC_COMBO_PEN_TYPE, m_nPenStyles);
	//DDX_Text(pDX, IDC_COMBO_BRUSH_TYPE, m_nBrushStyles);
	//DDV_MinMaxInt(pDX, m_nAngle, 0, 359);
}

void CDlgProperties::OnEditName()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());

	pView->UpdateName(m_strName);
}

void CDlgProperties::OnEditID()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateID(m_nID);
}

void CDlgProperties::OnEditAngle()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateAngle(m_nAngle);
}

void CDlgProperties::OnEditPen()
{
	UpdateData(true);
	for (int i = 0; i < 3; i++)
	{
		if (m_nPenColor[i] > 255)
			m_nPenColor[i] = 255;
	}
	UpdateData(false);
	COLORREF crPen = RGB(m_nPenColor[0], m_nPenColor[1], m_nPenColor[2]);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->SetColorValue(crPen, TRUE);
}

void CDlgProperties::OnEditBrush()
{
	UpdateData(true);
	for (int i = 0; i < 3; i++)
	{
		if (m_nBrushColor[i] > 255)
			m_nBrushColor[i] = 255;
	}
	UpdateData(false);
	COLORREF crBrush = RGB(m_nBrushColor[0], m_nBrushColor[1], m_nBrushColor[2]);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->SetColorValue(crBrush, FALSE);
}

void CDlgProperties::OnCBoxPenStyles()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	int nState = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_PEN_TYPE))->GetCurSel();
	pView->UpdatePenType(nState);
}

void CDlgProperties::OnCBoxBrushStyles()
{
	UpdateData(true);
	CEditorView *pView = static_cast<CEditorView*>(GetParent());
	int nState = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE))->GetCurSel();
	pView->UpdateBrushType(nState);
}

void CDlgProperties::OnEditCenter()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->MoveFigureWithDlg(m_Center);
}

void CDlgProperties::OnEditWidth()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateWidth(m_nWidth);
}

void CDlgProperties::OnEditCoordinateX1()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(0, TRUE, m_Vertices[0].x);
}

void CDlgProperties::OnEditCoordinateX2()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(1, TRUE, m_Vertices[1].x);
}

void CDlgProperties::OnEditCoordinateX3()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(2, TRUE, m_Vertices[2].x);
}

void CDlgProperties::OnEditCoordinateX4()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(3, TRUE, m_Vertices[3].x);
}

void CDlgProperties::OnEditCoordinateY1()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(0, FALSE, m_Vertices[0].y);
}

void CDlgProperties::OnEditCoordinateY2()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(1, FALSE, m_Vertices[1].y);
}

void CDlgProperties::OnEditCoordinateY3()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(2, FALSE, m_Vertices[2].y);
}

void CDlgProperties::OnEditCoordinateY4()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	pView->UpdateCoordinate(3, FALSE, m_Vertices[3].y);
}

void CDlgProperties::OnCBoxDirection()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	m_nDirection = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_DIRECTION))->GetCurSel();
	pView->UpdateDirection(m_nDirection);
}

void CDlgProperties::OnCBoxFirstFigure()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	int nFirstCurSel = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetCurSel();
	CString strFirstName;
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetLBText(nFirstCurSel, strFirstName);

	pView->UpdateLinkFigures(strFirstName, TRUE);
	pView->UpdateDlgLinkComboBox(*static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE)), FALSE,
		static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetCurSel());

	if (strFirstName == m_strSecondFigure)
	{
		m_strSecondFigure = m_strFirstFigure;
	}

	for (int i = 0; i < static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetCount(); i++)
	{
		CString str;
		static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetLBText(i, str);
		if (str == m_strSecondFigure)
		{
			static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->SetCurSel(i);
			pView->UpdateLinkFigures(m_strSecondFigure, FALSE);
			break;
		}
	}
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FIRST_FIGURE))->GetLBText(nFirstCurSel, m_strFirstFigure);
}

void CDlgProperties::OnCBoxSecondFigure()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	CString strName;
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->
		GetLBText(static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetCurSel(), strName);

	pView->UpdateLinkFigures(strName, FALSE);
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->
		GetLBText(static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SECOND_FIGURE))->GetCurSel(), m_strSecondFigure);
}


void CDlgProperties::OnButSetPenColor()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	COLORREF color = pView->GetColor();

	m_nPenColor[0] = GetRValue(color);
	m_nPenColor[1] = GetGValue(color);
	m_nPenColor[2] = GetBValue(color);
	UpdateData(false);
	OnEditPen();
}

void CDlgProperties::OnButSetBrushColor()
{
	UpdateData(true);
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	COLORREF color = pView->GetColor();

	m_nBrushColor[0] = GetRValue(color);
	m_nBrushColor[1] = GetGValue(color);
	m_nBrushColor[2] = GetBValue(color);
	UpdateData(false);
	OnEditBrush();
}




BEGIN_MESSAGE_MAP(CDlgProperties, CDialog)
	
	ON_WM_CTLCOLOR()
	//ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_EDIT_NAME, OnEditName)
	ON_EN_CHANGE(IDC_EDIT_ID, OnEditID)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, OnEditAngle)
	ON_EN_CHANGE(IDC_EDIT_PEN_WIDTH, OnEditWidth)
	ON_EN_CHANGE(IDC_PEN_COLOR_R, OnEditPen)
	ON_EN_CHANGE(IDC_PEN_COLOR_G, OnEditPen)
	ON_EN_CHANGE(IDC_PEN_COLOR_B, OnEditPen)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_R, OnEditBrush)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_G, OnEditBrush)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_B, OnEditBrush)
	ON_EN_CHANGE(IDC_CENTER_X, OnEditCenter)
	ON_EN_CHANGE(IDC_CENTER_Y, OnEditCenter)
	ON_EN_CHANGE(IDC_VERTICES_X1, OnEditCoordinateX1)
	ON_EN_CHANGE(IDC_VERTICES_X2, OnEditCoordinateX2)
	ON_EN_CHANGE(IDC_VERTICES_X3, OnEditCoordinateX3)
	ON_EN_CHANGE(IDC_VERTICES_X4, OnEditCoordinateX4)
	ON_EN_CHANGE(IDC_VERTICES_Y1, OnEditCoordinateY1)
	ON_EN_CHANGE(IDC_VERTICES_Y2, OnEditCoordinateY2)
	ON_EN_CHANGE(IDC_VERTICES_Y3, OnEditCoordinateY3)
	ON_EN_CHANGE(IDC_VERTICES_Y4, OnEditCoordinateY4)
	ON_CBN_SELCHANGE(IDC_COMBO_PEN_TYPE, OnCBoxPenStyles)
	ON_CBN_SELCHANGE(IDC_COMBO_BRUSH_TYPE, OnCBoxBrushStyles)
	ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, OnCBoxDirection)
	ON_CBN_SELCHANGE(IDC_COMBO_FIRST_FIGURE, OnCBoxFirstFigure)
	ON_CBN_SELCHANGE(IDC_COMBO_SECOND_FIGURE, OnCBoxSecondFigure)
	ON_COMMAND(IDC_BUT_SET_PEN, OnButSetPenColor)
	ON_COMMAND(IDC_BUT_SET_BRUSH, OnButSetBrushColor)
END_MESSAGE_MAP()

void CDlgProperties::MoveDLgItems()
{
	GetDlgItem(IDC_STATIC_OBJECT)->MoveWindow(9, 5, 315, 170);
	GetDlgItem(IDC_STATIC_PEN)->MoveWindow(9, 180, 315, 160);

	GetDlgItem(IDC_STATIC_NAME)->MoveWindow(19, 35, 55, 20);
	GetDlgItem(IDC_STATIC_ID)->MoveWindow(19, 68, 55, 20);
	GetDlgItem(IDC_STATIC_ANGLE)->MoveWindow(19, 101, 55, 20);
	GetDlgItem(IDC_STATIC_WIDTH)->MoveWindow(19, 205, 55, 20);
	GetDlgItem(IDC_STATIC_TYPE)->MoveWindow(19, 238, 55, 20);
	GetDlgItem(IDC_STATIC_COLOR)->MoveWindow(19, 271, 55, 20);

	GetDlgItem(IDC_EDIT_NAME)->MoveWindow(70, 34, 245, 25);
	GetDlgItem(IDC_EDIT_ID)->MoveWindow(70, 67, 245, 25);
	GetDlgItem(IDC_EDIT_ANGLE)->MoveWindow(70, 100, 245, 25);
	GetDlgItem(IDC_EDIT_PEN_WIDTH)->MoveWindow(70, 204, 245, 25);
	GetDlgItem(IDC_COMBO_PEN_TYPE)->MoveWindow(70, 236, 245, 25);

	GetDlgItem(IDC_STATIC_P_R)->MoveWindow(29, 294, 20, 20);
	GetDlgItem(IDC_PEN_COLOR_R)->MoveWindow(49, 293, 40, 25);
	GetDlgItem(IDC_STATIC_P_G)->MoveWindow(99, 294, 20, 20);
	GetDlgItem(IDC_PEN_COLOR_G)->MoveWindow(119, 293, 40, 25);
	GetDlgItem(IDC_STATIC_P_B)->MoveWindow(169, 294, 20, 20);
	GetDlgItem(IDC_PEN_COLOR_B)->MoveWindow(189, 293, 40, 25);
	GetDlgItem(IDC_BUT_SET_PEN)->MoveWindow(239, 292, 60, 27);


	GetDlgItem(IDC_STATIC_COORDINATES)->MoveWindow(340, 5, 349, 170);

	GetDlgItem(IDC_STATIC_CENTER)->MoveWindow(350, 28, 55, 20);
	GetDlgItem(IDC_STATIC_X)->MoveWindow(360, 50, 20, 20);
	GetDlgItem(IDC_STATIC_Y)->MoveWindow(440, 50, 20, 20);
	GetDlgItem(IDC_CENTER_X)->MoveWindow(385, 49, 43, 25);
	GetDlgItem(IDC_CENTER_Y)->MoveWindow(465, 49, 43, 25);

	GetDlgItem(IDC_STATIC_VERTICLES)->MoveWindow(350, 78, 70, 20);
	GetDlgItem(IDC_STATIC_X1)->MoveWindow(360, 100, 20, 20);
	GetDlgItem(IDC_STATIC_Y1)->MoveWindow(440, 100, 20, 20);
	GetDlgItem(IDC_VERTICES_X1)->MoveWindow(385, 99, 43, 25);
	GetDlgItem(IDC_VERTICES_Y1)->MoveWindow(465, 99, 43, 25);

	GetDlgItem(IDC_STATIC_X2)->MoveWindow(530, 100, 20, 20);
	GetDlgItem(IDC_STATIC_Y2)->MoveWindow(610, 100, 20, 20);
	GetDlgItem(IDC_VERTICES_X2)->MoveWindow(555, 99, 43, 25);
	GetDlgItem(IDC_VERTICES_Y2)->MoveWindow(635, 99, 43, 25);

	GetDlgItem(IDC_STATIC_X3)->MoveWindow(360, 132, 20, 20);
	GetDlgItem(IDC_STATIC_Y3)->MoveWindow(440, 132, 20, 20);
	GetDlgItem(IDC_VERTICES_X3)->MoveWindow(385, 131, 43, 25);
	GetDlgItem(IDC_VERTICES_Y3)->MoveWindow(465, 131, 43, 25);

	GetDlgItem(IDC_STATIC_X4)->MoveWindow(530, 132, 20, 20);
	GetDlgItem(IDC_STATIC_Y4)->MoveWindow(610, 132, 20, 20);
	GetDlgItem(IDC_VERTICES_X4)->MoveWindow(555, 131, 43, 25);
	GetDlgItem(IDC_VERTICES_Y4)->MoveWindow(635, 131, 43, 25);


	GetDlgItem(IDC_STATIC_BRUSH)->MoveWindow(340, 180, 349, 160);
	GetDlgItem(IDC_STATIC_BR_TYPE)->MoveWindow(350, 206, 55, 20);
	GetDlgItem(IDC_COMBO_BRUSH_TYPE)->MoveWindow(400, 206, 278, 20);

	GetDlgItem(IDC_STATIC_BR_COLOR)->MoveWindow(350, 235, 55, 20);
	GetDlgItem(IDC_STATIC_BR_R)->MoveWindow(360, 263, 20, 20);
	GetDlgItem(IDC_BRUSH_COLOR_R)->MoveWindow(380, 262, 40, 25);
	GetDlgItem(IDC_STATIC_BR_G)->MoveWindow(430, 263, 20, 20);
	GetDlgItem(IDC_BRUSH_COLOR_G)->MoveWindow(450, 263, 40, 25);
	GetDlgItem(IDC_STATIC_BR_B)->MoveWindow(500, 263, 20, 20);
	GetDlgItem(IDC_BRUSH_COLOR_B)->MoveWindow(520, 263, 40, 25);
	GetDlgItem(IDC_BUT_SET_BRUSH)->MoveWindow(570, 262, 60, 27);

	GetDlgItem(IDC_STATIC_LINK)->MoveWindow(340, 180, 349, 160);

	GetDlgItem(IDC_STATIC_DIRECTION)->MoveWindow(350, 205, 80, 20);
	GetDlgItem(IDC_COMBO_DIRECTION)->MoveWindow(430, 204, 250, 20);
	GetDlgItem(IDC_STATIC_FIGURE1)->MoveWindow(350, 238, 80, 20);
	GetDlgItem(IDC_COMBO_FIRST_FIGURE)->MoveWindow(430, 237, 250, 20);
	GetDlgItem(IDC_STATIC_FIGURE2)->MoveWindow(350, 271, 80, 20);
	GetDlgItem(IDC_COMBO_SECOND_FIGURE)->MoveWindow(430, 270, 250, 20);



	//GetDlgItem(IDC_BUT_SET_BRUSH)->ShowWindow(SW_HIDE);
	for (int i = 0; i < LinkElements.size(); i++)
		GetDlgItem(LinkElements[i])->ShowWindow(SW_HIDE);
}



