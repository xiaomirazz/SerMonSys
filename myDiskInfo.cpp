// myDiskInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SerMonSys.h"
#include "myDiskInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// myDiskInfo dialog


myDiskInfo::myDiskInfo(CWnd* pParent /*=NULL*/)
	: CDialog(myDiskInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(myDiskInfo)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(myDiskInfo, CDialog)
	//{{AFX_MSG_MAP(myDiskInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// myDiskInfo message handlers

BOOL myDiskInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	showDiskInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void myDiskInfo::DoDataExchange(CDataExchange* pDX) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(myDiskInfo)
	DDX_Control(pDX, IDC_RICHEDIT, m_richEdit);
	//}}AFX_DATA_MAP
}

void myDiskInfo::showDiskInfo()
{
	int DiskCount = 0;
	DWORD DiskInfo = GetLogicalDrives();
	//利用GetLogicalDrives()函数可以获取系统中逻辑驱动器的数量，函数返回的是一个32位无符号整型数据。
	while (DiskInfo)//通过循环操作查看每一位数据是否为1，如果为1则磁盘为真,如果为0则磁盘不存在。
	{
		if (DiskInfo&1)//通过位运算的逻辑与操作，判断是否为1
		{
			++DiskCount;
		}
		DiskInfo = DiskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。
		//DiskInfo = DiskInfo/2;
	}
	CString str = "逻辑磁盘数量:";
	CString temp;
	temp.Format("%d",DiskCount);
	str += temp;
	DWORD dLength = GetLogicalDriveStrings(0,NULL);
	TCHAR *dStr = new TCHAR[dLength];
	GetLogicalDriveStrings(dLength,dStr);
	
	int dType;
	bool fResult;
	int si = 0;
	__int64 i64FreeBytesToCaller;
	__int64 i64TotalBytes;
	__int64 i64FreeBytes;
	
	for (int i=0;i<dLength/4;i++)
	{
		CString strTemp = "";
		TCHAR dir[3] = {dStr[4*i],dStr[4*i+1],'\0'};
		strTemp += dir[0];
		strTemp += dir[1];

		dType = GetDriveType(dStr+i*4);
		if (dType == DRIVE_FIXED)
		{
			strTemp += "硬盘";
		}
		else if (dType == DRIVE_CDROM)
		{
			strTemp += "光驱";
		}
		else if (dType == DRIVE_REMOVABLE)
		{
			strTemp += "可移动式磁盘";
		}
		else if (dType == DRIVE_REMOTE)
		{
			strTemp += "网络磁盘";
		}
		else if (dType == DRIVE_RAMDISK)
		{
			strTemp += "虚拟RAM磁盘";
		}
		else if (dType == DRIVE_UNKNOWN)
		{
			strTemp += "未知设备";
		}
		
		fResult = GetDiskFreeSpaceEx (
			dir,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据
		if (fResult)//通过返回的BOOL数据判断驱动器是否在工作状态
		{
			strTemp += " totalSpace:";
			temp.Format("%.2f MB",(float)i64TotalBytes/1024/1024);
			strTemp += temp;
			strTemp += " freeSpace:";
			temp.Format("%.2f MB",(float)i64FreeBytesToCaller/1024/1024);
			strTemp += temp;
		}
		else
		{
			strTemp += " 设备未准备好";
		}
		if (!str.IsEmpty())
			str += "\r\n";//换行
		str += strTemp;
		si += 4;
	}
	m_richEdit.SetWindowText(str);
}