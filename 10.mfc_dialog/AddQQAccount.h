#if !defined(AFX_ADDQQACCOUNT_H__961B3F18_6656_437F_A909_1146D5BE09F2__INCLUDED_)
#define AFX_ADDQQACCOUNT_H__961B3F18_6656_437F_A909_1146D5BE09F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQQAccount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddQQAccount dialog
#include "list"

class CAddQQAccount : public CDialog
{
// Construction
public:
	int m_AddNewAccount;
	int m_nIndex;
	int m_LoginModleIndex;
	CAddQQAccount(CWnd* pParent = NULL);   // standard constructor
	QQAccountInfo* m_QQAccountInfo;
	std::list<QQAccountInfo>* m_pListQQAccount;

// Dialog Data
	//{{AFX_DATA(CAddQQAccount)
	enum { IDD = DLG_ADDQQACCOUNT };
	CComboBox	m_LoginModle;
	CString	m_QQNumber;
	CString	m_QQPassword;
	CString	m_NickName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddQQAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddQQAccount)
	virtual BOOL OnInitDialog();
	afx_msg void OnUseNickname();
	afx_msg void OnHideLogin();
	virtual void OnOK();
	afx_msg void OnChangeQQnumber();
	afx_msg void OnSetfocusPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQQACCOUNT_H__961B3F18_6656_437F_A909_1146D5BE09F2__INCLUDED_)
