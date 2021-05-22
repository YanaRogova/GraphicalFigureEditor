#pragma once
#include "afxcview.h"
#include "GraphicalWindow.h"
#include "DlgProperties.h"

class CEditorView : public CWnd
{
protected:
	DECLARE_MESSAGE_MAP()

public:
	CEditorView();
	virtual ~CEditorView();

	std::vector<CString> PenStylesNames;
	std::vector<CString> BrushStylesNames;
	std::vector<CString> LinkDirection;

	CDlgProperties m_dlgFigureProperties;
	
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNotify(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT, UINT nPos, CScrollBar*);
	afx_msg void OnVScroll(UINT, UINT nPos, CScrollBar*);
	afx_msg void OnButtonRect();
	afx_msg void OnButtonEllipse();
	afx_msg void OnButtonTriangle();
	afx_msg void OnButtonLink();
	afx_msg void OnButtonCreate();
	afx_msg void OnButtonPenColor();
	afx_msg void OnButtonBrushColor();
	afx_msg void OnButtonNormalizeFigure();
	afx_msg void OnButtonLeftRotate();
	afx_msg void OnButtonRightRotate();
	afx_msg void OnButtonMove();
	afx_msg void OnButtonDelete();
	afx_msg void OnCBoxPenStyles();
	afx_msg void OnCBoxBrushStyles();
	afx_msg void OnCBoxFirstFigure();
	afx_msg void OnCBoxSecondFigure();
	afx_msg void OnEditPenWidth();
	afx_msg void OnEditName();
	afx_msg void OnEditID();

public:
	void SaveFile(CString strFileName);
	void OpenFile(CString strFileName);
	void NewFile(bool bChangePictureSize = TRUE);

	void FigureOrLink(bool bFigureLink);
	bool FigureListNotEmpty();

	COLORREF GetColor();

	void UpdateListView(bool bSetFokus, bool bUpdateAll = TRUE);
	void UpdateWidth(int nWidth);
	void UpdatePenType(int nType);
	void UpdateBrushType(int nType);
	void UpdateName(CString strName);
	void UpdateID(int nID);
	void UpdateCoordinate(int nVertice, bool bXOrY, int nCoordinate);
	void UpdateDlgLinkComboBox(CComboBox& cbox, bool bFirstSecond, int nFirstSelected = 0);
	void UpdateDirection(int nDirection);
	void UpdateLinkFigures(CString strName, bool bFirstSecond);
	void UpdateAngle(int nAngle);
	void UpdateLinks(int nItem);

	void FillComboBox(std::vector<CString> vItems, CComboBox& cbox);
	void FillLinkComboBox(std::vector<CFigure*>& vItems, CComboBox& cbox, bool bFirstSecond, int nFirstSelected = 0);
	void MoveFigureWithDlg(CPoint point);
	int FindCurSelCBox(CComboBox& cbox, bool bFirstSecond);
	bool PictureNotSaved();

	void SetDlgFigureData(CString& strName, int& nID, int& nAngle, int& nWidth, int& nPenStyle, int& nBrushStyle, CPoint& Center,
		CPoint* Vertices, int* nPenColor, int* nBrushColor);
	void SetDlgLinkData(CString& strName, int& nID, int& nWidth, int& nPenStyle, CPoint* Vertices,
		int* nPenColor, int& nDirection, CComboBox& firstFigure, CComboBox& secondFigure);
	int SetUniqueID(int id);
	CString SetUniqueName(CString strEditText);
	void SetColorValue(COLORREF crColor, bool bPenBrush);
	void SetWidthAndHeight(int nWidth, int nHeight);

	CString GetFigureType();
	int GetWidth();
	int GetHeight();
	int GetHScrollPosition();
	int GetVScrollPosition();

protected:
	CGraphicalWindow m_GraphicalWindow;
	CListCtrl m_List;
	CButton m_ButRect;
	CButton m_ButEllipse;
	CButton m_ButLink;
	CButton m_ButCreate;
	CButton m_ButChousePenColor;
	CButton m_ButChouseBrushColor;
	CButton m_ButNormalizeFigure;
	CButton m_ButLeftRotate;
	CButton m_ButRightRotate;
	CButton m_ButMove;
	CButton m_ButDelete;
	CButton m_ButTriangle;
	CComboBox m_CBoxPenStyles;
	CComboBox m_CBoxBrushStyles;
	CComboBox m_CBoxFirstFigure;
	CComboBox m_CBoxSecondFigure;
	CComboBox m_CBoxLinkDirection;
	CEdit m_EditPenWidth;
	CEdit m_EditFigureAngle;
	CEdit m_EditName;
	CEdit m_EditID;
	CStatic m_StaticAngle;
	CStatic m_StaticPenType;
	CStatic m_StaticPenWidth;
	CStatic m_StaticBrush;
	CStatic m_StaticName;
	CStatic m_StaticNameWarning;
	CStatic m_StaticID;
	CStatic m_StaticIDWarning;
	CStatic m_StaticFirstFigure;
	CStatic m_StaticSecondFigure;
	CStatic m_StaticDirection;
	CFont m_Font;
	CFont m_ListFont;
	CBrush m_brBackground;
	CScrollBar m_VScrollbar;
	CScrollBar m_HScrollbar;

	int m_nHeight;
	int m_nWidth;
	int m_HScrollPosition;
	int m_VScrollPosition;
	bool bNewGraphicalWindow;
	bool bFirstFileCreated;
};
