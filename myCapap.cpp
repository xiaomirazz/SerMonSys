// myCapap.cpp : implementation file
//

#include "stdafx.h"
#include "SerMonSys.h"
#include "myCapap.h"
#include "CpuInfo.h"
#include "mySettings.h"
#include "smtp.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// myCapap dialog

//自定义变量

#define WM_MY_REPAINT (WM_USER +100)

int g_flags = 1;
double dbIdleTime = 0;
CWnd *pWnd = NULL;
int a_dbIdleTime[281];
int g_num = 0;

double memSize = 0;
int a_memSize[281];
int memTotal = 0;
int memAvail = 0;

myCapap::myCapap(CWnd* pParent /*=NULL*/)
	: CDialog(myCapap::IDD, pParent)
{
	//{{AFX_DATA_INIT(myCapap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void myCapap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(myCapap)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(myCapap, CDialog)
	//{{AFX_MSG_MAP(myCapap)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_PAINT()
	ON_MESSAGE(WM_MY_REPAINT, OnMyRepaint)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// myCapap message handlers

UINT getCpuInfo(double &dbIdleTime,LARGE_INTEGER &liOldIdleTime,LARGE_INTEGER &liOldSystemTime)
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo; 
	SYSTEM_TIME_INFORMATION SysTimeInfo; 
	SYSTEM_BASIC_INFORMATION SysBaseInfo; 
	double dbSystemTime; 
	LONG status; 
	
	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"),"NtQuerySystemInformation");
	
	if (!NtQuerySystemInformation) 
		return 1;
	
	// get number of processors in the system 
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL); 
	if (status != NO_ERROR) 
		return 2;
	// get new system time 
	status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0); 
	if (status!=NO_ERROR) 
		return 3;
	
	// get new CPU's idle time 
	status =NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL); 
	if (status != NO_ERROR) 
		return 4;
	
	// if it's a first call - skip it 
	if (liOldIdleTime.QuadPart != 0) 
	{ 
		// CurrentValue = NewValue - OldValue 
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime); //空闲时间
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - 	Li2Double(liOldSystemTime); //总时间
		
		// CurrentCpuIdle = IdleTime / SystemTime 
		dbIdleTime = dbIdleTime / dbSystemTime;
		
		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors 
		dbIdleTime = 100.0 - dbIdleTime * 100.0 /
			(double)SysBaseInfo.bKeNumberProcessors + 0.5;
		
	}
	
	// store new CPU's idle and system time 
	liOldIdleTime = SysPerfInfo.liIdleTime; 
	liOldSystemTime = SysTimeInfo.liKeSystemTime;
	
	// wait one second 
	return 0;
}

UINT getMemInfo(MEMORYSTATUS &memory)
{
	::GlobalMemoryStatus(&memory);
	return 0;
}


UINT MyThreadFunction( LPVOID pParam )
{	
	LARGE_INTEGER liOldIdleTime = {0,0}; 
	LARGE_INTEGER liOldSystemTime = {0,0};
	MEMORYSTATUS memory;
	while(g_flags)
	{
		ofstream out("a.txt",ios::app);

		getCpuInfo(dbIdleTime,liOldIdleTime,liOldSystemTime);
		getMemInfo(memory);
		memSize = memory.dwMemoryLoad;
		CString str;
		str.Format("%2.0f      %2.0f\n",dbIdleTime,memSize);
		out.write(str,strlen(str));
		flush(out);
		double MemorySetting = atoi(g_memory);
		if (MemorySetting < memSize)
		{
			send();
		}
		memAvail = memory.dwAvailPhys;
		memTotal = memory.dwTotalPhys;
		a_memSize[g_num] = int(memSize);
		pWnd->SendMessage(WM_MY_REPAINT);
		a_dbIdleTime[g_num] = (int)dbIdleTime;
		if(g_num < 281)
		{
			g_num++;
		}
		else
		{
			for(int i =0; i < 281; i++)
			{
				a_dbIdleTime[i] = a_dbIdleTime[i +1];
				a_memSize[i] = a_memSize[i +1];
			}
			a_dbIdleTime[g_num] = (int)dbIdleTime;
			a_memSize[g_num] = int(memSize);
			g_num--;
		}
		Sleep(1000); 	
	}
	return 0;
}

