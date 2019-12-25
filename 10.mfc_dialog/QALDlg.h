// QALDlg.h : header file
//

#if !defined(AFX_QALDLG_H__FE2F64EC_8C9B_4DD3_94F3_CA9DBF6DA345__INCLUDED_)
#define AFX_QALDLG_H__FE2F64EC_8C9B_4DD3_94F3_CA9DBF6DA345__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQAL dialog

#include <list>

struct StartPara 
{
	CString szQQPath;
	CString szParament;
	CString szQQDir;
};

class CQAL : public CDialog
{
// Construction
private:
	std::list<StartPara*> m_ListStartPara;
	void CreatQQProcessEx(StartPara* Para);
	void SetWorkDirectory();
	void EndQALProcess();
	int m_HaveArg;
	void SaveAllItems();
	void RefreshAccountList();
	void CQAL::InsertItem(int n, QQAccountInfo* pAccountInfo);
	void EnableStartAccount();
	CImageList m_LoginImage;
	void InitList(CListCtrl *pCtrlBillsLst);
	void CQAL::StartQQProcess(int nIndex, std::list<QQAccountInfo>::iterator& it);
public:
	CQAL(CWnd* pParent = NULL);	// standard constructor
	std::list<QQAccountInfo> m_ListQQAccount;
	CWinApp* m_App;
	char m_szIniPath[250];

// Dialog Data
	//{{AFX_DATA(CQAL)
	enum { IDD = IDD_QAL_DIALOG };
	CComboBox	m_SearchList;
	CListCtrl	m_QQAccontList;
	CString	m_SearcheKeyWord;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAL)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQAL)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	afx_msg void OnRclickQQAccount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedQAccount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartQQ();
	afx_msg void OnStartAccount();
	afx_msg void OnAddQQAccount();
	afx_msg void OnAccountInfo();
	afx_msg void OnOnlyThisQQ();
	afx_msg void OnClickQQAccount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMoveUp();
	afx_msg void OnDeleteAccount();
	afx_msg void OnMoveDown();
	afx_msg void OnExportLink();
	afx_msg void OnHideMe();
	afx_msg void OnOptions();
	afx_msg void OnDblclkQQAccount(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnSetfocusKeyword();
	afx_msg void OnKillfocusKeyword();
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QALDLG_H__FE2F64EC_8C9B_4DD3_94F3_CA9DBF6DA345__INCLUDED_)
