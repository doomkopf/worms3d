// Loader.h : main header file for the LOADER application
//

#if !defined(AFX_LOADER_H__D928B971_BC52_431E_BA45_5513F260A724__INCLUDED_)
#define AFX_LOADER_H__D928B971_BC52_431E_BA45_5513F260A724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoaderApp:
// See Loader.cpp for the implementation of this class
//

class CLoaderApp : public CWinApp
{
public:
	CLoaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoaderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADER_H__D928B971_BC52_431E_BA45_5513F260A724__INCLUDED_)
