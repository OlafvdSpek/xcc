; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cdlg_edit_bin32
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xif editor.h"
LastPage=0

ClassCount=10
Class1=CChildFrame
Class2=Cdlg_edit_bin32
Class3=CMainFrame
Class4=CXIFEditorApp
Class5=CAboutDlg
Class6=CXIFEditorDoc
Class7=CXIFList
Class8=CXIFTree

ResourceCount=7
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_EDIT_INT32
Resource3=IDR_XIFTYPE (English (U.S.))
Resource4=CG_IDR_POPUP_XIFLIST
Resource5=IDD_EDIT_BIN32
Class9=Cdlg_edit_int32
Resource6=CG_IDR_POPUP_XIFTREE
Class10=Cdlg_edit_string
Resource7=IDD_EDIT_STRING

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
VirtualFilter=mfWC

[CLS:Cdlg_edit_bin32]
Type=0
BaseClass=CDialog
HeaderFile=dlg_edit_bin32.h
ImplementationFile=dlg_edit_bin32.cpp
Filter=D
VirtualFilter=dWC
LastObject=Cdlg_edit_bin32

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CXIFEditorApp]
Type=0
BaseClass=CWinApp
HeaderFile=XIF Editor.h
ImplementationFile=XIF Editor.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=XIF Editor.cpp
ImplementationFile=XIF Editor.cpp
LastObject=CAboutDlg

[CLS:CXIFEditorDoc]
Type=0
BaseClass=CDocument
HeaderFile=XIF EditorDoc.h
ImplementationFile=XIF EditorDoc.cpp

[CLS:CXIFList]
Type=0
BaseClass=CListView
HeaderFile=XIFList.h
ImplementationFile=XIFList.cpp
LastObject=ID_POPUP_LOAD_VALUE_PCX
Filter=C
VirtualFilter=VWC

[CLS:CXIFTree]
Type=0
BaseClass=CTreeView
HeaderFile=XIFTree.h
ImplementationFile=XIFTree.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_POPUP_INSERT

[DLG:IDD_EDIT_BIN32]
Type=1
Class=Cdlg_edit_bin32
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VALUE,edit,1350631560
Control4=IDC_KEY,edit,1350633600

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
CommandCount=6

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
CommandCount=6

[MNU:IDR_XIFTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
CommandCount=17

[MNU:CG_IDR_POPUP_XIFTREE]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_POPUP_INSERT
Command5=ID_POPUP_REMOVE
CommandCount=5

[MNU:CG_IDR_POPUP_XIFLIST]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_POPUP_INSERT_BIN32
Command5=ID_POPUP_INSERT_BINARY
Command6=ID_POPUP_INSERT_INT32
Command7=ID_POPUP_INSERT_STRING
Command8=ID_POPUP_EDIT_VALUE
Command9=ID_POPUP_LOAD_VALUE_PCX
Command10=ID_POPUP_LOAD_VALUE_RAW
Command11=ID_POPUP_REMOVE
CommandCount=11

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_POPUP_EDIT_VALUE
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_EDIT_INT32]
Type=1
Class=Cdlg_edit_int32
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VALUE,edit,1350631552
Control4=IDC_KEY,edit,1350633600

[CLS:Cdlg_edit_int32]
Type=0
HeaderFile=dlg_edit_int32.h
ImplementationFile=dlg_edit_int32.cpp
BaseClass=CDialog
Filter=D
LastObject=Cdlg_edit_int32
VirtualFilter=dWC

[DLG:IDD_EDIT_STRING]
Type=1
Class=Cdlg_edit_string
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VALUE,edit,1350631552
Control4=IDC_KEY,edit,1350633600

[CLS:Cdlg_edit_string]
Type=0
HeaderFile=dlg_edit_string.h
ImplementationFile=dlg_edit_string.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

