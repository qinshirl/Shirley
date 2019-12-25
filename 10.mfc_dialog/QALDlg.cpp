// QALDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QAL.h"
#include "QALDlg.h"
#include "base64.h"
#include "AddQQAccount.h"
#include "Options.h"
#include "QALLogin.h"
// #include "KAES.h"
// #include "md5.h"

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAL dialog

CQAL::CQAL(CWnd* pParent /*=NULL*/)
	: CDialog(CQAL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQAL)
	m_SearcheKeyWord = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQAL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQAL)
	DDX_Control(pDX, COM_SEARCHLIST, m_SearchList);
	DDX_Control(pDX, LST_QQACCOUNT, m_QQAccontList);
	DDX_Text(pDX, EDT_KEYWORD, m_SearcheKeyWord);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQAL, CDialog)
	//{{AFX_MSG_MAP(CQAL)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RCLICK, LST_QQACCOUNT, OnRclickQQAccount)
	ON_NOTIFY(LVN_ITEMCHANGED, LST_QQACCOUNT, OnItemchangedQAccount)
	ON_BN_CLICKED(BTN_STARTQQ, OnStartQQ)
	ON_BN_CLICKED(BTN_STARTACCOUNT, OnStartAccount)
	ON_BN_CLICKED(BTN_ADDQQACCOUNT, OnAddQQAccount)
	ON_COMMAND(MENU_ACCOUNTINFO, OnAccountInfo)
	ON_COMMAND(MENU_ONLYTHISQQ, OnOnlyThisQQ)
	ON_NOTIFY(NM_CLICK, LST_QQACCOUNT, OnClickQQAccount)
	ON_BN_CLICKED(BTN_MOVEUP, OnMoveUp)
	ON_COMMAND(MENU_DELETEACCOUNT, OnDeleteAccount)
	ON_BN_CLICKED(BTN_MOVEDOWN, OnMoveDown)
	ON_COMMAND(MENU_EXPORTLINK, OnExportLink)
	ON_COMMAND(MENU_HIDEME, OnHideMe)
	ON_BN_CLICKED(BTN_OPTIONS, OnOptions)
	ON_NOTIFY(NM_DBLCLK, LST_QQACCOUNT, OnDblclkQQAccount)
	ON_EN_SETFOCUS(EDT_KEYWORD, OnSetfocusKeyword)
	ON_EN_KILLFOCUS(EDT_KEYWORD, OnKillfocusKeyword)
	ON_BN_CLICKED(BTN_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAL message handlers

LoginDataInfo DataInfo;
QQAccountInfo AccountInfo;

void GetDirectory(char* szPath)
{
	int n;
	for (n = strlen(szPath) - 1; n >= 0; n--)
	{
		if (szPath[n] == '\\')
		{
			break;
		}
		szPath[n] = '\0';
	}
}

BOOL CQAL::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

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
	
	// TODO: Add extra initialization here

	//百度搜索相关
	m_SearcheKeyWord.Format("请输入要搜索的内容");
	m_SearchList.SetCurSel(0);
	UpdateData(FALSE);
	//百度搜索结束

	//定义程序工作目录
	char szExePath[256];
	ZeroMemory(szExePath, sizeof(szExePath));
	GetModuleFileName(0, szExePath, sizeof(szExePath));
	GetDirectory(szExePath);
	SetCurrentDirectory(szExePath);
		
	//定义INI文件
	ZeroMemory(m_szIniPath, sizeof(m_szIniPath));
	GetModuleFileName(0, m_szIniPath, sizeof(m_szIniPath));
	GetDirectory(m_szIniPath);
	strcat(m_szIniPath, "QAL.ini");
	m_App = AfxGetApp();
	m_App->m_pszProfileName = m_szIniPath;
	//定义INI文件结束

	//检测是否需要密码启动
	if ( m_App->GetProfileInt("Setting", "Is_StartPW", NULL) == 1)
	{
		CString QALPassWord;
		QALPassWord = m_App->GetProfileString("Setting", "PW_HASH");
		if (QALPassWord.GetLength() == 32)
		{
			CQALLogin login;
			login.DoModal();
		}
	}

	//查找当前目录下是否有QQ
	HANDLE hTmpFile;
	CString TmpQQPath;
	char szQQpath[256] = {"\0"};	
	TmpQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
	if (TmpQQPath.GetLength() == 0)
	{
		hTmpFile = ::CreateFile("CoralQQ.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE != hTmpFile)
		{
			strcpy(szQQpath, szExePath);
			strcat(szQQpath, "CoralQQ.exe");
			m_App->WriteProfileString("Setting", "QQ_Path", szQQpath);
			CloseHandle(hTmpFile);
		}
		
		else if(INVALID_HANDLE_VALUE == hTmpFile)
		{
			hTmpFile = ::CreateFile("QQ.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE != hTmpFile)
			{
				strcpy(szQQpath, szExePath);
				strcat(szQQpath, "QQ.exe");
				m_App->WriteProfileString("Setting", "QQ_Path", szQQpath);
				CloseHandle(hTmpFile);
			}
			else
			{
				CFileDialog OpenQQPath(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, NULL, NULL);
				char szTitle[] = "设定QQ.exe路径";
				char szExName[] = "应用程序\0*.exe\0\0";
				OpenQQPath.m_ofn.lpstrTitle = szTitle;
				OpenQQPath.m_ofn.lpstrFilter = szExName;
				OpenQQPath.DoModal();
				TmpQQPath = OpenQQPath.GetPathName();
				if (TmpQQPath.GetLength() != 0)
				{
					m_App->WriteProfileString("Setting", "QQ_Path", TmpQQPath.GetBuffer(0));
				}
				else
				{
					AfxMessageBox("没有设定QQ路径,请在进入程序后设置!");
				}
			}
		}
	}

	TmpQQPath = m_App->GetProfileString("Setting", "TM_Path", NULL);
	if (TmpQQPath.GetLength() == 0)
	{
		hTmpFile = ::CreateFile("TMShell.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE != hTmpFile)
		{
			strcpy(szQQpath, szExePath);
			strcat(szQQpath, "TMShell.exe");
			m_App->WriteProfileString("Setting", "TM_Path", szQQpath);
			CloseHandle(hTmpFile);
		}
	}
	//查找完毕

	//定义程序工作目录
	SetWorkDirectory();

	//看看有没有参数
	m_HaveArg = 0;
	char cmdline[256]; 
	ZeroMemory(cmdline, sizeof(cmdline));
	strcpy(cmdline, GetCommandLine());

	int YinHaoNum = 0;
	char *pCmdLine = cmdline;
	int CmdLen = 0;
	while (1)
	{
		if (CmdLen == strlen(cmdline) - 2)
		{
			break;
		}

		if (YinHaoNum == 2)
		{
			pCmdLine++;
			break;
		}
		
		if(*pCmdLine == '\"')
		{
			YinHaoNum++;
		}
		pCmdLine++;
		CmdLen++;
	}

	InitList(&m_QQAccontList);
	m_QQAccontList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_QQAccontList.InsertColumn(1, "QQ帐号", LVCFMT_LEFT, 105);
	m_QQAccontList.InsertColumn(2, "上次登录时间", LVCFMT_LEFT, 105);

	//初始化登陆图片列表
	m_LoginImage.Create(16, 16, ILC_COLOR16, 5, 1);
	m_LoginImage.SetBkColor(RGB( 0xFF, 0xFF, 0xE0 ));
	m_LoginImage.Add(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(ICO_QQONLINE)));
	m_LoginImage.Add(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(ICO_QQOFFLINE)));
	m_LoginImage.Add(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(ICO_TMONLINE)));
	m_LoginImage.Add(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(ICO_TMOFFLINE)));
	m_LoginImage.Add(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(ICO_QQGAME)));
	m_QQAccontList.SetImageList(&m_LoginImage,LVSIL_SMALL);
	
	//读取数据文件
	ULONG TmpNum;
	HANDLE hLoginData = ::CreateFile("LoginData.dat", GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLoginData == INVALID_HANDLE_VALUE)
	{
		hLoginData = ::CreateFile("LoginData.dat", GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hLoginData == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("打开数据文件失败!!!");
		}
		CloseHandle(hLoginData);
		return FALSE;
	}

	//检查数据大小，若为0则返回
	DWORD DataSize;
	if (GetFileSize(hLoginData, &DataSize) == 0)
	{
		CloseHandle(hLoginData);
		return FALSE;
	}

	::ReadFile(hLoginData, &DataInfo, sizeof(DataInfo), &TmpNum, NULL);
	if (strcmp(DataInfo.szQALClassName, "QAL.") || DataInfo.ClassVer != 0x1000)
	{
		AfxMessageBox("发现了不兼容的旧数据,\r\n旧数据将被备份为\"Logindata.bak\"");
		::CopyFile("LoginData.dat", "LoginData.bak", FALSE);
		::DeleteFile("LoginData.dat");
		CloseHandle(hLoginData);
		hLoginData = ::CreateFile("LoginData.dat", GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hLoginData == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("打开数据文件失败!!!");
		}
		CloseHandle(hLoginData);
		return FALSE;
	}

	//循环插入数据
	::SetFilePointer(hLoginData, -2, NULL, FILE_CURRENT);
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	for (int n = 0; n < DataInfo.QQAccountNum; n++)
	{
		::ReadFile(hLoginData, &AccountInfo, sizeof(AccountInfo), &TmpNum, NULL);
		//先插入到链表
		m_ListQQAccount.push_back(AccountInfo);
		it++;
		if (!strcmp(AccountInfo.QQNickName, pCmdLine))
		{
			m_HaveArg = 1;
			StartQQProcess(n, it);
		}
	}

	if (m_HaveArg == 1)
	{
		EndDialog(0);
	}

	RefreshAccountList();
	CloseHandle(hLoginData);

	EnableStartAccount();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQAL::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
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

