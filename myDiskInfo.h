#if !defined(AFX_MYDISKINFO_H__FFE6A036_5099_482D_8D7F_26743BEB6670__INCLUDED_)
#define AFX_MYDISKINFO_H__FFE6A036_5099_482D_8D7F_26743BEB6670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// myDiskInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// myDiskInfo dialog

class myDiskInfo : public CDialog
{
// Construction
public:
	myDiskInfo(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(myDiskInfo)
	enum { IDD = IDD_DISKINFO };
	CRichEditCtrl	m_richEdit;
	//}}AFX_DATA
	
	void showDiskInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(myDiskInfo)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(myDiskInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDISKINFO_H__FFE6A036_5099_482D_8D7F_26743BEB6670__INCLUDED_)
