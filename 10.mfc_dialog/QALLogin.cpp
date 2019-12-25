// QALLogin.cpp : implementation file
//

#include "stdafx.h"
#include "QAL.h"
#include "QALLogin.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQALLogin dialog


CQALLogin::CQALLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CQALLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQALLogin)
	m_QALPassWord = _T("");
	//}}AFX_DATA_INIT
}


void CQALLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQALLogin)
	DDX_Text(pDX, EDT_PASSWORD, m_QALPassWord);
	DDV_MaxChars(pDX, m_QALPassWord, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQALLogin, CDialog)
	//{{AFX_MSG_MAP(CQALLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQALLogin message handlers

static int LoginTimes;

BOOL CQALLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_App = AfxGetApp();
	LoginTimes = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CQALLogin::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	m_QALPassWord = MD5String(m_QALPassWord.GetBuffer(0));

	m_TmpPassWord = m_App->GetProfileString("Setting", "PW_HASH");

	if ( strcmp( m_TmpPassWord.GetBuffer(0), m_QALPassWord.GetBuffer(0) ) )
	{
		if (LoginTimes == 2)
		{
			AfxMessageBox("已达到密码重试上限,程序将自动退出!");
			ExitProcess(0);
		}
		AfxMessageBox("密码不正确!请重新输入!");
		LoginTimes++;
		return;
	}

	CDialog::OnOK();
}

void CQALLogin::OnCancel() 
{
	// TODO: Add extra cleanup here
	ExitProcess(0);
	CDialog::OnCancel();
}
