// Options.cpp : implementation file
//

#include "stdafx.h"
#include "QAL.h"
#include "Options.h"
#include "SetPassWord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog


COptions::COptions(CWnd* pParent /*=NULL*/)
	: CDialog(COptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Control(pDX, LST_DELAYTIME, m_ListDelayTime);
	DDX_Control(pDX, LST_QQPATH, m_QQPathList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
	ON_NOTIFY(NM_CLICK, LST_QQPATH, OnClickQQPath)
	ON_BN_CLICKED(BTN_CLEAR, OnClearPath)
	ON_BN_CLICKED(BTN_BROWSE, OnBrowsePath)
	ON_BN_CLICKED(CHK_PASSWORD, OnPassword)
	ON_BN_CLICKED(BTN_SETPASSWORD, OnSetPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers

BOOL COptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_App = AfxGetApp();

	InitList(&m_QQPathList);
	
	m_QQPathList.InsertColumn(0, "程序类型", LVCFMT_LEFT, 70);
	m_QQPathList.InsertColumn(1, "程序路径", LVCFMT_LEFT, 200);

	m_QQPathList.InsertItem(0, "QQ");
	m_QQPathList.InsertItem(1, "TM");
	m_QQPathList.InsertItem(2, "QQ游戏");

	m_QQPathList.SetItemText(0, 1, m_App->GetProfileString("Setting", "QQ_Path",
		NULL) );
	m_QQPathList.SetItemText(1, 1, m_App->GetProfileString("Setting", "TM_Path",
		NULL) );
	m_QQPathList.SetItemText(2, 1, m_App->GetProfileString("Setting", "QQ_Game",
		NULL) );

	
	if ( m_App->GetProfileInt("Setting", "Is_Close", NULL) == 1)
	{
		((CButton*)GetDlgItem(CHK_NOCLOSE))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(CHK_NOCLOSE))->SetCheck(0);
	}

	if ( m_App->GetProfileInt("Setting", "Is_DbClickRun", NULL) == 1)
	{
		((CButton*)GetDlgItem(CHK_DBCLICK))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(CHK_DBCLICK))->SetCheck(0);
	}

	CString PW_HASH;
	PW_HASH = m_App->GetProfileString("Setting", "PW_HASH", NULL);
	if ( PW_HASH.GetLength() == 0)
	{
		((CButton*)GetDlgItem(CHK_PASSWORD))->SetCheck(0);
		GetDlgItem(BTN_SETPASSWORD)->EnableWindow(FALSE);
		GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(CHK_PASSWORD))->SetCheck(1);
		GetDlgItem(BTN_SETPASSWORD)->EnableWindow(TRUE);
		GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(TRUE);
	}

	if ( m_App->GetProfileInt("Setting", "Is_StartPW", NULL) == 1)
	{
		((CButton*)GetDlgItem(CHK_MUSTPASSWORD))->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(CHK_MUSTPASSWORD))->SetCheck(0);
	}

	//将浏览和清除按钮禁用
	GetDlgItem(BTN_CLEAR)->EnableWindow(FALSE);
	GetDlgItem(BTN_BROWSE)->EnableWindow(FALSE);

	//设置延迟时间
	char szTmpTime[4];
	int nListData = m_App->GetProfileInt("Setting", "Is_Delay", NULL);
	if (nListData < 0 || nListData > 9)
	{
		nListData = 0;
	}
	for (int n = 9; n >=0; n--)
	{
		m_ListDelayTime.AddString(itoa(n, szTmpTime, 10));
		if (nListData == n)
		{
			m_ListDelayTime.SetCurSel(9 - n);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptions::InitList(CListCtrl *pCtrlBillsLst)
{
    DWORD dwStyle;
    dwStyle = ::GetWindowLong( pCtrlBillsLst->m_hWnd, GWL_STYLE );
    dwStyle |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_EDITLABELS;
    
    ::SetWindowLong( pCtrlBillsLst->m_hWnd, GWL_STYLE, dwStyle );
    
    dwStyle = pCtrlBillsLst->GetExtendedStyle();
    dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
    pCtrlBillsLst->SetExtendedStyle( dwStyle );
    
    pCtrlBillsLst->SetBkColor( RGB(255, 255, 255 ) );
    pCtrlBillsLst->SetTextBkColor( RGB(255, 255, 255) );
}

void COptions::OnClickQQPath(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQPathList.GetNextItem(-1, LVNI_SELECTED);
	if (nIndex < 0 || nIndex > m_QQPathList.GetItemCount() - 1)
	{
		//将浏览和清除按钮禁用
		GetDlgItem(BTN_CLEAR)->EnableWindow(FALSE);
		GetDlgItem(BTN_BROWSE)->EnableWindow(FALSE);
		return;
	}

	//将浏览和清除按钮启用
	GetDlgItem(BTN_CLEAR)->EnableWindow(TRUE);
	GetDlgItem(BTN_BROWSE)->EnableWindow(TRUE);

	*pResult = 0;
}

void COptions::OnClearPath() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQPathList.GetNextItem(-1, LVNI_SELECTED);
	if (nIndex < 0 || nIndex > m_QQPathList.GetItemCount() - 1)
	{
		//将浏览和清除按钮禁用
		return;
	}
	m_QQPathList.SetItemText(nIndex, 1, "");
}

void COptions::OnBrowsePath() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_QQPathList.GetNextItem(-1, LVNI_SELECTED);
	CString QQPathStr;
	CFileDialog OpenLink(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, NULL, NULL);
    OpenLink.m_ofn.lpstrTitle = "设定程序路径";
    OpenLink.m_ofn.lpstrFilter = "可执行文件\0*.exe\0\0";
	QQPathStr = m_QQPathList.GetItemText(nIndex, 1);
	GetDirectory(QQPathStr.GetBuffer(0));
	OpenLink.m_ofn.lpstrInitialDir = QQPathStr;
    OpenLink.DoModal();

	QQPathStr = OpenLink.GetPathName();

	if (QQPathStr.GetLength() == 0)
	{
		return;
	}

	m_QQPathList.SetItemText(nIndex, 1, QQPathStr);
}

