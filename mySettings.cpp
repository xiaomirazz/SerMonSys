 // mySettings.cpp : implementation file
//

#include "stdafx.h"
#include "SerMonSys.h"
#include "mySettings.h"
#include "tinystr.h"
#include "tinyxml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// mySettings dialog

mySettings::mySettings(CWnd* pParent /*=NULL*/)
	: CDialog(mySettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(mySettings)
	//}}AFX_DATA_INIT
}


void mySettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(mySettings)
	DDX_Control(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Control(pDX, IDC_EDIT_MEMORY, m_memory);
	DDX_Control(pDX, IDC_EDIT_MAIL, m_mail);
	DDX_Control(pDX, IDC_EDIT_CPU, m_cpu);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_save);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_reSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(mySettings, CDialog)
	//{{AFX_MSG_MAP(mySettings)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &mySettings::OnBnClickedButtonSave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// mySettings message handlers

CString mySettings::GetAppPath()
{//获取应用程序根目录
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	CString strModulePath(modulePath);
	strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
	return strModulePath;
}

bool mySettings::CreateXmlFile(string& szFileName)
{
	try
	{
		TiXmlDocument *myDocument = new TiXmlDocument();
		TiXmlElement *RootElement = new TiXmlElement("Server");
		myDocument->LinkEndChild(RootElement);

		TiXmlElement *SystemElement = new TiXmlElement("System");
		RootElement->LinkEndChild(SystemElement);

		SystemElement->SetAttribute("ID", "1");

		TiXmlElement *CpuElement = new TiXmlElement("CPU");
		SystemElement->LinkEndChild(CpuElement);
		TiXmlElement *MemoryElement = new TiXmlElement("Memory");
		SystemElement->LinkEndChild(MemoryElement);

		TiXmlText *CpuContent = new TiXmlText(g_cpu);
		TiXmlText *MemoryContent = new TiXmlText(g_memory);
		CpuElement->LinkEndChild(CpuContent);
		MemoryElement->LinkEndChild(MemoryContent);
		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) + seperator+szFileName;
		myDocument->SaveFile(fullPath.c_str());//保存到文件
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}

bool mySettings::ReadXmlFile(string& szFileName)
{//读取Xml文件，并遍历
	try
	{
		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) +seperator+szFileName;
		TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
		myDocument->LoadFile();
		TiXmlElement *RootElement = myDocument->RootElement();
		TiXmlElement *SystemElement = RootElement->FirstChildElement();
		TiXmlElement *CPUElement = SystemElement->FirstChildElement();
		TiXmlElement *MemoryElement = CPUElement->NextSiblingElement();
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}


void mySettings::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT_CPU,g_cpu);
	GetDlgItemText(IDC_EDIT_MEMORY,g_memory);
	GetDlgItemText(IDC_EDIT_MAIL,g_mail);
	GetDlgItemText(IDC_EDIT_PWD,g_pwd);
	string szFileName = "info.xml";
	CreateXmlFile(szFileName);
}
