// LoaderDlg.h : header file
//

#if !defined(AFX_LOADERDLG_H__D218BFBB_282E_4542_B8DE_682D33126885__INCLUDED_)
#define AFX_LOADERDLG_H__D218BFBB_282E_4542_B8DE_682D33126885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLoaderDlg dialog

class CLoaderDlg : public CDialog
{
// Construction
public:
	CLoaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLoaderDlg)
	enum { IDD = IDD_LOADER_DIALOG };
	CComboBox	m_resolution;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int bits;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLoaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void On16bit();
	afx_msg void On32bit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADERDLG_H__D218BFBB_282E_4542_B8DE_682D33126885__INCLUDED_)
