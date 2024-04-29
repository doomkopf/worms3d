// LoaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Loader.h"
#include "LoaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoaderDlg dialog

CLoaderDlg::CLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoaderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoaderDlg)
	DDX_Control(pDX, IDC_COMBO1, m_resolution);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoaderDlg, CDialog)
	//{{AFX_MSG_MAP(CLoaderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnStart)
	ON_BN_CLICKED(IDC_RADIO1, On16bit)
	ON_BN_CLICKED(IDC_RADIO2, On32bit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoaderDlg message handlers

BOOL CLoaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	bits=0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLoaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CLoaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLoaderDlg::OnStart()
{
	CString cbox,cmdline;
	int cur;

	cur=m_resolution.GetCurSel();
	if(cur<0 || bits==0)
	{
		MessageBox("Du musst schon alles einstellen!");
		return;
	}

	m_resolution.GetLBText(cur,cbox);

	cmdline.Format("MainGame.exe %sx%d",cbox,bits);

	if(WinExec(cmdline,0)<=31)
		MessageBox("Das Programm konnte nicht gestartet werden.");
	else
		ExitProcess(0);
}

void CLoaderDlg::On16bit()
{
	bits=16;
}

void CLoaderDlg::On32bit()
{
	bits=32;
}