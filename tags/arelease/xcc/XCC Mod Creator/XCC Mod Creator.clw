; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXCCModCreatorView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XCC Mod Creator.h"
LastPage=0

ClassCount=8
Class1=CXCCModCreatorApp
Class2=CXCCModCreatorDoc
Class3=CXCCModCreatorView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_XCCMODTYPE
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=CG_IDR_POPUP
Class5=CChildFrame
Class6=CLeftView
Resource6=IDR_XCCMODTYPE (English (U.S.))
Resource7=IDR_MAINFRAME (English (U.S.))
Class8=Coptions_dlg
Resource8=IDD_OPTIONS

[CLS:CXCCModCreatorApp]
Type=0
HeaderFile=XCC Mod Creator.h
ImplementationFile=XCC Mod Creator.cpp
Filter=N

[CLS:CXCCModCreatorDoc]
Type=0
HeaderFile=XCC Mod CreatorDoc.h
ImplementationFile=XCC Mod CreatorDoc.cpp
Filter=N

[CLS:CXCCModCreatorView]
Type=0
HeaderFile=XCC Mod CreatorView.h
ImplementationFile=XCC Mod CreatorView.cpp
Filter=W
BaseClass=CListView
VirtualFilter=VWC
LastObject=ID_POPUP_EXPLORE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_VIEW_REFRESH


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=ID_MOD_DEACTIVATE

[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC

[CLS:CAboutDlg]
Type=0
HeaderFile=XCC Mod Creator.cpp
ImplementationFile=XCC Mod Creator.cpp
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
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7
Command3=ID_FILE_MRU_FILE1

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_XCCMODTYPE]
Type=1
Class=CXCCModCreatorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
CommandCount=18
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT

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
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_XCCMODTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_EXPORT
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_INSERT
Command14=ID_EDIT_DELETE
Command15=ID_EDIT_SELECT_ALL
Command16=ID_EDIT_INVERT_SELECTION
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_VIEW_REFRESH
Command20=ID_MOD_ACTIVATE
Command21=ID_VIEW_LAUNCH
Command22=ID_MOD_DEACTIVATE
Command23=ID_MOD_CLEAR_GAME_DIRECTORY
Command24=ID_VIEW_OPTIONS
Command25=ID_WINDOW_NEW
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_TILE_HORZ
Command28=ID_WINDOW_ARRANGE
Command29=ID_APP_ABOUT
CommandCount=29

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_COPY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_DELETE
Command9=ID_EDIT_CUT
Command10=ID_VIEW_REFRESH
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_VIEW_LAUNCH
Command14=ID_VIEW_OPTIONS
Command15=ID_EDIT_INSERT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_POPUP_OPEN
Command19=ID_EDIT_CUT
Command20=ID_EDIT_UNDO
CommandCount=20

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
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

[MNU:CG_IDR_POPUP]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_POPUP_OPEN
Command5=ID_POPUP_EXPLORE
Command6=ID_EDIT_INSERT
Command7=ID_EDIT_DELETE
CommandCount=7

[DLG:IDD_OPTIONS]
Type=1
Class=Coptions_dlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NAME,edit,1350631552
Control8=IDC_MAIL,edit,1350631552
Control9=IDC_LINK_TITLE,edit,1350631552
Control10=IDC_LINK,edit,1350631552
Control11=IDC_GAME,combobox,1344339971
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MOD_NAME,edit,1350631552

[CLS:Coptions_dlg]
Type=0
HeaderFile=options_dlg.h
ImplementationFile=options_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Coptions_dlg

