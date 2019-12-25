#if !defined(AFX_SETPASSWORD_H__129F9011_F392_412D_862D_07A3EE3B6A43__INCLUDED_)
#define AFX_SETPASSWORD_H__129F9011_F392_412D_862D_07A3EE3B6A43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPassWord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPassWord dialog

class CSetPassWord : public CDialog
{
// Construction
public:
	CSetPassWord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetPassWord)
	enum { IDD = DLG_SETPASSWORD };
	CString	m_NewPassWord;
	CString	m_OldPassWord;
	CString	m_RetypePassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPassWord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetPassWord)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

private:
	CWinApp* m_App;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPASSWORD_H__129F9011_F392_412D_862D_07A3EE3B6A43__INCLUDED_)
