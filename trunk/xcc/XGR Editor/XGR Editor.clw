; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XGR Editor.h"
LastPage=0

ClassCount=7
Class1=CXGREditorApp
Class2=CXGREditorDoc
Class3=CXGREditorView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_XGREDITYPE
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=CG_IDR_POPUP_LEFT_VIEW
Resource6=IDR_XGREDITYPE (English (U.S.))
Class5=CChildFrame
Class6=CLeftView
Resource7=IDR_MAINFRAME (English (U.S.))

[CLS:CXGREditorApp]
Type=0
HeaderFile=XGR Editor.h
ImplementationFile=XGR Editor.cpp
Filter=N

[CLS:CXGREditorDoc]
Type=0
HeaderFile=XGR EditorDoc.h
ImplementationFile=XGR EditorDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CXGREditorView]
Type=0
HeaderFile=XGR EditorView.h
ImplementationFile=XGR EditorView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=ID_POPUP_DELETE

[CLS:CAboutDlg]
Type=0
HeaderFile=XGR Editor.cpp
ImplementationFile=XGR Editor.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command4=ID_APP_EXIT
Command5=ID_VIEW_STATUS_BAR
CommandCount=6

CommandCount=6
Command3=ID_FILE_MRU_FILE1
Command6=ID_APP_ABOUT

[MNU:IDR_XGREDITYPE]
Type=1
Class=CXGREditorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_NEW
Command14=ID_WINDOW_CASCADE
CommandCount=17
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_WINDOW_ARRANGE
Command17=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_STATUS_BAR
Command6=ID_WINDOW_SPLIT
CommandCount=6

[MNU:IDR_XGREDITYPE (English (U.S.))]
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
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_SPLIT
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
CommandCount=17

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_POPUP_DELETE
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:CG_IDR_POPUP_LEFT_VIEW]
Type=1
Class=?
Command1=ID_POPUP_DELETE
CommandCount=1

