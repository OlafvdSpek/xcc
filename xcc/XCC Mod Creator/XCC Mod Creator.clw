; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Coptions_dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XCC Mod Creator.h"
LastPage=0

ClassCount=9
Class1=CXCCModCreatorApp
Class2=CXCCModCreatorDoc
Class3=CXCCModCreatorView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=7
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDR_XCCMODTYPE
Resource4=CG_IDR_POPUP
Resource5=IDR_XCCMODTYPE (English (U.S.))
Class5=CChildFrame
Class6=CLeftView
Resource6=IDD_ABOUTBOX (English (U.S.))
Class8=Coptions_dlg
Class9=Cexport_options_dlg
Resource7=IDD_OPTIONS

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
LastObject=CXCCModCreatorView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=ID_FILE_IMPORT

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
CommandCount=6

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
Command24=ID_MOD_OPTIONS
Command25=ID_MOD_REPORT
Command26=ID_WINDOW_NEW
Command27=ID_WINDOW_CASCADE
Command28=ID_WINDOW_TILE_HORZ
Command29=ID_WINDOW_ARRANGE
Command30=ID_LAUNCH_XAP
Command31=ID_LAUNCH_XED
Command32=ID_LAUNCH_XMR
Command33=ID_LAUNCH_XME
Command34=ID_LAUNCH_XMC
Command35=ID_LAUNCH_XML
Command36=ID_LAUNCH_FS
Command37=ID_LAUNCH_FA
Command38=ID_LAUNCH_SE
Command39=ID_LAUNCH_SEMM
Command40=ID_LAUNCH_RAGE
CommandCount=40

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
Command14=ID_MOD_OPTIONS
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

[CLS:Coptions_dlg]
Type=0
HeaderFile=options_dlg.h
ImplementationFile=options_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Coptions_dlg

[CLS:Cexport_options_dlg]
Type=0
HeaderFile=export_options_dlg.h
ImplementationFile=export_options_dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=Cexport_options_dlg
VirtualFilter=dWC

[DLG:IDD_OPTIONS]
Type=1
Class=Coptions_dlg
ControlCount=29
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NAME,edit,1350631552
Control12=IDC_MAIL,edit,1350631552
Control13=IDC_LINK_TITLE,edit,1350631552
Control14=IDC_LINK,edit,1350631552
Control15=IDC_MOD_NAME,edit,1350631552
Control16=IDC_GAME,combobox,1344339971
Control17=IDC_MOD_VERSION,edit,1350631552
Control18=IDC_MOD_UCF,edit,1350631552
Control19=IDC_CSF_DIFF_COMPRESSION,button,1342242819
Control20=IDC_INI_DIFF_COMPRESSION,button,1342242819
Control21=IDC_CUSTOM_BUTTON_TEXT,button,1342242819
Control22=IDC_XHP_BUTTON,button,1342242819
Control23=IDC_EXIT_BUTTON,button,1342242819
Control24=IDC_UPDATE_BUTTON,button,1342242819
Control25=IDC_MANUAL_BUTTON,button,1342242819
Control26=IDC_SITE_BUTTON,button,1342242819
Control27=IDC_CONFIRM_DEACTIVATE,button,1342242819
Control28=IDC_SHP_COMPRESSION,button,1342242819
Control29=IDC_VXL_COMPRESSION,button,1342242819