void CQAL::OnPaint() 
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
HCURSOR CQAL::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQAL::InitList(CListCtrl *pCtrlBillsLst)
{
    DWORD dwStyle;
    dwStyle = ::GetWindowLong( pCtrlBillsLst->m_hWnd, GWL_STYLE );
    dwStyle |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_EDITLABELS;
    
    ::SetWindowLong( pCtrlBillsLst->m_hWnd, GWL_STYLE, dwStyle );
    
    dwStyle = pCtrlBillsLst->GetExtendedStyle();
    dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
    pCtrlBillsLst->SetExtendedStyle( dwStyle );
    
    pCtrlBillsLst->SetBkColor( RGB( 0xFF, 0xFF, 0xE0 ) );
    pCtrlBillsLst->SetTextBkColor( RGB( 0xFF, 0xFF, 0xE0 ) );
}

void CQAL::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg about;
	about.DoModal();
}

void CQAL::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SaveAllItems();
	std::list<StartPara*>::iterator it = m_ListStartPara.begin();
	for (int n = 0; n < m_ListStartPara.size(); n++)
	{
		delete *it;
	}
	CDialog::OnClose();
}

void CQAL::OnRclickQQAccount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex < 0)
	{
		return;
	}
    CMenu menu;
    CMenu* pmenu;
	menu.LoadMenu(MENU_MAIN_RIGHTCLICK);
    pmenu = menu.GetSubMenu(0);
    if (NULL == pmenu)
    {
        return;
    }

	//快速设置隐身
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	for (int n = 0; n < nIndex; n++)
	{
		it++;
	}
	if ((*it).QQYinShen == 40)
	{
		pmenu->CheckMenuItem(MENU_HIDEME, MF_CHECKED);
	}
	else
	{
		pmenu->CheckMenuItem(MENU_HIDEME, MF_UNCHECKED);
	}
	//快速设置隐身结束
    
    CPoint pt;
    GetCursorPos(&pt);
    pmenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);

	*pResult = 0;
}

