// SerMonSysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerMonSys.h"
#include "SerMonSysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerMonSysDlg dialog

CSerMonSysDlg::CSerMonSysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerMonSysDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerMonSysDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerMonSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerMonSysDlg)
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerMonSysDlg, CDialog)
	//{{AFX_MSG_MAP(CSerMonSysDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_MENU_SHUTDOWN, OnMenuShutdown)
	ON_COMMAND(IDC_MENU_REBOOT, OnMenuReboot)
	ON_COMMAND(IDC_MENU_LOGOFF, OnMenuLogoff)
	ON_COMMAND(IDC_MENU_EXIT, OnMenuExit)
	ON_COMMAND(IDC_MENU_ABOUT, OnMenuAbout)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerMonSysDlg message handlers

BOOL CSerMonSysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	//添加显示IDC_MENU1
	m_Menu.LoadMenu(IDR_MENU1);//装载IDR_MENU1菜单资源
	SetMenu(&m_Menu);//和当前窗口关联起来
	m_Menu.Detach();//分离

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//添加三个tab页
	m_TabCtrl.InsertItem(0,_T("硬盘"));
	m_TabCtrl.InsertItem(1,_T("性能"));
	m_TabCtrl.InsertItem(2,_T("设置"));

	m_diskInfo.Create(IDD_DISKINFO,&m_TabCtrl);
	m_capDlg.Create(IDD_CAPABILITY,&m_TabCtrl);
	m_settings.Create(IDD_SETTINGS,&m_TabCtrl);

	CRect r;
	m_TabCtrl.GetClientRect (&r);
	m_diskInfo.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//关于对话框的修改
void CSerMonSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
// 	else
// 	{
// 		CDialog::OnSysCommand(nID, lParam);
// 	}
	if (nID == SW_SHOW)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerMonSysDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerMonSysDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//处理menu菜单shutdown
void CSerMonSysDlg::OnMenuShutdown() 
{
	// TODO: Add your command handler code here
	if(MessageBox("确定关闭计算机？","信息询问",MB_YESNO) == IDYES)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); 
		tkp.PrivilegeCount = 1; 
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,  (PTOKEN_PRIVILEGES)NULL, 0);
		ExitWindowsEx(EWX_SHUTDOWN,NULL);
	}
}
//处理menu菜单下的reboot
void CSerMonSysDlg::OnMenuReboot() 
{
	// TODO: Add your command handler code here
	if(MessageBox("计算机重新启动？","信息提示",MB_YESNO)==IDYES)
	{
		HANDLE hToken; 
		TOKEN_PRIVILEGES tkp; 
		OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES |  TOKEN_QUERY,&hToken);
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); 
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
		
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,  (PTOKEN_PRIVILEGES)NULL, 0); 
		ExitWindowsEx(EWX_REBOOT,NULL);
	}	
}
//处理menu菜单下的logoff
void CSerMonSysDlg::OnMenuLogoff() 
{
	// TODO: Add your command handler code here
	if(MessageBox("确定要注销当前用户？","信息询问",MB_YESNO) == IDYES)
	{
		::ExitWindowsEx(EWX_LOGOFF,NULL);
	}
}

//处理关闭服务器监控系统
void CSerMonSysDlg::OnMenuExit() 
{
	// TODO: Add your command handler code here
	OnOK();
}



void CSerMonSysDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	OnSysCommand(SW_SHOW,0);
}

//处理tab切换
void CSerMonSysDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_TabCtrl.GetClientRect (&r);
	
	switch(m_TabCtrl.GetCurSel())
	{
	case 0:
		m_diskInfo.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);
		m_capDlg.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW ); 
		m_settings.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW ); 
		break;
	case 1:
		m_diskInfo.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_capDlg.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW ); 
		m_settings.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW );  
		break;
	case 2:
		m_diskInfo.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_capDlg.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW ); 
		m_settings.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW ); 
		break;
		
	}
	*pResult = 0;
}
