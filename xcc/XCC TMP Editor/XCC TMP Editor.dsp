# Microsoft Developer Studio Project File - Name="XCC TMP Editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC TMP Editor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC TMP Editor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC TMP Editor.mak" CFG="XCC TMP Editor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC TMP Editor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC TMP Editor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC TMP Editor - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libjpeg.lib libpng.lib vfw32.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\misc\library"

!ELSEIF  "$(CFG)" == "XCC TMP Editor - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libjpeg.lib libpng.lib vfw32.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\misc\library"

!ENDIF 

# Begin Target

# Name "XCC TMP Editor - Win32 Release"
# Name "XCC TMP Editor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\properties_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP Editor.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP Editor.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP EditorDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP EditorView.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\properties_dlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_binary.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_image.h
# End Source File
# Begin Source File

SOURCE=".\XCC TMP Editor.h"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP EditorDoc.h"
# End Source File
# Begin Source File

SOURCE=".\XCC TMP EditorView.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\XCC TMP Editor.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC TMP Editor.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\XCC TMP EditorDoc.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=".\XCC TMP Editor.reg"
# End Source File
# End Target
# End Project
# Section XCC TMP Editor : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:22:CG_IDR_POPUP_LEFT_VIEW:102
# End Section