void CQAL::EnableStartAccount()
{
	//判断是否有默认被选择的QQ帐号
	HWND hStartAccount = GetDlgItem(BTN_STARTACCOUNT)->GetSafeHwnd();
	for (int n = 0; n < m_QQAccontList.GetItemCount(); n++)
	{
		if(m_QQAccontList.GetCheck(n) == TRUE)
		{
			::EnableWindow(hStartAccount, TRUE);
			return;
		}
	}
	::EnableWindow(hStartAccount, FALSE);
}

void CQAL::OnItemchangedQAccount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	EnableStartAccount();
	*pResult = 0;
}

void CQAL::OnStartQQ() 
{
	// TODO: Add your control notification handler code here
	CString szQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
	CString szQQDir = szQQPath;
	GetDirectory(szQQDir.GetBuffer(0)) ;
	//下面要启动QQ了
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	CreateProcess(szQQPath.GetBuffer(0), NULL, NULL, NULL, FALSE, NULL, NULL, szQQDir.GetBuffer(0), &si, &pi);
	EndQALProcess();
}

void CQAL::StartQQProcess(int nIndex, std::list<QQAccountInfo>::iterator& it)
{
	//下面要启动QQ了
	CString szQQPath;
	CString szQQDir;	
	CString StartParament;
	char szTmpMD5[40];
	char szPasswdBase64[40];
	ZeroMemory(szTmpMD5, sizeof(szTmpMD5));
	ZeroMemory(szPasswdBase64, sizeof(szPasswdBase64));
	
	if (m_QQAccontList.GetCheck(nIndex) == TRUE || m_HaveArg == 1)
	{
		//确定启动的是QQ还是TM还是QQ游戏
		switch ((*it).QQLoginModle)
		{
		case 1:
			szQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
			break;
		case 2:
			szQQPath = m_App->GetProfileString("Setting", "TM_Path", NULL);
			break;
		case 3:
			szQQPath = m_App->GetProfileString("Setting", "QQ_Game", NULL);
			break;
		default:
			szQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
			break;
		}
		
		szQQDir = szQQPath;
		GetDirectory(szQQDir.GetBuffer(0));
		
		//初始化参数
		ZeroMemory(szTmpMD5, sizeof(szTmpMD5));
		ZeroMemory(szPasswdBase64, sizeof(szPasswdBase64));
		memcpy( szTmpMD5, (*it).QQPassWordMd5, sizeof((*it).QQPassWordMd5) );
		base64(szTmpMD5, szPasswdBase64); //得到了QQ密码的BASE64值
		StartParament.Format("\"%s\" /START QQUIN:%d PWDHASH:%s /STAT:%d", \
			szQQPath, (*it).QQNumber, szPasswdBase64, (*it).QQYinShen);
		
		//创建QQ进程
		StartPara* Para = new StartPara;
		m_ListStartPara.push_back(Para);
		Para->szQQPath = szQQPath;
		Para->szParament = StartParament;
		Para->szQQDir = szQQDir;
		CreatQQProcessEx(Para);
		GetLocalTime(&((*it).LoginTime));
		
		int Is_Delay;
		Is_Delay = m_App->GetProfileInt("Setting", "Is_Delay", NULL);
		Is_Delay *= 1000;
		Sleep(Is_Delay);
	}
}

