; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cproperties_dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XCC TMP Editor.h"
LastPage=0

ClassCount=8
Class1=CXCCTMPEditorApp
Class2=CXCCTMPEditorDoc
Class3=CXCCTMPEditorView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=8
Resource1=IDR_TMPTYPE (English (U.S.))
Resource2=CG_IDR_POPUP_LEFT_VIEW
Resource3=IDR_TMPTYPE
Class5=CChildFrame
Class6=CLeftView
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDR_MAINFRAME (English (U.S.))
Class8=Cproperties_dlg
Resource6=IDD_PROPERTIES
Resource7=CG_IDR_POPUP_LEFT_VIEW (English (U.S.))
Resource8=IDD_PROPERTIES (English (U.S.))

[CLS:CXCCTMPEditorApp]
Type=0
HeaderFile=XCC TMP Editor.h
ImplementationFile=XCC TMP Editor.cpp
Filter=N

[CLS:CXCCTMPEditorDoc]
Type=0
HeaderFile=XCC TMP EditorDoc.h
ImplementationFile=XCC TMP EditorDoc.cpp
Filter=N
LastObject=ID_PALET_LUNAR

[CLS:CXCCTMPEditorView]
Type=0
HeaderFile=XCC TMP EditorView.h
ImplementationFile=XCC TMP EditorView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_POPUP_INSERT


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
LastObject=ID_PALET_URBAN2

[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CListView
VirtualFilter=VWC
LastObject=ID_POPUP_COPY_IMAGE

[CLS:CAboutDlg]
Type=0
HeaderFile=XCC TMP Editor.cpp
ImplementationFile=XCC TMP Editor.cpp
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

[MNU:IDR_TMPTYPE]
Type=1
Class=CXCCTMPEditorView
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

[MNU:IDR_TMPTYPE (English (U.S.))]
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
Command12=ID_POPUP_INSERT
Command13=ID_POPUP_DELETE
Command14=ID_EDIT_SELECT_ALL
Command15=ID_EDIT_INVERT_SELECTION
Command16=ID_PALET_LOAD
Command17=ID_PALET_DESERT
Command18=ID_PALET_LUNAR
Command19=ID_PALET_URBAN2
Command20=ID_PALET_SNOW
Command21=ID_PALET_TEMPERATE
Command22=ID_PALET_URBAN
Command23=ID_VIEW_TRUE_HEIGHT
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
CommandCount=27

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
Command8=ID_POPUP_DELETE
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_POPUP_INSERT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_POPUP_PROPERTIES
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

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

[MNU:CG_IDR_POPUP_LEFT_VIEW]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_POPUP_COPY_COMPLETE
Command3=ID_POPUP_COPY_IMAGE
Command4=ID_POPUP_COPY_EXTRA_IMAGE
Command5=ID_POPUP_PASTE_COMPLETE
Command6=ID_POPUP_PASTE_IMAGE
Command7=ID_POPUP_PASTE_EXTRA_IMAGE
Command8=ID_POPUP_LOAD_COMPLETE
Command9=ID_POPUP_LOADASPCX_IMAGE
Command10=ID_POPUP_LOADASPCX_EXTRAIMAGE
Command11=ID_POPUP_SAVE_COMPLETE
Command12=ID_POPUP_SAVEASPCX_IMAGE
Command13=ID_POPUP_SAVEASPCX_EXTRAIMAGE
Command14=ID_POPUP_INSERT
Command15=ID_POPUP_DELETE
Command16=ID_POPUP_PROPERTIES
CommandCount=16

[DLG:IDD_PROPERTIES]
Type=1
Class=Cproperties_dlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_X,edit,1350639744
Control11=IDC_Y,edit,1350639744
Control12=IDC_X_EXTRA,edit,1350639744
Control13=IDC_Y_EXTRA,edit,1350639744
Control14=IDC_HEIGHT,edit,1350639744
Control15=IDC_TERRAIN_TYPE,edit,1350639744
Control16=IDC_RAMP_TYPE,edit,1350639744

[CLS:Cproperties_dlg]
Type=0
HeaderFile=properties_dlg.h
ImplementationFile=properties_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cproperties_dlg

[DLG:IDD_PROPERTIES (English (U.S.))]
Type=1
Class=?
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_X,edit,1350639744
Control11=IDC_Y,edit,1350639744
Control12=IDC_X_EXTRA,edit,1350631552
Control13=IDC_Y_EXTRA,edit,1350639744
Control14=IDC_HEIGHT,edit,1350639744
Control15=IDC_TERRAIN_TYPE,edit,1350639744
Control16=IDC_RAMP_TYPE,edit,1350639744

[MNU:CG_IDR_POPUP_LEFT_VIEW (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_POPUP_COPY_COMPLETE
Command3=ID_POPUP_COPY_IMAGE
Command4=ID_POPUP_COPY_EXTRA_IMAGE
Command5=ID_POPUP_PASTE_COMPLETE
Command6=ID_POPUP_PASTE_IMAGE
Command7=ID_POPUP_PASTE_EXTRA_IMAGE
Command8=ID_POPUP_LOAD_COMPLETE
Command9=ID_POPUP_LOADASPCX_IMAGE
Command10=ID_POPUP_LOADASPCX_EXTRAIMAGE
Command11=ID_POPUP_SAVE_COMPLETE
Command12=ID_POPUP_SAVEASPCX_IMAGE
Command13=ID_POPUP_SAVEASPCX_EXTRAIMAGE
Command14=ID_POPUP_INSERT
Command15=ID_POPUP_DELETE
Command16=ID_POPUP_DELETE_EXTRAIMAGE
Command17=ID_POPUP_PROPERTIES
CommandCount=17

