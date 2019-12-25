#if !defined(AFX_OPTIONS_H__CB575452_935D_4624_841C_079D780CAC9D__INCLUDED_)
#define AFX_OPTIONS_H__CB575452_935D_4624_841C_079D780CAC9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptions dialog

class COptions : public CDialog
{
// Construction
public:
	CWinApp* m_App;
	void COptions::InitList(CListCtrl *pCtrlBillsLst);
	COptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = DLG_OPTIONS };
	CListBox	m_ListDelayTime;
	CListCtrl	m_QQPathList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickQQPath(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClearPath();
	afx_msg void OnBrowsePath();
	virtual void OnOK();
	afx_msg void OnPassword();
	afx_msg void OnSetPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__CB575452_935D_4624_841C_079D780CAC9D__INCLUDED_)