void COptions::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString QQPath;
	QQPath = m_QQPathList.GetItemText(0 ,1);
	m_App->WriteProfileString("Setting", "QQ_Path", QQPath);

	QQPath = m_QQPathList.GetItemText(1 ,1);
	m_App->WriteProfileString("Setting", "TM_Path", QQPath);

	QQPath = m_QQPathList.GetItemText(2 ,1);
	m_App->WriteProfileString("Setting", "QQ_Game", QQPath);

	if ( ((CButton*)GetDlgItem(CHK_NOCLOSE))->GetCheck() == 1 )
	{
		m_App->WriteProfileInt("Setting", "Is_Close", 1);
	}
	else
	{
		m_App->WriteProfileInt("Setting", "Is_Close", 0);
	}

	if ( ((CButton*)GetDlgItem(CHK_DBCLICK))->GetCheck() == 1 )
	{
		m_App->WriteProfileInt("Setting", "Is_DbClickRun", 1);
	}
	else
	{
		m_App->WriteProfileInt("Setting", "Is_DbClickRun", 0);
	}

	if ( ((CButton*)GetDlgItem(CHK_PASSWORD))->GetCheck() == 0 )
	{
		m_App->WriteProfileString("Setting", "PW_HASH", "");
		m_App->WriteProfileInt("Setting", "Is_StartPW", 0);
	}
	else if ( ((CButton*)GetDlgItem(CHK_PASSWORD))->GetCheck() == 1 )
	{
		if ( ((CButton*)GetDlgItem(CHK_MUSTPASSWORD))->GetCheck() == 1 )
		{
			m_App->WriteProfileInt("Setting", "Is_StartPW", 1);
		}
		else
		{
			m_App->WriteProfileInt("Setting", "Is_StartPW", 0);
		}
	}

	char szListData[4];
	m_ListDelayTime.GetText(m_ListDelayTime.GetTopIndex(), szListData);
	m_App->WriteProfileString("Setting", "Is_Delay", szListData);

	CDialog::OnOK();
}

void COptions::OnPassword() 
{
	// TODO: Add your control notification handler code here
	if ( ((CButton*)GetDlgItem(CHK_PASSWORD))->GetCheck() == 1 )
	{
		CString QALPassWord;
		QALPassWord = m_App->GetProfileString("Setting", "PW_HASH");
		if (QALPassWord.GetLength() != 0)
		{
			GetDlgItem(BTN_SETPASSWORD)->EnableWindow(TRUE);
			GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(TRUE);
			return;
		}

		CSetPassWord setpass;
		setpass.DoModal();

		QALPassWord = m_App->GetProfileString("Setting", "PW_HASH");
		if (QALPassWord.GetLength() != 0)
		{
			GetDlgItem(BTN_SETPASSWORD)->EnableWindow(TRUE);
			GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(TRUE);
			((CButton*)GetDlgItem(CHK_PASSWORD))->SetCheck(1);
		}
		else
		{
			GetDlgItem(BTN_SETPASSWORD)->EnableWindow(FALSE);
			GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(FALSE);
			((CButton*)GetDlgItem(CHK_PASSWORD))->SetCheck(0);
		}
	}
	else
	{
		MessageBox("这个操作将清空本程序的启动密码,但是不影响QQ密码!", "注意!", MB_OK);
		((CButton*)GetDlgItem(CHK_MUSTPASSWORD))->SetCheck(0);
		GetDlgItem(BTN_SETPASSWORD)->EnableWindow(FALSE);
		GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(FALSE);
	}	
}

void COptions::OnSetPassword() 
{
	// TODO: Add your control notification handler code here
	if ( ((CButton*)GetDlgItem(CHK_PASSWORD))->GetCheck() == 1 )
	{
		CSetPassWord setpass;
		setpass.DoModal();
		CString PW_HASH;
		PW_HASH = m_App->GetProfileString("Setting", "PW_HASH");
		if ( PW_HASH.GetLength() != 0 )
		{
			GetDlgItem(BTN_SETPASSWORD)->EnableWindow(TRUE);
			GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(BTN_SETPASSWORD)->EnableWindow(FALSE);
			GetDlgItem(CHK_MUSTPASSWORD)->EnableWindow(FALSE);
		}
	}
	else
	{
		MessageBox("这个操作将清空本程序的启动密码,但是不影响QQ密码!", "警告!", MB_OK);
		GetDlgItem(BTN_SETPASSWORD)->EnableWindow(FALSE);
	}
}
