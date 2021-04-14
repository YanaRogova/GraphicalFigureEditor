#pragma once
#include <vector>

// CDlgProperties dialog

class CDlgProperties : public CDialog
{
	DECLARE_DYNAMIC(CDlgProperties)

public:
	CDlgProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgProperties();
	void SetData();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditName();
	afx_msg void OnEditID();
	afx_msg void OnEditAngle();
	afx_msg void OnEditPen();
	afx_msg void OnEditBrush();
	afx_msg void OnEditCenter();
	afx_msg void OnCBoxPenStyles();
	afx_msg void OnCBoxBrushStyles();
	afx_msg void OnEditWidth();
	afx_msg void OnEditCoordinateX1();
	afx_msg void OnEditCoordinateX2();
	afx_msg void OnEditCoordinateX3();
	afx_msg void OnEditCoordinateX4();
	afx_msg void OnEditCoordinateY1();
	afx_msg void OnEditCoordinateY2();
	afx_msg void OnEditCoordinateY3();
	afx_msg void OnEditCoordinateY4();
	afx_msg void OnCBoxDirection();
	afx_msg void OnCBoxFirstFigure();
	afx_msg void OnCBoxSecondFigure();
	afx_msg void OnButSetPenColor();
	afx_msg void OnButSetBrushColor();



	DECLARE_MESSAGE_MAP()


protected:
	CFont m_Font;
	CString m_strFigure;
	CString m_strName;
	CString m_strFirstFigure;
	CString m_strSecondFigure;
	int m_nID;
	int m_nAngle;
	int m_nPenColor[3];
	int m_nBrushColor[3];
	int m_nWidth;
	int m_nDirection;
	
	int m_nPenStyles;
	int m_nBrushStyles;
	CPoint m_Center;
	CPoint m_Vertices[4];
	void MoveDLgItems();

	CComboBox *m_ptrCBoxPenStyles;
	CComboBox *m_ptrCBoxBrushStyles;
	CComboBox* m_ptrCBoxLinkDirection;

	std::vector<int> LinkElements;
	std::vector<int> FigureElements;

	HBRUSH hbrush;
	HBRUSH CDlgProperties::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//CComboBox* m_ptrCBoxLinkFirstFigure;
	//CComboBox* m_ptrCBoxLinkSecondFigure;

};
