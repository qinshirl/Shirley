// SetPassWord.cpp : implementation file
//

#include "stdafx.h"
#include "QAL.h"
#include "SetPassWord.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPassWord dialog


CSetPassWord::CSetPassWord(CWnd* pParent /*=NULL*/)
	: CDialog(CSetPassWord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPassWord)
	m_NewPassWord = _T("");
	m_OldPassWord = _T("");
	m_RetypePassWord = _T("");
	//}}AFX_DATA_INIT
}


void CSetPassWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPassWord)
	DDX_Text(pDX, EDT_NEWPASSWORD, m_NewPassWord);
	DDV_MaxChars(pDX, m_NewPassWord, 50);
	DDX_Text(pDX, EDT_OLDPASSWORD, m_OldPassWord);
	DDV_MaxChars(pDX, m_OldPassWord, 50);
	DDX_Text(pDX, EDT_RETYPEPASSWORD, m_RetypePassWord);
	DDV_MaxChars(pDX, m_RetypePassWord, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetPassWord, CDialog)
	//{{AFX_MSG_MAP(CSetPassWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPassWord message handlers

BOOL CSetPassWord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_App = AfxGetApp();
	CString szPassWord;
	szPassWord = m_App->GetProfileString("Setting", "PW_HASH");

	if (szPassWord.GetLength() == 0)
	{
		GetDlgItem(EDT_OLDPASSWORD)->EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetPassWord::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	CString szPassWord;
	szPassWord = m_App->GetProfileString("Setting", "PW_HASH");
	if (szPassWord.GetLength() != 0)
	{
		m_OldPassWord = MD5String(m_OldPassWord.GetBuffer(0));
		if (strcmp(szPassWord, m_OldPassWord) != 0)
		{
			AfxMessageBox("旧的密码错误!请重新输入!");
			return;
		}
	}

	if (m_NewPassWord.GetLength() == 0 || m_RetypePassWord.GetLength() == 0)
	{
		AfxMessageBox("请将内容填写完整!");
		return;
	}

	if (strcmp(m_NewPassWord, m_RetypePassWord) != 0)
	{
		AfxMessageBox("两次输入的密码不一致,请重新输入!");
		return;
	}

	m_OldPassWord = MD5String(m_NewPassWord.GetBuffer(0));

	m_App->WriteProfileString("Setting", "PW_HASH", m_OldPassWord.GetBuffer(0));

	CDialog::OnOK();
}
