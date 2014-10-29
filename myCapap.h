#if !defined(AFX_MYCAPAP_H__54DFA4CE_105F_41D8_B147_B5962170E4D3__INCLUDED_)
#define AFX_MYCAPAP_H__54DFA4CE_105F_41D8_B147_B5962170E4D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// myCapap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// myCapap dialog

class myCapap : public CDialog
{
// Construction
public:
	LRESULT OnMyRepaint(WPARAM wparam, LPARAM lparam);
	myCapap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(myCapap)
	enum { IDD = IDD_CAPABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(myCapap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(myCapap)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnPaint();
	afx_msg BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCAPAP_H__54DFA4CE_105F_41D8_B147_B5962170E4D3__INCLUDED_)
