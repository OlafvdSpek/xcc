# Microsoft Developer Studio Project File - Name="XCC Library" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=XCC Library - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Library.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Library.mak" CFG="XCC Library - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Library - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XCC Library - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Library - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "JPEG_SUPPORT" /D "OGG_SUPPORT" /D "PNG_SUPPORT" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "XCC Library - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "JPEG_SUPPORT" /D "OGG_SUPPORT" /D "PNG_SUPPORT" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x413 /d "_DEBUG"
# ADD RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "XCC Library - Win32 Release"
# Name "XCC Library - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\misc\art_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\aud_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\aud_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\aud_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\audio_idx_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\avi_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\big_edit.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\big_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\big_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\bink_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\cc_structures.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\cps_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\crc.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\csf_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\ddpf_conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\dds_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\extract_object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\file32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\fname.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\fs_ini_file.cpp
# End Source File
# Begin Source File

SOURCE="..\..\xhp\cgi-bin\misc\html.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\hva_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\id_log.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_encode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\image_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\image_tools.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\jpeg_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_ra_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_td_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_encoder.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\lzo\minilzo\minilzo.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_cache.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_edit.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_edit.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_sfl.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mp3_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mp3_frame_header.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\multi_line.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\neat_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\neat_key_list.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ogg_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pak_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pal_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\palet.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pkt_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\png_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\wol\ra2_names.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\riff_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\rules_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_dune2_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_images.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_ts_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_ts_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\sound_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\st_file.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\misc\stream_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\stream_writer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\string_conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\tga_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\theme_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\timer.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_ra.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_ts_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\video_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_audio.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_binary.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\virtual_tfile.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\voc_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\vxl_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\w3d_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\wav_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\wav_header.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\win_handle.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\wsa_dune2_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\wsa_file.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_apps.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dirs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_draw.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_lmd_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_log.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_mixs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_key.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_key_r.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_key_r.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\xif_value.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xse.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\XSTE.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\misc\art_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\aud_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\aud_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\aud_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\audio_idx_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\avi_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\big_edit.h
# End Source File
# Begin Source File

SOURCE=..\misc\big_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\bin_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\bink_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\blowfish.h
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file_sh.h
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file_small.h
# End Source File
# Begin Source File

SOURCE=..\misc\cc_structures.h
# End Source File
# Begin Source File

SOURCE=..\misc\cps_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\crc.h
# End Source File
# Begin Source File

SOURCE=..\misc\csf_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\dd_window.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\ddpf_conversion.h
# End Source File
# Begin Source File

SOURCE=..\misc\dds_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\ETSLayout.h
# End Source File
# Begin Source File

SOURCE=..\misc\extract_object.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\file32.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\fname.h
# End Source File
# Begin Source File

SOURCE=..\misc\fnt_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\fs_ini_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\hva_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\id_log.h
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_encode.h
# End Source File
# Begin Source File

SOURCE=..\misc\image_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\image_tools.h
# End Source File
# Begin Source File

SOURCE=..\misc\ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\jpeg_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\log_window.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ra_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_td_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_encoder.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\lzo\minilzo\minilzo.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_cache.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_edit.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_edit.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_sfl.h
# End Source File
# Begin Source File

SOURCE=..\misc\mp3_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\mp3_frame_header.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\multi_line.h
# End Source File
# Begin Source File

SOURCE=..\misc\neat_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\neat_key_list.h
# End Source File
# Begin Source File

SOURCE=..\misc\null_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\ogg_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\pak_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\pal_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\palet.h
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\pkt_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\png_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\wol\ra2_names.h
# End Source File
# Begin Source File

SOURCE=..\misc\riff_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\riff_structures.h
# End Source File
# Begin Source File

SOURCE=..\misc\rules_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_dune2_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_images.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_ra_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_ts_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\shp_ts_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\sound_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\st_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\stream_reader.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\stream_writer.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\string_conversion.h
# End Source File
# Begin Source File

SOURCE=..\misc\text_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\tga_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\theme_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\timer.h
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_ra_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_structures.h
# End Source File
# Begin Source File

SOURCE=..\misc\tmp_ts_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\vartypes.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_audio.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_binary.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_image.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\virtual_tfile.h
# End Source File
# Begin Source File

SOURCE=..\misc\voc_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqa_play.h
# End Source File
# Begin Source File

SOURCE=..\misc\vqp_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\vxl_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\w3d_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\wav_file.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\wav_header.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\wav_structures.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\win_handle.h
# End Source File
# Begin Source File

SOURCE=..\misc\wsa_dune2_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\wsa_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_apps.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_cell.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_cell_manager.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dd.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dds.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dirs.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_draw.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_ds.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dsb.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_file_sh.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_infantry.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_level.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_lmd_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_lmd_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_log.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_mixs.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_overlays.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_registry.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_structures.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_templates.h
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_units.h
# End Source File
# Begin Source File

SOURCE=..\misc\XCCSetDirectoriesDlg.h
# End Source File
# Begin Source File

SOURCE=..\misc\xif_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\XSTE.h
# End Source File
# End Group
# End Target
# End Project