void CQAL::CreatQQProcessEx(StartPara* Para)
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	CreateProcess(Para->szQQPath.GetBuffer(0), Para->szParament.GetBuffer(0), \
		NULL, NULL, FALSE, NULL, NULL, Para->szQQDir.GetBuffer(0), &si, &pi);
}

void CQAL::OnStartAccount() 
{
	// TODO: Add your control notification handler code here
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	ShowWindow(SW_HIDE);
	for (int n = 0; n < m_QQAccontList.GetItemCount(); n++)
	{
		StartQQProcess(n, it);
		it++;
	}
	ShowWindow(SW_SHOW);

	SaveAllItems();
	EndQALProcess();
}

void CQAL::OnAddQQAccount() 
{
	// TODO: Add your control notification handler code here
	SaveAllItems();
	CAddQQAccount add;
	add.m_LoginModleIndex = 0;
	add.m_AddNewAccount = 1;
	add.m_pListQQAccount = &m_ListQQAccount;
	add.m_QQAccountInfo = &AccountInfo;
	add.DoModal();
	RefreshAccountList();
}


void CQAL::OnAccountInfo() 
{
	// TODO: Add your command handler code here
	SaveAllItems();
	CAddQQAccount EditAccount;
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);

	EditAccount.m_nIndex = nIndex;
	for (int n = 0; n < nIndex; n++)
	{
		it++;
	}
	EditAccount.m_QQNumber.Format("%d", (*it).QQNumber );
	EditAccount.m_QQPassword.Format("********");
	EditAccount.m_LoginModleIndex = (*it).QQLoginModle - 1;
	EditAccount.m_QQAccountInfo = &(*it);
	EditAccount.m_AddNewAccount = 0;
	EditAccount.DoModal();
	RefreshAccountList();
}

