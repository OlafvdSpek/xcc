# Microsoft Developer Studio Project File - Name="XCC Universal Container Reader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC Universal Container Reader - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Universal Container Reader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Universal Container Reader.mak" CFG="XCC Universal Container Reader - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Universal Container Reader - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC Universal Container Reader - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Universal Container Reader - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 bzip_static.lib z_static.lib /nologo /subsystem:windows /map /machine:I386

!ELSEIF  "$(CFG)" == "XCC Universal Container Reader - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 bzip_static.lib z_static.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XCC Universal Container Reader - Win32 Release"
# Name "XCC Universal Container Reader - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\directories_dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\ETSLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\format_edit_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\formats_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\library_dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ucr_container_simple.cpp
# End Source File
# Begin Source File

SOURCE=.\ucr_container_ws_ra_mix.cpp
# End Source File
# Begin Source File

SOURCE=.\ucr_format.cpp
# End Source File
# Begin Source File

SOURCE=.\ucr_formats.cpp
# End Source File
# Begin Source File

SOURCE=.\ucr_library.cpp
# End Source File
# Begin Source File

SOURCE=.\ucr_object.cpp
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container Reader.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container Reader.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container ReaderDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container ReaderView.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\directories_dlg.h
# End Source File
# Begin Source File

SOURCE=.\format_edit_dlg.h
# End Source File
# Begin Source File

SOURCE=.\formats_dlg.h
# End Source File
# Begin Source File

SOURCE=.\library_dlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ucr_container.h
# End Source File
# Begin Source File

SOURCE=.\ucr_container_simple.h
# End Source File
# Begin Source File

SOURCE=.\ucr_container_ws_ra_mix.h
# End Source File
# Begin Source File

SOURCE=.\ucr_format.h
# End Source File
# Begin Source File

SOURCE=.\ucr_formats.h
# End Source File
# Begin Source File

SOURCE=.\ucr_library.h
# End Source File
# Begin Source File

SOURCE=.\ucr_object.h
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container Reader.h"
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container ReaderDoc.h"
# End Source File
# Begin Source File

SOURCE=".\XCC Universal Container ReaderView.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\XCC Universal Container Reader.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Universal Container Reader.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Universal Container ReaderDoc.ico"
# End Source File
# End Group
# End Target
# End Project
# Section XCC Universal Container Reader : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDR_POPUP_VIEW:102
# End Section
