#if !defined(AFX_MYSETTINGS_H__8DE9A939_B812_4701_9AF8_BFCD4ABA44E6__INCLUDED_)
#define AFX_MYSETTINGS_H__8DE9A939_B812_4701_9AF8_BFCD4ABA44E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mySettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// mySettings dialog

#include <string>
using namespace std;

class mySettings : public CDialog
{
// Construction
public:
	mySettings(CWnd* pParent = NULL);   // standard constructor

	CString GetAppPath();
	bool CreateXmlFile(string& szFileName);
	bool ReadXmlFile(string& szFileName);

// Dialog Data
	//{{AFX_DATA(mySettings)
	enum { IDD = IDD_SETTINGS };
	CEdit	m_pwd;
	CEdit	m_memory;
	CEdit	m_mail;
	CEdit	m_cpu;
	CButton	m_save;
	CButton	m_reSet;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mySettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(mySettings)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSETTINGS_H__8DE9A939_B812_4701_9AF8_BFCD4ABA44E6__INCLUDED_)
