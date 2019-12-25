// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A930D1D1_A193_4916_902E_12AD7699C3FA__INCLUDED_)
#define AFX_STDAFX_H__A930D1D1_A193_4916_902E_12AD7699C3FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT 

struct LoginDataInfo
{
	char szQALClassName[4];
	int ClassVer;
	WORD QQAccountNum;
};

struct QQAccountInfo
{
	int RubbishDataA;
	char QQNickName[16];
	char QQPassWordMd5[16];
	int QQNumber;
	int QQYinShen;
	int QQLoginModle;
	int IsSelect;
	SYSTEMTIME LoginTime;
	char ForgetPassword[16];
};

void GetDirectory(char* szPath);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A930D1D1_A193_4916_902E_12AD7699C3FA__INCLUDED_)
