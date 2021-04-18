#pragma once


// CDlgResize dialog

class CDlgResize : public CDialog
{
	DECLARE_DYNAMIC(CDlgResize)

public:
	CDlgResize(int nWidth, int nHeight, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgResize();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RESIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_nWidth;
	int m_nHeight;
};
