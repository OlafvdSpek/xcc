# Microsoft Developer Studio Project File - Name="XCC Map Decoder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC Map Decoder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Map Decoder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Map Decoder.mak" CFG="XCC Map Decoder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Map Decoder - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC Map Decoder - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Map Decoder - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "NO_FT_SUPPORT" /D "NO_INI_SUPPORT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libpng.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\misc\library"

!ELSEIF  "$(CFG)" == "XCC Map Decoder - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "NO_FT_SUPPORT" /D "NO_INI_SUPPORT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libpng.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\misc\library"

!ENDIF 

# Begin Target

# Name "XCC Map Decoder - Win32 Release"
# Name "XCC Map Decoder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\misc\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\crc.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\csf_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\file32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\fname.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_encoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\lzo\minilzo\minilzo.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_decode.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\misc\string_conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_binary.cpp
# End Source File
# Begin Source File

SOURCE=".\XCC Map Decoder.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Map Decoder.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC Map DecoderDlg.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dirs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_lmd_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_key.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_value.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\XSTE.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\misc\map_ts_encoder.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\XCC Map Decoder.h"
# End Source File
# Begin Source File

SOURCE=".\XCC Map DecoderDlg.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\palet.bin
# End Source File
# Begin Source File

SOURCE=".\res\XCC Map Decoder.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Map Decoder.rc2"
# End Source File
# End Group
# End Target
# End Project
