// DlgResize.cpp : implementation file
//

#include "pch.h"
#include "GraphicalFigureEditor.h"
#include "DlgResize.h"
#include "afxdialogex.h"


// CDlgResize dialog

IMPLEMENT_DYNAMIC(CDlgResize, CDialog)

CDlgResize::CDlgResize(int nWidth, int nHeight, CWnd* pParent /*=nullptr*/): CDialog(IDD_DLG_RESIZE, pParent)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

CDlgResize::~CDlgResize()
{
}

void CDlgResize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_nWidth);
	DDX_Text(pDX, IDC_EDIT1, m_nHeight);
}


BEGIN_MESSAGE_MAP(CDlgResize, CDialog)
	ON_COMMAND(IDOK, &CDlgResize::OnBnClickedOk)
END_MESSAGE_MAP()




void CDlgResize::OnBnClickedOk()
{
	UpdateData(true);
	CDialog::OnOK();
}

BOOL CDlgResize::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(false);
	return 0;
}