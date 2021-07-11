#pragma once
#include <vector>

#define ARRAY_RGB 3
#define MAX_NUMBER_VERTICES 4
#define NUMBER_LINK_CONTROLS 9
#define NUMBER_DLG_CONTROLS 61


class CDlgProperties : public CDialog
{
	DECLARE_DYNAMIC(CDlgProperties)
protected:
	DECLARE_MESSAGE_MAP()

public:
	CDlgProperties(CWnd* pParent = nullptr); 
	virtual ~CDlgProperties();
	void SetData();
	
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	virtual BOOL OnInitDialog();
	void MoveDLgItems();

	afx_msg void OnEditName();
	afx_msg void OnEditID();
	afx_msg void OnEditAngle();
	afx_msg void OnEditPen();
	afx_msg void OnEditBrush();
	afx_msg void OnEditCenter();
	afx_msg void OnEditWidth();
	afx_msg void OnEditCoordinateX1();
	afx_msg void OnEditCoordinateX2();
	afx_msg void OnEditCoordinateX3();
	afx_msg void OnEditCoordinateX4();
	afx_msg void OnEditCoordinateY1();
	afx_msg void OnEditCoordinateY2();
	afx_msg void OnEditCoordinateY3();
	afx_msg void OnEditCoordinateY4();

	afx_msg void OnCBoxPenStyles();
	afx_msg void OnCBoxBrushStyles();
	afx_msg void OnCBoxDirection();
	afx_msg void OnCBoxFirstFigure();
	afx_msg void OnCBoxSecondFigure();

	afx_msg void OnButSetPenColor();
	afx_msg void OnButSetBrushColor();
	afx_msg void OnOK() override;
	afx_msg void OnCancel() override;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	CFont m_Font;

	CString m_strFigure;
	CString m_strName;
	CString m_strFirstFigure;
	CString m_strSecondFigure;

	int m_nID;
	int m_nAngle;
	int m_nPenColor[ARRAY_RGB];
	int m_nBrushColor[ARRAY_RGB];
	int m_nWidth;
	int m_nDirection;

	int m_nPenStyles;
	int m_nBrushStyles;

	CPoint m_Center;
	CPoint m_Vertices[MAX_NUMBER_VERTICES];

	CComboBox *m_ptrCBoxPenStyles;
	CComboBox *m_ptrCBoxBrushStyles;
	CComboBox* m_ptrCBoxLinkDirection;

	std::vector<int> LinkElements;
	std::vector<int> FigureElements;

	HBRUSH hbrush;

};
