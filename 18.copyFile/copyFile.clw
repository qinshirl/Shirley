; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCopyFileDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "copyFile.h"

ClassCount=3
Class1=CCopyFileApp
Class2=CCopyFileDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COPYFILE_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_COPYFILE_DIALOG (English (U.S.))

[CLS:CCopyFileApp]
Type=0
HeaderFile=copyFile.h
ImplementationFile=copyFile.cpp
Filter=N

[CLS:CCopyFileDlg]
Type=0
HeaderFile=copyFileDlg.h
ImplementationFile=copyFileDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PROGRESSBAR

[CLS:CAboutDlg]
Type=0
HeaderFile=copyFileDlg.h
ImplementationFile=copyFileDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_COPYFILE_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CCopyFileDlg

[DLG:IDD_COPYFILE_DIALOG (English (U.S.))]
Type=1
Class=CCopyFileDlg
ControlCount=8
Control1=BTN_BROWSE1,button,1342242816
Control2=BTN_BROWSE2,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=EBX_CPFROM,edit,1484849280
Control6=EBX_CPTO,edit,1484849280
Control7=IDC_PROGRESSBAR,msctls_progress32,1350565888
Control8=BTN_CP,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

