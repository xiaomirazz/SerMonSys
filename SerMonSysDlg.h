// SerMonSysDlg.h : header file
//

#if !defined(AFX_SERMONSYSDLG_H__7A654701_719D_4DEC_9A13_F9F49A53D4BD__INCLUDED_)
#define AFX_SERMONSYSDLG_H__7A654701_719D_4DEC_9A13_F9F49A53D4BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "myCapap.h"
#include "myDiskInfo.h"
#include "mySettings.h"

/////////////////////////////////////////////////////////////////////////////
// CSerMonSysDlg dialog

class CSerMonSysDlg : public CDialog
{
// Construction
public:
	CSerMonSysDlg(CWnd* pParent = NULL);	// standard constructor

	myCapap m_capDlg;
	myDiskInfo m_diskInfo;
	mySettings m_settings;

// Dialog Data
	//{{AFX_DATA(CSerMonSysDlg)
	enum { IDD = IDD_SERMONSYS_DIALOG };
	CTabCtrl	m_TabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerMonSysDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	
	CMenu m_Menu;

	// Generated message map functions
	//{{AFX_MSG(CSerMonSysDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuShutdown();
	afx_msg void OnMenuReboot();
	afx_msg void OnMenuLogoff();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuAbout();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERMONSYSDLG_H__7A654701_719D_4DEC_9A13_F9F49A53D4BD__INCLUDED_)
