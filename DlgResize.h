#pragma once

class CDlgResize : public CDialog
{
	DECLARE_DYNAMIC(CDlgResize)
protected:
	DECLARE_MESSAGE_MAP()

public:
	CDlgResize(int nWidth, int nHeight, CWnd* pParent = nullptr); 
	virtual ~CDlgResize();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

public:
	int m_nWidth;
	int m_nHeight;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RESIZE };
#endif
};
