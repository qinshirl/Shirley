; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CQAL
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "QAL.h"

ClassCount=7
Class1=CQALApp
Class2=CQAL
Class3=CAboutDlg

ResourceCount=8
Resource1=DLG_SETPASSWORD
Resource2=IDR_MAINFRAME
Resource3=DLG_QALLOGIN
Resource4=IDD_QAL_DIALOG
Class4=CAddQQAccount
Resource5=DLG_ADDQQACCOUNT
Class5=COptions
Resource6=IDD_ABOUTBOX
Class6=CSetPassWord
Resource7=DLG_OPTIONS
Class7=CQALLogin
Resource8=MENU_MAIN_RIGHTCLICK

[CLS:CQALApp]
Type=0
HeaderFile=QAL.h
ImplementationFile=QAL.cpp
Filter=N

[CLS:CQAL]
Type=0
HeaderFile=QALDlg.h
ImplementationFile=QALDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=MENU_ACCOUNTINFO

[CLS:CAboutDlg]
Type=0
HeaderFile=QALDlg.h
ImplementationFile=QALDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_QAL_DIALOG]
Type=1
Class=CQAL
ControlCount=16
Control1=BTN_STARTACCOUNT,button,1476460545
Control2=BTN_STARTQQ,button,1342242817
Control3=BTN_ADDQQACCOUNT,button,1342242817
Control4=BTN_MOVEUP,button,1476460545
Control5=BTN_MOVEDOWN,button,1476460545
Control6=BTN_OPTIONS,button,1342242817
Control7=BTN_IMPORTACCOUNT,button,1476460545
Control8=BTN_ABOUT,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342177294
Control11=IDC_STATIC,button,1342177287
Control12=LST_QQACCOUNT,SysListView32,1350664197
Control13=IDC_STATIC,static,1476526080
Control14=EDT_KEYWORD,edit,1350631552
Control15=COM_SEARCHLIST,combobox,1344339971
Control16=BTN_SEARCH,button,1342242816

[MNU:MENU_MAIN_RIGHTCLICK]
Type=1
Class=CQAL
Command1=MENU_ONLYTHISQQ
Command2=MENU_EXPORTLINK
Command3=MENU_HIDEME
Command4=MENU_DELETEACCOUNT
Command5=MENU_ACCOUNTINFO
CommandCount=5

[DLG:DLG_ADDQQACCOUNT]
Type=1
Class=CAddQQAccount
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=CMB_LOGINMODLE,combobox,1344274499
Control3=IDC_STATIC,button,1342177287
Control4=CHK_USENICKNAME,button,1342242819
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=EDT_NICKNAME,edit,1484849280
Control9=EDT_QQNUMBER,edit,1350631552
Control10=EDT_PASSWORD,edit,1350631584
Control11=CHK_HIDELOGIN,button,1342242819
Control12=CHK_ALLOWFINDPSW,button,1476460547
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816

[CLS:CAddQQAccount]
Type=0
HeaderFile=AddQQAccount.h
ImplementationFile=AddQQAccount.cpp
BaseClass=CDialog
Filter=D
LastObject=EDT_QQNUMBER
VirtualFilter=dWC

[DLG:DLG_OPTIONS]
Type=1
Class=COptions
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=LST_QQPATH,SysListView32,1350631429
Control4=BTN_CLEAR,button,1342242817
Control5=BTN_BROWSE,button,1342242816
Control6=CHK_NOCLOSE,button,1342242819
Control7=CHK_AUTOUPDATE,button,1476460547
Control8=CHK_DBCLICK,button,1342242819
Control9=CHK_PASSWORD,button,1342242819
Control10=CHK_MUSTPASSWORD,button,1342242819
Control11=BTN_SETPASSWORD,button,1476460544
Control12=IDC_STATIC,static,1342308352
Control13=LST_DELAYTIME,listbox,1352732928

[CLS:COptions]
Type=0
HeaderFile=Options.h
ImplementationFile=Options.cpp
BaseClass=CDialog
Filter=D
LastObject=LST_DELAYTIME
VirtualFilter=dWC

[DLG:DLG_SETPASSWORD]
Type=1
Class=CSetPassWord
ControlCount=9
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=EDT_OLDPASSWORD,edit,1350631584
Control6=EDT_NEWPASSWORD,edit,1350631584
Control7=EDT_RETYPEPASSWORD,edit,1350631584
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[CLS:CSetPassWord]
Type=0
HeaderFile=SetPassWord.h
ImplementationFile=SetPassWord.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetPassWord
VirtualFilter=dWC

[DLG:DLG_QALLOGIN]
Type=1
Class=CQALLogin
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=EDT_PASSWORD,edit,1350631584
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CQALLogin]
Type=0
HeaderFile=QALLogin.h
ImplementationFile=QALLogin.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CQALLogin

