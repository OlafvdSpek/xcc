; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cdlg_ccr
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XCC Cheat Reporter.h"

ClassCount=3
Class1=CXCCCheatReporterApp
Class2=CXCCCheatReporterDlg

ResourceCount=4
Resource2=IDD_XCCCHEATREPORTER_DIALOG
Resource3=IDD_XCCCHEATREPORTER_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=Cdlg_ccr
Resource4=IDD_CCR

[CLS:CXCCCheatReporterApp]
Type=0
HeaderFile=XCC Cheat Reporter.h
ImplementationFile=XCC Cheat Reporter.cpp
Filter=N

[CLS:CXCCCheatReporterDlg]
Type=0
HeaderFile=XCC Cheat ReporterDlg.h
ImplementationFile=XCC Cheat ReporterDlg.cpp
Filter=C
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CXCCCheatReporterDlg



[DLG:IDD_XCCCHEATREPORTER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CXCCCheatReporterDlg

[DLG:IDD_XCCCHEATREPORTER_DIALOG (English (U.S.))]
Type=1
Class=CXCCCheatReporterDlg
ControlCount=5
Control1=IDC_CREATE,button,1342242817
Control2=IDC_DECODE,button,1342242816
Control3=IDC_XHP,button,1342242816
Control4=IDC_PASTE,button,1342242816
Control5=IDC_GAME,combobox,1344339971

[DLG:IDD_CCR]
Type=1
Class=Cdlg_ccr
ControlCount=20
Control1=IDC_DESCRIPTION,edit,1353781380
Control2=IDC_LIST,SysListView32,1350631433
Control3=IDC_DISCONNECT,button,1342242819
Control4=IDC_RECONNECTION_ERROR,button,1342242819
Control5=IDC_GAME_SPEED,button,1342242819
Control6=IDC_CONNECTION_SPEED,button,1342242819
Control7=IDC_MAP_REVEALER,button,1342242819
Control8=IDC_MOD_MAP,button,1342242819
Control9=IDC_BUILD_ANYWHERE,button,1342242819
Control10=IDC_MONEY,button,1342242819
Control11=IDC_TECH,button,1342242819
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816
Control14=IDC_NAME,edit,1350631552
Control15=IDC_NICKNAME,combobox,1344340227
Control16=IDC_MAIL,edit,1350631552
Control17=IDC_STATS,edit,1353779332
Control18=IDC_GAME_ID,edit,1350639744
Control19=IDC_SEND_WS,button,1342242819
Control20=IDC_SEND_XHP,button,1342242819

[CLS:Cdlg_ccr]
Type=0
HeaderFile=dlg_ccr.h
ImplementationFile=dlg_ccr.cpp
BaseClass=ETSLayoutDialog
Filter=D
LastObject=Cdlg_ccr
VirtualFilter=dWC