void CQAL::InsertItem(int n, QQAccountInfo* pAccountInfo)
{
	char szTmp[20];
	ZeroMemory(szTmp, sizeof(szTmp));
	//检查登陆模式
	int LoginImage = 5;
	switch (pAccountInfo->QQLoginModle)
	{
	case 1:
		if (pAccountInfo->QQYinShen == 40)
		{
			LoginImage = 1;
		}
		else
		{
			LoginImage = 0;
		}
		break;
	case 2:
		if (pAccountInfo->QQYinShen == 40)
		{
			LoginImage = 3;
		}
		else
		{
			LoginImage = 2;
		}
		break;
	case 3:
		LoginImage = 4;
		break;
	}
	//检查登陆模式完成
	
	m_QQAccontList.InsertItem(n, pAccountInfo->QQNickName, LoginImage);
	wsprintf(szTmp, "%d年%d月%d日", pAccountInfo->LoginTime.wYear,
		pAccountInfo->LoginTime.wMonth, pAccountInfo->LoginTime.wDay);
	m_QQAccontList.SetItemText(n, 1, szTmp);
	if (pAccountInfo->IsSelect == 1)
	{
		m_QQAccontList.SetCheck(n, TRUE);
	}
}

void CQAL::RefreshAccountList()
{
	m_QQAccontList.DeleteAllItems();
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();

	for (int n = 0; n < m_ListQQAccount.size(); n++, it++)
	{
		InsertItem(n, &(*it));
	}
}

void CQAL::OnOnlyThisQQ() 
{
	// TODO: Add your command handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	for (int n = 0; n < nIndex; n++)
	{
		it++;
	}

	//下面要启动QQ了
	CString szQQPath;
	CString szQQDir;	
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	CString StartParament;
	char szTmpMD5[40];
	char szPasswdBase64[40];
	ZeroMemory(szTmpMD5, sizeof(szTmpMD5));
	ZeroMemory(szPasswdBase64, sizeof(szPasswdBase64));
	
	//确定启动的是QQ还是TM还是QQ游戏
	switch ((*it).QQLoginModle)
	{
	case 1:
		szQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
		break;
	case 2:
		szQQPath = m_App->GetProfileString("Setting", "TM_Path", NULL);
		break;
	case 3:
		szQQPath = m_App->GetProfileString("Setting", "QQ_Game", NULL);
		break;
	default:
		szQQPath = m_App->GetProfileString("Setting", "QQ_Path", NULL);
	}
	
	szQQDir = szQQPath;
	GetDirectory(szQQDir.GetBuffer(0));
	
	//初始化参数
	ZeroMemory(szTmpMD5, sizeof(szTmpMD5));
	ZeroMemory(szPasswdBase64, sizeof(szPasswdBase64));
	memcpy( szTmpMD5, (*it).QQPassWordMd5, sizeof((*it).QQPassWordMd5) );
	base64(szTmpMD5, szPasswdBase64); //得到了QQ密码的BASE64值
	StartParament.Format("\"%s\" /START QQUIN:%d PWDHASH:%s /STAT:%d", \
		szQQPath, (*it).QQNumber, szPasswdBase64, (*it).QQYinShen);
	
	//创建QQ进程
	CreateProcess(szQQPath.GetBuffer(0), StartParament.GetBuffer(0), NULL, NULL, FALSE, NULL, NULL, szQQDir.GetBuffer(0), &si, &pi);
	GetLocalTime(&((*it).LoginTime));
	//RefreshAccountList();

	EndQALProcess();
}

void CQAL::OnClickQQAccount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	if (nIndex < 0)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(FALSE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(FALSE);
		*pResult = 0;
		return;
	}

	if (m_QQAccontList.GetItemCount() == 1)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(FALSE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(FALSE);
		*pResult = 0;
		return;
	}
	
	if (nIndex > 0 && nIndex < m_QQAccontList.GetItemCount() - 1 )
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(TRUE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(TRUE);
		*pResult = 0;
		return;
	}

	if (nIndex == 0)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(FALSE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(TRUE);
		*pResult = 0;
		return;
	}

	if (nIndex == m_QQAccontList.GetItemCount() - 1)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(TRUE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(FALSE);
		*pResult = 0;
		return;
	}

	*pResult = 0;
}

