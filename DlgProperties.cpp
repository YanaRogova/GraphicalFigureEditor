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

	CEditorView* pView = static_cast<CEditorView*>(GetParent());

	m_ptrCBoxPenStyles = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_PEN_TYPE));
	pView->FillComboBox(pView->PenStylesNames, *m_ptrCBoxPenStyles);

	m_ptrCBoxBrushStyles = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE));
	pView->FillComboBox(pView->BrushStylesNames, *m_ptrCBoxBrushStyles);

	m_strFigure = pView->GetFigureType();
	

	//if (m_strFigure == L"Triangle")
	//{
	//	
	//}
	return 0;
}

CDlgProperties::CDlgProperties(CWnd* pParent /*=nullptr*/) : CDialog(IDD_DLG_PROPERTIES, pParent)
{
	m_ptrCBoxPenStyles = nullptr;
	m_ptrCBoxBrushStyles = nullptr;
}

CDlgProperties::~CDlgProperties()
{
}

void CDlgProperties::SetData()
{
	CEditorView* pView = static_cast<CEditorView*>(GetParent());
	//m_strFigure = pView->GetFigureType();
	if (pView->FigureListNotEmpty())
		pView->SetDlgData(m_strFigure, m_strName, m_nID, m_nAngle, m_nWidth, m_nPenStyles, m_nBrushStyles, m_Center,
			m_Vertices, m_nPenColor, m_nBrushColor);
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_PEN_TYPE))->SetCurSel(m_nPenStyles);
	static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BRUSH_TYPE))->SetCurSel(m_nBrushStyles);

	int nState;
	if (m_strFigure == L"Triangle")
		nState = SW_HIDE;
	else
		nState = SW_SHOW;
	static_cast<CEdit*>(GetDlgItem(IDC_VERTICES_X4))->ShowWindow(nState);
	static_cast<CEdit*>(GetDlgItem(IDC_VERTICES_Y4))->ShowWindow(nState);
	static_cast<CStatic*>(GetDlgItem(IDC_STATIC_X4))->ShowWindow(nState);
	static_cast<CStatic*>(GetDlgItem(IDC_STATIC_Y4))->ShowWindow(nState);



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

	DDX_Text(pDX, IDC_STATIC_FIGURE, m_strFigure);

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

BEGIN_MESSAGE_MAP(CDlgProperties, CDialog)
	ON_WM_CREATE()
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, OnEditName)
	ON_EN_KILLFOCUS(IDC_EDIT_ID, OnEditID)
	ON_EN_KILLFOCUS(IDC_EDIT_ANGLE, OnEditAngle)
	ON_EN_CHANGE(IDC_EDIT_PEN_WIDTH, OnEditWidth)
	ON_EN_CHANGE(IDC_PEN_COLOR_R, OnEditPen)
	ON_EN_CHANGE(IDC_PEN_COLOR_G, OnEditPen)
	ON_EN_CHANGE(IDC_PEN_COLOR_B, OnEditPen)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_R, OnEditBrush)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_G, OnEditBrush)
	ON_EN_CHANGE(IDC_BRUSH_COLOR_B, OnEditBrush)
	ON_EN_KILLFOCUS(IDC_CENTER_X, OnEditCenter)
	ON_EN_KILLFOCUS(IDC_CENTER_Y, OnEditCenter)
	ON_EN_KILLFOCUS(IDC_VERTICES_X1, OnEditCoordinateX1)
	ON_EN_KILLFOCUS(IDC_VERTICES_X2, OnEditCoordinateX2)
	ON_EN_KILLFOCUS(IDC_VERTICES_X3, OnEditCoordinateX3)
	ON_EN_KILLFOCUS(IDC_VERTICES_X4, OnEditCoordinateX4)
	ON_EN_KILLFOCUS(IDC_VERTICES_Y1, OnEditCoordinateY1)
	ON_EN_KILLFOCUS(IDC_VERTICES_Y2, OnEditCoordinateY2)
	ON_EN_KILLFOCUS(IDC_VERTICES_Y3, OnEditCoordinateY3)
	ON_EN_KILLFOCUS(IDC_VERTICES_Y4, OnEditCoordinateY4)
	ON_CBN_SELCHANGE(IDC_COMBO_PEN_TYPE, OnCBoxPenStyles)
	ON_CBN_SELCHANGE(IDC_COMBO_BRUSH_TYPE, OnCBoxBrushStyles)
END_MESSAGE_MAP()



