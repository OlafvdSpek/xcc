; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXCCModLauncherDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XCC Mod Launcher.h"

ClassCount=3
Class1=CXCCModLauncherApp
Class2=CXCCModLauncherDlg

ResourceCount=4
Resource2=IDD_XCCMODLAUNCHER_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=Cdownload_dlg
Resource3=IDD_DOWNLOAD_UPDATE
Resource4=IDD_MODE

[CLS:CXCCModLauncherApp]
Type=0
HeaderFile=XCC Mod Launcher.h
ImplementationFile=XCC Mod Launcher.cpp
Filter=D
LastObject=CXCCModLauncherApp

[CLS:CXCCModLauncherDlg]
Type=0
HeaderFile=XCC Mod LauncherDlg.h
ImplementationFile=XCC Mod LauncherDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BANNER



[DLG:IDD_XCCMODLAUNCHER_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_BANNER,static,1342177806
Control2=IDOK,button,1476460545
Control3=IDC_BUTTON_MANUAL,button,1476460544
Control4=IDC_BUTTON_XHP,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_BUTTON_UPDATE,button,1342242816
Control7=IDC_BUTTON_SITE,button,1476460544

[DLG:IDD_DOWNLOAD_UPDATE]
Type=1
Class=Cdownload_dlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SOURCE,edit,1350633600
Control4=IDC_DESTINATION,edit,1350633600
Control5=IDC_PROGRESS,msctls_progress32,1350565888
Control6=IDC_FSIZE,edit,1350641792
Control7=IDC_STATIC,static,1342308352

[CLS:Cdownload_dlg]
Type=0
HeaderFile=download_dlg.h
ImplementationFile=download_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cdownload_dlg

[DLG:IDD_MODE]
Type=1
Class=?
ControlCount=3
Control1=IDC_MODE,combobox,1344339971
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