void CQAL::OnMoveUp() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	nIndex--;
	
	if (nIndex == 0)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(FALSE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(TRUE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(TRUE);		
	}

	std::list<QQAccountInfo>::iterator ita = m_ListQQAccount.begin();
	std::list<QQAccountInfo>::iterator itb = m_ListQQAccount.begin();
	QQAccountInfo TmpQQInfo;
	for (int n = 0; n < nIndex; n++)
	{
		ita++;
		itb++;
	}
	itb++;

	memcpy(&TmpQQInfo, &(*itb), sizeof(QQAccountInfo));
	memcpy(&(*itb), &(*ita), sizeof(QQAccountInfo));
	memcpy(&(*ita), &TmpQQInfo, sizeof(QQAccountInfo));

	RefreshAccountList();

	m_QQAccontList.SetFocus();
	m_QQAccontList.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
}

void CQAL::OnDeleteAccount() 
{
	// TODO: Add your command handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();

	for (int n = 0; n < m_ListQQAccount.size(); n++)
	{
		if (n == nIndex)
		{
			it = m_ListQQAccount.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	RefreshAccountList();
}

void CQAL::OnMoveDown() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	nIndex++;

	std::list<QQAccountInfo>::iterator ita = m_ListQQAccount.begin();
	std::list<QQAccountInfo>::iterator itb = m_ListQQAccount.begin();
	QQAccountInfo TmpQQInfo;
	for (int n = 0; n < nIndex; n++)
	{
		ita++;
		itb++;
	}
	itb--;
	
	memcpy(&TmpQQInfo, &(*itb), sizeof(QQAccountInfo));
	memcpy(&(*itb), &(*ita), sizeof(QQAccountInfo));
	memcpy(&(*ita), &TmpQQInfo, sizeof(QQAccountInfo));
	
	RefreshAccountList();

	m_QQAccontList.SetFocus();
	m_QQAccontList.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
	
	if (nIndex == m_QQAccontList.GetItemCount() - 1)
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(TRUE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(BTN_MOVEUP)->EnableWindow(TRUE);
		GetDlgItem(BTN_MOVEDOWN)->EnableWindow(TRUE);		
	}
}

void CQAL::SaveAllItems()
{
	//下面要重写所有的Data数据到文件
	char szTmp[] = "QAL.";
	memcpy(DataInfo.szQALClassName, szTmp, 4);
	DataInfo.QQAccountNum = m_QQAccontList.GetItemCount();
	DataInfo.ClassVer = 0x1000;

	if (m_QQAccontList.GetItemCount() != 0)
	{
		HANDLE hLoginData = ::CreateFile("LoginData.dat", GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hLoginData == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("打开数据文件失败!!");
			CloseHandle(hLoginData);
			return;
		}
		DataInfo.QQAccountNum = m_ListQQAccount.size();
		DWORD TmpNum;
		::WriteFile(hLoginData, &DataInfo, sizeof(DataInfo), &TmpNum, NULL);
		::SetFilePointer(hLoginData, -2, NULL, FILE_CURRENT);
		std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
		for (int n = 0; n < DataInfo.QQAccountNum; n++)
		{
			if (m_QQAccontList.GetCheck(n) == 0)
			{
				(*it).IsSelect = 0;
			}
			else
			{
				(*it).IsSelect = 1;
			}
			::WriteFile(hLoginData, (void*)(&(*it)), sizeof(QQAccountInfo), &TmpNum, NULL);
			it++;
		}
		CloseHandle(hLoginData);
	}
	
	if (m_QQAccontList.GetItemCount() == 0)
	{
		HANDLE hLoginData = ::CreateFile("LoginData.dat", GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD DataFaileSize;
		if (GetFileSize(hLoginData, &DataFaileSize) == 0)
		{
			CloseHandle(hLoginData);
			return;
		}
		DataInfo.QQAccountNum = m_ListQQAccount.size();
		DWORD TmpNum;
		::WriteFile(hLoginData, &DataInfo, sizeof(DataInfo), &TmpNum, NULL);
		CloseHandle(hLoginData);
	}
}

void CQAL::OnExportLink() 
{
	// TODO: Add your command handler code here
	char szLoginName[256];
	ZeroMemory(szLoginName, sizeof(szLoginName));
	char szQuickLogin[] = "登陆";
	int nIndex = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	m_QQAccontList.GetItemText(nIndex, 0, szLoginName, sizeof(szLoginName));
	strcat(szQuickLogin, szLoginName);
	CFileDialog OpenLink(FALSE, NULL, szQuickLogin, OFN_OVERWRITEPROMPT, NULL, NULL);
	char szTitle[] = "生成登录快捷方式";
	char szExName[] = "快捷方式\0*.lnk\0\0";
    OpenLink.m_ofn.lpstrTitle = szTitle;
    OpenLink.m_ofn.lpstrFilter = szExName;
    OpenLink.DoModal();
	CString szLinkPath;
	szLinkPath = OpenLink.GetFileName();
	if (szLinkPath.GetLength() == 0)
	{
		return;
	}

	szLinkPath = OpenLink.GetPathName();
	char szFileEx[5];
	ZeroMemory(szFileEx, sizeof(szFileEx));
	for (int n = 0; n < 4; n++)
	{
		szFileEx[n] = (szLinkPath.GetBuffer(0))[szLinkPath.GetLength() - 4 + n];
	}
	strupr(szFileEx);
	if(strcmp(szFileEx, ".LNK") != 0)
	{
		szLinkPath += ".lnk";
	}

	//开始创建快捷方式
	HRESULT hr = CoInitialize(NULL);
	
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			//这里是我们要创建快捷方式的原始文件地址
			char szQALPath[256];
			ZeroMemory(szQALPath, sizeof(szQALPath));
			GetModuleFileName(0, szQALPath, sizeof(szQALPath));
			pisl->SetArguments(szLoginName);
			pisl->SetPath(szQALPath);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{   
				//这里是我们要创建快捷方式的目标地址
				WCHAR szTmpLnk[512];
				ZeroMemory(szTmpLnk, sizeof(szTmpLnk));
				MultiByteToWideChar(CP_ACP, NULL, szLinkPath.GetBuffer(0), 
					-1, szTmpLnk, sizeof(szTmpLnk));
				pIPF->Save(szTmpLnk, FALSE);
				pIPF->Release();
			}
			pisl->Release();
		}
		CoUninitialize();
	}

	char szExePath[256];
	ZeroMemory(szExePath, sizeof(szExePath));
	GetModuleFileName(0, szExePath, sizeof(szExePath));
	GetDirectory(szExePath);
	SetCurrentDirectory(szExePath);
}

