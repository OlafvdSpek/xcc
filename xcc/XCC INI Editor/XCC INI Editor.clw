; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CINILeftView
LastTemplate=CTreeView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xcc ini editor.h"
LastPage=0

ClassCount=12
Class1=CCrystalEditView
Class2=CCrystalTextBuffer
Class3=CCrystalTextView
Class4=CEditReplaceDlg
Class5=CFindTextDlg
Class6=CINIChildFrame
Class7=CINIDoc
Class8=CINIMainFrame
Class9=CINIView
Class10=CXIEApp
Class11=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME (English (U.S.))
Class12=CINILeftView
Resource3=IDR_INITYPE (English (U.S.))

[CLS:CCrystalEditView]
Type=0
BaseClass=CCrystalTextView
HeaderFile=CCrystalEditView.h
ImplementationFile=CCrystalEditView.cpp

[CLS:CCrystalTextBuffer]
Type=0
BaseClass=CCmdTarget
HeaderFile=CCrystalTextBuffer.h
ImplementationFile=CCrystalTextBuffer.cpp

[CLS:CCrystalTextView]
Type=0
BaseClass=CView
HeaderFile=CCrystalTextView.h
ImplementationFile=CCrystalTextView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CEditReplaceDlg]
Type=0
BaseClass=CDialog
HeaderFile=CEditReplaceDlg.h
ImplementationFile=CEditReplaceDlg.cpp

[CLS:CFindTextDlg]
Type=0
BaseClass=CDialog
HeaderFile=CFindTextDlg.h
ImplementationFile=CFindTextDlg.cpp

[CLS:CINIChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=INIChildFrm.h
ImplementationFile=INIChildFrm.cpp

[CLS:CINIDoc]
Type=0
BaseClass=CDocument
HeaderFile=INIDoc.h
ImplementationFile=INIDoc.cpp

[CLS:CINIMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=INIMainFrm.h
ImplementationFile=INIMainFrm.cpp
Filter=M

[CLS:CINIView]
Type=0
BaseClass=CCrystalEditView
HeaderFile=INIView.h
ImplementationFile=INIView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CXIEApp]
Type=0
BaseClass=CWinApp
HeaderFile=XCC INI Editor.h
ImplementationFile=XCC INI Editor.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=XCC INI Editor.cpp
ImplementationFile=XCC INI Editor.cpp

[DLG:IDD_EDIT_REPLACE]
Type=1
Class=CEditReplaceDlg

[DLG:IDD_EDIT_FIND]
Type=1
Class=CFindTextDlg

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
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
CommandCount=4

[MNU:IDR_INITYPE (English (U.S.))]
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
Command9=ID_EDIT_REDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_DELETE
Command14=ID_EDIT_SELECT_ALL
Command15=ID_EDIT_FIND
Command16=ID_EDIT_REPEAT
Command17=ID_EDIT_FIND_PREVIOUS
Command18=ID_EDIT_REPLACE
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_SPLIT
CommandCount=23

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CINILeftView]
Type=0
HeaderFile=INILeftView.h
ImplementationFile=INILeftView.cpp
BaseClass=CTreeView
Filter=C
VirtualFilter=VWC
LastObject=ID_WINDOW_SPLIT

