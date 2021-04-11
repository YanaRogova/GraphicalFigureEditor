#pragma once


// CDlgProperties dialog

class CDlgProperties : public CDialog
{
	DECLARE_DYNAMIC(CDlgProperties)

public:
	CDlgProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgProperties();
	void SetData();

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



	DECLARE_MESSAGE_MAP()


protected:

	CString m_strFigure;
	CString m_strName;
	int m_nID;
	int m_nAngle;
	int m_nPenColor[3];
	int m_nBrushColor[3];
	int m_nWidth;

	int m_nPenStyles;
	int m_nBrushStyles;
	CPoint m_Center;
	CPoint m_Vertices[4];

	CComboBox *m_ptrCBoxPenStyles;
	CComboBox *m_ptrCBoxBrushStyles;
};
