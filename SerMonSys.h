// SerMonSys.h : main header file for the SERMONSYS application
//

#if !defined(AFX_SERMONSYS_H__FCDC6BD3_6F91_45C7_A664_B0F97E9BF2B0__INCLUDED_)
#define AFX_SERMONSYS_H__FCDC6BD3_6F91_45C7_A664_B0F97E9BF2B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerMonSysApp:
// See SerMonSys.cpp for the implementation of this class
//

class CSerMonSysApp : public CWinApp
{
public:
	CSerMonSysApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerMonSysApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerMonSysApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERMONSYS_H__FCDC6BD3_6F91_45C7_A664_B0F97E9BF2B0__INCLUDED_)
