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
	//����GetLogicalDrives()�������Ի�ȡϵͳ���߼����������������������ص���һ��32λ�޷����������ݡ�
	while (DiskInfo)//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�
	{
		if (DiskInfo&1)//ͨ��λ������߼���������ж��Ƿ�Ϊ1
		{
			++DiskCount;
		}
		DiskInfo = DiskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��
		//DiskInfo = DiskInfo/2;
	}
	CString str = "�߼���������:";
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
			strTemp += "Ӳ��";
		}
		else if (dType == DRIVE_CDROM)
		{
			strTemp += "����";
		}
		else if (dType == DRIVE_REMOVABLE)
		{
			strTemp += "���ƶ�ʽ����";
		}
		else if (dType == DRIVE_REMOTE)
		{
			strTemp += "�������";
		}
		else if (dType == DRIVE_RAMDISK)
		{
			strTemp += "����RAM����";
		}
		else if (dType == DRIVE_UNKNOWN)
		{
			strTemp += "δ֪�豸";
		}
		
		fResult = GetDiskFreeSpaceEx (
			dir,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,�������ص��Ǹ�BOOL��������
		if (fResult)//ͨ�����ص�BOOL�����ж��������Ƿ��ڹ���״̬
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
			strTemp += " �豸δ׼����";
		}
		if (!str.IsEmpty())
			str += "\r\n";//����
		str += strTemp;
		si += 4;
	}
	m_richEdit.SetWindowText(str);
}