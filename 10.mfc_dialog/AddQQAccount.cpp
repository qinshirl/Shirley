// AddQQAccount.cpp : implementation file
//

#include "stdafx.h"
#include "QAL.h"
#include "AddQQAccount.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQQAccount dialog


CAddQQAccount::CAddQQAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CAddQQAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddQQAccount)
	m_QQNumber = _T("");
	m_QQPassword = _T("");
	m_NickName = _T("");
	//}}AFX_DATA_INIT
}


void CAddQQAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQQAccount)
	DDX_Control(pDX, CMB_LOGINMODLE, m_LoginModle);
	DDX_Text(pDX, EDT_QQNUMBER, m_QQNumber);
	DDV_MaxChars(pDX, m_QQNumber, 11);
	DDX_Text(pDX, EDT_PASSWORD, m_QQPassword);
	DDV_MaxChars(pDX, m_QQPassword, 16);
	DDX_Text(pDX, EDT_NICKNAME, m_NickName);
	DDV_MaxChars(pDX, m_NickName, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQQAccount, CDialog)
	//{{AFX_MSG_MAP(CAddQQAccount)
	ON_BN_CLICKED(CHK_USENICKNAME, OnUseNickname)
	ON_BN_CLICKED(CHK_HIDELOGIN, OnHideLogin)
	ON_EN_CHANGE(EDT_QQNUMBER, OnChangeQQnumber)
	ON_EN_SETFOCUS(EDT_PASSWORD, OnSetfocusPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQQAccount message handlers

BOOL CAddQQAccount::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LoginModle.SetCurSel(m_LoginModleIndex);

// 	if (m_AddNewAccount == 1)
// 	{
// 		m_QQAccountInfo = new QQAccountInfo;
// 	}

	if(m_AddNewAccount != 1)
	{
		if (m_QQAccountInfo->QQYinShen == 40)
		{
			((CButton*)GetDlgItem(CHK_HIDELOGIN))->SetCheck(1);
		}
		else if (m_QQAccountInfo->QQYinShen == 41)
		{
			((CButton*)GetDlgItem(CHK_HIDELOGIN))->SetCheck(0);
		}
		
		m_NickName = m_QQAccountInfo->QQNickName;
		
		if(strcmp(m_NickName, m_QQNumber) == 0)
		{
			((CButton*)GetDlgItem(CHK_USENICKNAME))->SetCheck(0);
			GetDlgItem(EDT_NICKNAME)->EnableWindow(FALSE);
		}
		else
		{
			((CButton*)GetDlgItem(CHK_USENICKNAME))->SetCheck(1);
			GetDlgItem(EDT_NICKNAME)->EnableWindow(TRUE);
		}
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddQQAccount::OnUseNickname() 
{
	// TODO: Add your control notification handler code here
	if (m_AddNewAccount != 1)
	{
		if ( ((CButton*)GetDlgItem(CHK_USENICKNAME))->GetCheck() == 1)
		{
			GetDlgItem(EDT_NICKNAME)->EnableWindow(TRUE);
			m_NickName.Format("%s", m_QQAccountInfo->QQNickName);
			UpdateData(FALSE);
		}
		else
		{
			GetDlgItem(EDT_NICKNAME)->EnableWindow(FALSE);
			m_NickName = m_QQNumber;
			UpdateData(FALSE);
		}
	}
	else
	{
		if ( ((CButton*)GetDlgItem(CHK_USENICKNAME))->GetCheck() == 1)
		{
			GetDlgItem(EDT_NICKNAME)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(EDT_NICKNAME)->EnableWindow(FALSE);
		}
	}
}

void CAddQQAccount::OnHideLogin() 
{
	// TODO: Add your control notification handler code here
	if ( ((CButton*)GetDlgItem(CHK_HIDELOGIN))->GetCheck() == 1 )
	{
		m_QQAccountInfo->QQYinShen = 40;
	}
	else
	{
		m_QQAccountInfo->QQYinShen = 41;
	}
}

void CAddQQAccount::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	//检查帐户别名
	if ( ((CButton*)GetDlgItem(CHK_USENICKNAME))->GetCheck() == 1 && m_NickName.GetLength() == 0 )
	{
		AfxMessageBox("还没有填写帐户别名!");
		return;
	}

	//检查帐号和密码是否填写
	if (m_QQNumber.GetLength() == 0 || m_QQPassword.GetLength() == 0)
	{
		AfxMessageBox("请将帐户和密码填写完整!");
		return;
	}

	//保存昵称
	strcpy(m_QQAccountInfo->QQNickName, m_NickName.GetBuffer(0));

	//保存是否隐身
	if ( ((CButton*)GetDlgItem(CHK_HIDELOGIN))->GetCheck() == 1)
	{
		m_QQAccountInfo->QQYinShen = 40;
	}
	else
	{
		m_QQAccountInfo->QQYinShen = 41;
	}

	//保存
	if (strcmp(m_QQPassword.GetBuffer(0), "********") != 0)
	{
		char szTmpMD5[36];
		memcpy(&(m_QQAccountInfo->QQPassWordMd5), MD5HEX(m_QQPassword.GetBuffer(0), szTmpMD5), \
			sizeof(m_QQAccountInfo->QQPassWordMd5))  ;
	}

	m_QQAccountInfo->QQNumber = atoi(m_QQNumber.GetBuffer(0));

	m_QQAccountInfo->QQLoginModle = m_LoginModle.GetCurSel() + 1;

	if (m_AddNewAccount == 1)
	{
		m_QQAccountInfo->IsSelect = 0;
		GetLocalTime(&(m_QQAccountInfo->LoginTime));
		m_QQAccountInfo->RubbishDataA = 0;
		ZeroMemory(m_QQAccountInfo->ForgetPassword, sizeof(m_QQAccountInfo->ForgetPassword));
		m_pListQQAccount->push_back(*m_QQAccountInfo);
		//delete m_QQAccountInfo;
	}

	CDialog::OnOK();
}

void CAddQQAccount::OnChangeQQnumber() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int StrLen;
	UpdateData(TRUE);
	StrLen = m_QQNumber.GetLength();
	char TmpChar;
	for (int m = 0; m <= StrLen;)
	{
		TmpChar = (m_QQNumber.GetBuffer(0))[m];
		if ( (TmpChar < 48 || TmpChar > 57) && TmpChar != 0 )
		{
			for (int n = m; n < StrLen; n++)
			{
				(m_QQNumber.GetBuffer(0))[n] = (m_QQNumber.GetBuffer(0))[n + 1];
			}
			StrLen--;
		}
		else
		{
			++m;
		}
	}
	UpdateData(FALSE);

	if ( ((CButton*)GetDlgItem(CHK_USENICKNAME))->GetCheck() == 0 )
	{
		m_NickName = m_QQNumber;
		UpdateData(FALSE);
	}
}

void CAddQQAccount::OnSetfocusPassword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (!strcmp(m_QQPassword.GetBuffer(0), "********"))
	{
		m_QQPassword = "";
	}

	UpdateData(FALSE);
}
