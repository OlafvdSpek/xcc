; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXCCMIXEditorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xcc mix editor.h"
LastPage=0

ClassCount=4
Class1=CMIXList
Class2=CMIXOptions
Class3=CXCCMIXEditorApp
Class4=CXCCMIXEditorDlg

ResourceCount=2
Resource1=IDD_XCCMIXEDITOR_DIALOG (English (U.S.))
Resource2=IDD_OPTIONS

[CLS:CMIXList]
Type=0
BaseClass=CListCtrl
HeaderFile=MIXList.h
ImplementationFile=MIXList.cpp
LastObject=CMIXList

[CLS:CMIXOptions]
Type=0
BaseClass=CDialog
HeaderFile=MIXOptions.h
ImplementationFile=MIXOptions.cpp

[CLS:CXCCMIXEditorApp]
Type=0
BaseClass=CWinApp
HeaderFile=XCC MIX Editor.h
ImplementationFile=XCC MIX Editor.cpp

[CLS:CXCCMIXEditorDlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=XCC MIX EditorDlg.h
ImplementationFile=XCC MIX EditorDlg.cpp
LastObject=CXCCMIXEditorDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_OPTIONS]
Type=1
Class=CMIXOptions
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_ENCRYPTED,button,1342242819
Control4=IDC_CHECK_CHECKSUM,button,1342242819
Control5=IDC_COMBO_GAME,combobox,1344339971

[DLG:IDD_XCCMIXEDITOR_DIALOG]
Type=1
Class=CXCCMIXEditorDlg

[DLG:IDD_XCCMIXEDITOR_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_LIST,SysListView32,1350631433
Control2=IDC_BUTTON_NEW,button,1342242816
Control3=IDC_BUTTON_OPEN,button,1342242816
Control4=IDC_BUTTON_SAVE,button,1342242816
Control5=IDC_BUTTON_COMPACT,button,1342242816
Control6=IDC_BUTTON_CLOSE,button,1342242816
Control7=IDC_BUTTON_LOAD_KEY,button,1342242816
Control8=IDC_BUTTON_DELETE,button,1342242816
Control9=IDC_BUTTON_OPTIONS,button,1342242816
Control10=IDC_BUTTON_XCC_HOME_PAGE,button,1342242816
Control11=IDC_EDIT_STATUS,edit,1350633600
Control12=IDC_BUTTON_INSERT,button,1342242816

