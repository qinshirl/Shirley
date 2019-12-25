// QAL.h : main header file for the QAL application
//

#if !defined(AFX_QAL_H__76244B8C_6020_4943_A77C_DB2705854B06__INCLUDED_)
#define AFX_QAL_H__76244B8C_6020_4943_A77C_DB2705854B06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQALApp:
// See QAL.cpp for the implementation of this class
//

class CQALApp : public CWinApp
{
public:
	CQALApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQALApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQALApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QAL_H__76244B8C_6020_4943_A77C_DB2705854B06__INCLUDED_)