void CQAL::OnHideMe() 
{
	// TODO: Add your command handler code here
	int nIndex  = m_QQAccontList.GetNextItem(-1, LVNI_SELECTED);
	std::list<QQAccountInfo>::iterator it = m_ListQQAccount.begin();
	
	for (int n = 0; n < nIndex; n++)
	{
		it++;
	}

	if ((*it).QQYinShen == 40)
	{
		(*it).QQYinShen = 41;
	}
	else if ((*it).QQYinShen == 41)
	{
		(*it).QQYinShen = 40;
	}
	
	RefreshAccountList();

	//m_QQAccontList.SetFocus();
	//m_QQAccontList.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
}

void CQAL::EndQALProcess()
{
	int CloseQQ;
	CloseQQ = m_App->GetProfileInt("Setting", "Is_Close", NULL);
	if (CloseQQ == 0)
	{
		SaveAllItems();
		EndDialog(0);
		ExitProcess(0);
	}
}

void CQAL::OnOptions() 
{
	// TODO: Add your control notification handler code here
	COptions op;
	op.DoModal();
}

void CQAL::OnDblclkQQAccount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_QQAccontList.GetNextItem(-1, LVNI_SELECTED) < 0)
	{
		*pResult = 0;
		return;
	}
	if (m_App->GetProfileInt("Setting", "Is_DbClickRun", NULL) == 1)
	{
		OnOnlyThisQQ();
	}
	else if (m_App->GetProfileInt("Setting", "Is_DbClickRun", NULL) == 0)
	{
		OnAccountInfo();
	}
	*pResult = 0;
}

