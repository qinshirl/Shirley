// copyFileDlg.h : header file
//

#if !defined(AFX_COPYFILEDLG_H__60D9390F_4434_4D4C_8971_20136B3FB6A2__INCLUDED_)
#define AFX_COPYFILEDLG_H__60D9390F_4434_4D4C_8971_20136B3FB6A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCopyFileDlg dialog

class CCopyFileDlg : public CDialog
{
// Construction
public:
	void copy_file();
	CCopyFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCopyFileDlg)
	enum { IDD = IDD_COPYFILE_DIALOG };
	CProgressCtrl	m_cp_progress;
	CString	m_ebx_cpfrom;
	CString	m_cbx_cpto;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCopyFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse1();
	afx_msg void OnEnter_CP_From();
	afx_msg void OnBrowse2();
	afx_msg void OnCp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYFILEDLG_H__60D9390F_4434_4D4C_8971_20136B3FB6A2__INCLUDED_)
