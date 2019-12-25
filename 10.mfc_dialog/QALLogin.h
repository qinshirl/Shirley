#if !defined(AFX_QALLOGIN_H__581C7731_7F00_4DAA_93C3_9DB6739568E4__INCLUDED_)
#define AFX_QALLOGIN_H__581C7731_7F00_4DAA_93C3_9DB6739568E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QALLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQALLogin dialog

class CQALLogin : public CDialog
{
// Construction
public:
	CQALLogin(CWnd* pParent = NULL);   // standard constructor
	CWinApp* m_App;

// Dialog Data
	//{{AFX_DATA(CQALLogin)
	enum { IDD = DLG_QALLOGIN };
	CString	m_QALPassWord;
	CString	m_TmpPassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQALLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQALLogin)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QALLOGIN_H__581C7731_7F00_4DAA_93C3_9DB6739568E4__INCLUDED_)