void myCapap::OnPaint() 
{
	CPaintDC dc(this); // device context for painting  
	CDC dcMem;
	CRect rect;
	GetClientRect( &rect );
	CBitmap bmp;
	bmp.CreateCompatibleBitmap( &dc, rect.Width(), rect.Height() );
	dcMem.CreateCompatibleDC( &dc );
	dcMem.SelectObject( &bmp );
	dcMem.FillSolidRect(rect,RGB(236,233,216));
	CBrush brush;										//画刷
	brush.CreateSolidBrush(RGB(0,0,0));

	CPen pen,pen1,pen2,pen3,pen5;						//画笔
	pen1.CreatePen(PS_SOLID,1,RGB(0,120,0));
	pen2.CreatePen(PS_SOLID,1,RGB(250,0,0));
	pen3.CreatePen(PS_SOLID,1,RGB(0,0,0));
	pen5.CreatePen(PS_SOLID,1,RGB(0,250,0));

	HFONT   hf;											//字体
	LOGFONT logFont;
	logFont.lfHeight = 15;
	logFont.lfWidth   = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	strcpy (logFont.lfFaceName, "Times New Roman");
	hf=CreateFontIndirect(&logFont);   
	dcMem.SetBkMode(TRANSPARENT); 

	dcMem.SelectObject( &brush );			//cpu使用率
	dcMem.Rectangle(CRect(40,40,90,160));
	int num = 0;
	int i,j;
	for( i = 50; i <= 80; i++)
	{
		for( j = 46; j < 146; j++)
		{
			if((j -8) % 3 != 0)
			if((j-6)% 3 ==0)
			{
				if(i % 2 == 0)
				{
					//if( i != 26)
					dcMem.SetPixel(CPoint(i,j),RGB(0,150,0));
				}
			}
			else
			{
				if((i ) % 2 != 0)
				{
					if( i != 25 )
					dcMem.SetPixel(CPoint(i,j),RGB(0,150,0));
				}
			}
		}
	}

	dcMem.SelectObject(&pen5);
	for( i = 0 ; i < (int)dbIdleTime + 2; i++)
	{
		if(i % 3 != 0)
		{
			dcMem.MoveTo(50,146 - i);
			dcMem.LineTo(81,146 - i);
		}
	}
	 
	dcMem.SelectObject(hf);   
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(RGB(0,250,0));
	CString str;
	str.Format("%d",(int)dbIdleTime);
	str+="%";
	dcMem.DrawText(str,CRect(50,147,80,167),1);
	
	dcMem.SelectObject(&pen3);
	dcMem.MoveTo(65,46);
	dcMem.LineTo(65,146);
	
	dcMem.Rectangle(CRect(130,40,410,160));	//cpu使用历史记录
	dcMem.SelectObject(&pen1);				
	
	for( i = 40; i <= 160; i+=10)
	{
		dcMem.MoveTo(130,i);
		dcMem.LineTo(410,i);
	}
	for(int j = 130; j < 410; j+=10)
	{
		dcMem.MoveTo(j,40);
		dcMem.LineTo(j,160);	
	}
	dcMem.SelectObject(&pen5);
	dcMem.MoveTo(410 ,140);
	for( j = 0; j <g_num ; j++)
	{		
		dcMem.LineTo(410 - j,140-a_dbIdleTime[j]);	
	}

	dcMem.SelectObject( &pen3 );		
	dcMem.Rectangle(CRect(40,200,95,320)); //内存使用率
	num = 0;
	for( i = 50; i <= 80; i++)
	{
		for( j = 206; j < 306; j++)
		{
			if((j -8) % 3 != 0)
			if((j-6)% 3 ==0)
			{
				if(i % 2 == 0)
				{
					//if( i != 26)
					dcMem.SetPixel(CPoint(i,j),RGB(0,150,0));
				}
			}
			else
			{
				if((i ) % 2 != 0)
				{
					if( i != 25 )
					dcMem.SetPixel(CPoint(i,j),RGB(0,150,0));
				}
			}
		}
	}

	dcMem.SelectObject(&pen5);
	for( i = 0 ; i < (int)memSize + 2; i++)
	{
		if(i % 3 != 0)
		{
			dcMem.MoveTo(50,305 - i);
			dcMem.LineTo(81,305 - i);
		}
	}
	 
	dcMem.SelectObject(hf);   
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(RGB(0,250,0));
	str.Format("%d",(int)memSize);
	str+="%";
	dcMem.DrawText(str,CRect(50,306,80,326),1);
	
	dcMem.SelectObject(&pen3);
	dcMem.MoveTo(65,200);
	dcMem.LineTo(65,306);
	
	dcMem.Rectangle(CRect(130,200,410,320));	//内存使用历史记录
	dcMem.SelectObject(&pen1);
	
	for( i = 200; i <= 320; i+=10)//绘制横线
	{
		dcMem.MoveTo(130,i);
		dcMem.LineTo(410,i);
	}
	for( j = 130; j < 410; j+=10)
	{
		dcMem.MoveTo(j,200);
		dcMem.LineTo(j,320);	
	}
	dcMem.SelectObject(&pen5);
	dcMem.MoveTo(410 ,316);

	for( j = 0; j <g_num ; j++)
	{		
		dcMem.LineTo(410 - j,316-a_memSize[j]);	
	}


	dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	bmp.DeleteObject();        
	dcMem.DeleteDC();
}

BOOL myCapap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	ofstream out("a.txt");
	CString str;
	str.Format("CPU    内存\n");
	out.write(str,strlen(str));
	pWnd = CWnd::FromHandle(m_hWnd);
	AfxBeginThread(MyThreadFunction,NULL,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT myCapap::OnMyRepaint(WPARAM wparam, LPARAM lparam)
{
	this->Invalidate(FALSE);

// 	CString str;
// 	str.Format("可用物理内存     %dK", memAvail/1024);
// 	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
// 	
// 	str.Format("内存总容量       %dK", memTotal/1024);
// 	GetDlgItem(IDC_STATIC2)->SetWindowText(str);

	return 0;
}

HBRUSH myCapap::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//pDC->SetBkMode(TRANSPARENT);
	//return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

