; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXCCAudioPlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xcc audio player.h"
LastPage=0

ClassCount=3
Class1=CXCCAudioPlayerApp
Class2=CXCCAudioPlayerDlg
Class3=CXCCAudioPlayerInfoDlg

ResourceCount=3
Resource1=IDD_XCCAUDIOPLAYER_DIALOG
Resource2=IDD_XCCDIRECTORIES
Resource3=IDD_INFO

[CLS:CXCCAudioPlayerApp]
Type=0
BaseClass=CWinApp
HeaderFile=XCC Audio Player.h
ImplementationFile=XCC Audio Player.cpp
LastObject=CXCCAudioPlayerApp

[CLS:CXCCAudioPlayerDlg]
Type=0
BaseClass=CDialog
HeaderFile=XCC Audio PlayerDlg.h
ImplementationFile=XCC Audio PlayerDlg.cpp
LastObject=IDOPENVQA
Filter=D
VirtualFilter=dWC

[CLS:CXCCAudioPlayerInfoDlg]
Type=0
BaseClass=CDialog
HeaderFile=XCCAudioPlayerInfoDlg.h
ImplementationFile=XCCAudioPlayerInfoDlg.cpp

[DLG:IDD_XCCAUDIOPLAYER_DIALOG]
Type=1
Class=CXCCAudioPlayerDlg
ControlCount=16
Control1=IDOK,button,1342242816
Control2=IDC_STATUSBAR,static,1342312576
Control3=IDC_LIST1,SysListView32,1350664205
Control4=IDEXTRACT,button,1342242816
Control5=IDOPENMIX,button,1342242816
Control6=IDSETDIRECTORIES,button,1342242816
Control7=IDSTOP,button,1342242816
Control8=IDINFO,button,1342242816
Control9=IDPLAY,button,1342242817
Control10=IDC_OpenMovies,button,1342242816
Control11=IDC_OpenScores,button,1342242816
Control12=IDC_OpenSounds,button,1342242816
Control13=IDSHUFFLE,button,1342242816
Control14=IDEXTRACT_RAW,button,1342242816
Control15=IDOPENAUD,button,1342242816
Control16=IDOPENVQA,button,1342242816

[DLG:IDD_INFO]
Type=1
Class=CXCCAudioPlayerInfoDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_XCCDIRECTORIES]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_PRIMARY,edit,1350631552
Control6=IDC_EDIT_SECONDARY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_CD,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_DATA,edit,1350631552

