# Microsoft Developer Studio Project File - Name="XCC Audio Player" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC Audio Player - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Audio Player.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Audio Player.mak" CFG="XCC Audio Player - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Audio Player - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC Audio Player - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Audio Player - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\misc\libjpeg" /I "..\..\misc\zlib" /I "..\..\misc\libpng" /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib libjpeg.lib libpng.lib vfw32.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib /nologo /subsystem:windows /machine:I386 /out:"Release/XCC AV Player.exe" /libpath:"..\..\misc\library"

!ELSEIF  "$(CFG)" == "XCC Audio Player - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\misc\include" /I "..\..\misc" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dsound.lib libjpeg.lib libpng.lib vfw32.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/XCC AV Player.exe" /pdbtype:sept /libpath:"..\..\misc\library"

!ENDIF 

# Begin Target

# Name "XCC Audio Player - Win32 Release"
# Name "XCC Audio Player - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\misc\dd_window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\ETSLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\misc\timer.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_play.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\wav_header.cpp
# End Source File
# Begin Source File

SOURCE=".\XCC Audio Player.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Audio Player.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC Audio PlayerDlg.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dd.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dds.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dirs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_ds.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dsb.cpp
# End Source File
# Begin Source File

SOURCE=.\XCCAUDIOPLAYERINFODlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xfile32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xstring.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\misc\aud_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\dd_window.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_file.h
# End Source File
# Begin Source File

SOURCE=.\vqa_play.h
# End Source File
# Begin Source File

SOURCE=".\XCC Audio Player.h"
# End Source File
# Begin Source File

SOURCE=".\XCC Audio PlayerDlg.h"
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dsb.h
# End Source File
# Begin Source File

SOURCE=.\XCCAUDIOPLAYERINFODlg.h
# End Source File
# Begin Source File

SOURCE=..\misc\XCCSetDirectoriesDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\XCC Audio Player.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Audio Player.rc2"
# End Source File
# End Group
# End Target
# End Project