void CQAL::SetWorkDirectory()
{
	//定义程序工作目录
	char szExePath[256];
	ZeroMemory(szExePath, sizeof(szExePath));
	GetModuleFileName(0, szExePath, sizeof(szExePath));
	GetDirectory(szExePath);
	SetCurrentDirectory(szExePath);
}

void CQAL::OnCancel() 
{
	// TODO: Add extra cleanup here
	SaveAllItems();
	CDialog::OnCancel();
}

void CQAL::OnSetfocusKeyword() 
{
	// TODO: Add your control notification handler code here
	if (!strcmp(m_SearcheKeyWord, "请输入要搜索的内容"))
	{
		m_SearcheKeyWord.Format("");
		UpdateData(FALSE);
	}
}

void CQAL::OnKillfocusKeyword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_SearcheKeyWord.GetLength() == 0)
	{
		m_SearcheKeyWord.Format("请输入要搜索的内容");
		UpdateData(FALSE);
	}
}

inline BYTE toHex(const BYTE &x)
{	
	return x > 9 ? x + 55: x + 48;
}

CString URLEncode(CString sIn)
{	
	CString sOut;	
	const int nLen = sIn.GetLength() + 1;	
	register LPBYTE pOutTmp = NULL;	
	LPBYTE pOutBuf = NULL;	
	register LPBYTE pInTmp = NULL;	
	LPBYTE pInBuf =(LPBYTE)sIn.GetBuffer(nLen);	
	BYTE b = 0;	
	
	//alloc out buffer	
	pOutBuf = (LPBYTE)sOut.GetBuffer(nLen*3 - 2);//new BYTE [nLen  * 3];
	if(pOutBuf)		
	{		
		pInTmp   = pInBuf;		
		pOutTmp = pOutBuf;
		
		// do encoding
		
		while (*pInTmp)
		{
			if(isalnum(*pInTmp))
				*pOutTmp++ = *pInTmp;
			else
				if(isspace(*pInTmp))
					*pOutTmp++ = '+';
				else
				{
					*pOutTmp++ = '%';
					*pOutTmp++ = toHex(*pInTmp>>4);
					*pOutTmp++ = toHex(*pInTmp%16);
				}
				pInTmp++;
		}
		
		*pOutTmp = '\0';
		sOut.ReleaseBuffer();
	}
	sIn.ReleaseBuffer();
	return sOut;
}

void CQAL::OnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!strcmp(m_SearcheKeyWord, "请输入要搜索的内容") || m_SearcheKeyWord.GetLength() == 0)
	{
		AfxMessageBox("请输入要搜索的内容!");
		return;
	}
	
	CString SearchUrl;
	m_SearcheKeyWord = URLEncode(m_SearcheKeyWord);
	switch (m_SearchList.GetCurSel())
	{
	case 0:
		SearchUrl.Format("http://www.baidu.com/s?tn=jobcrazydg&ct=&lm=-1&kw=&word=%s", m_SearcheKeyWord);
		//ShellExecute(NULL, NULL, "Iexplore", SearchUrl, NULL, SW_NORMAL);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 1:
		SearchUrl.Format("http://mp3.gougou.com/search?search=%s&id=11005617", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 2:
		SearchUrl.Format("http://soft.gougou.com/search?search=%s&restype=2&id=11005617&ty=0", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 3:
		SearchUrl.Format("http://movie.gougou.com/search?search=%s&id=11005617", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 4:
		SearchUrl.Format("http://image.baidu.com/i?tn=jobcrazydg&ct=201326592&lm=-1&kw=&word=%s", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 5:
		SearchUrl.Format("http://zhidao.baidu.com/q?ct=17&pn=0&tn=ikaslist&rn=10&word=%s", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	case 6:
		SearchUrl.Format("http://news.baidu.com/ns?cl=2&rn=20&tn=news&word=%s&t=1", m_SearcheKeyWord);
		ShellExecute(NULL, _T("open"), SearchUrl, NULL, NULL, SW_SHOWMAXIMIZED);
		break;
	}
}

BOOL CQAL::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN || pMsg->wParam == VK_SPACE )
	{
		if (pMsg->hwnd == (GetDlgItem(EDT_KEYWORD))->GetSafeHwnd() && pMsg->wParam == VK_RETURN)
		{
			OnSearch();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
