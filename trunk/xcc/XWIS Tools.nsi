!define VERSION "0.0.0"

Name "XWIS Tools ${VERSION}"
Outfile "XWIS_Tools-${VERSION}.exe"
InstallDir "$PROGRAMFILES\XWIS\Tools"
InstallDirRegKey HKLM "Software\XWIS\Tools" "InstallDir"
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"
	File "data\snow_colormap.bin"
	File "data\temperate_colormap.bin"
	File "data\urban_colormap.bin"
	File "xcc game spy\release\xcc game spy.exe"
	File "xcc game spy player\release\xcc game spy player.exe"
	File "xcc wol irc server beeper\release\xcc wol irc server beeper.exe"
	File "xcc wol irc server client\release\xcc wol irc server client.exe"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	CreateDirectory "$SMPROGRAMS\XCC"
	CreateShortCut "$SMPROGRAMS\XCC\Game Spy.lnk" "$INSTDIR\XCC Game Spy.exe"
	CreateShortCut "$SMPROGRAMS\XCC\Game Spy Player.lnk" "$INSTDIR\XCC Game Spy Player.exe"
	CreateShortCut "$SMPROGRAMS\XCC\WOL IRC Server Beeper.lnk" "$INSTDIR\XCC WOL IRC Server Beeper.exe"
	CreateShortCut "$SMPROGRAMS\XCC\WOL IRC Server Client.lnk" "$INSTDIR\XCC WOL IRC Server Client.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XWIS Tools" "DisplayName" "XWIS Tools ${VERSION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XWIS Tools" "UninstallString" '"$INSTDIR\Uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XWIS Tools" "NoModify" 1
	WriteRegStr HKLM "Software\XWIS\Tools" "InstallDir" "$INSTDIR"
SectionEnd

Section "Uninstall"
	SetShellVarContext all
	Delete "$SMPROGRAMS\XCC\Game Spy.lnk"
	Delete "$SMPROGRAMS\XCC\Game Spy Player.lnk"
	Delete "$SMPROGRAMS\XCC\WOL IRC Server Beeper.lnk"
	Delete "$SMPROGRAMS\XCC\WOL IRC Server Client.lnk"
	RmDir "$SMPROGRAMS\XCC"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XWIS Tools"
	DeleteRegKey HKLM "Software\XWIS\Tools"
	DeleteRegKey /ifempty HKLM "Software\XWIS"
	RMDir /r "$INSTDIR"
	RMDir "$PROGRAMFILES\XWIS"
SectionEnd
