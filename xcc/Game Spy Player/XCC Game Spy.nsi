!define VERSION "1.10"

Name "XCC Game Spy ${VERSION}"
Outfile "XCC_Game_Spy.exe"
InstallDir "$PROGRAMFILES\XCC\Game Spy"
InstallDirRegKey HKLM "Software\XCC\Game Spy" "InstallDir"
XPStyle on
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"
	File "..\data\snow_colormap.bin"
	File "..\data\temperate_colormap.bin"
	File "..\data\urban_colormap.bin"
	File "..\game spy\release\xcc game spy.exe"
	File "..\game spy player\release\xcc game spy player.exe"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	CreateDirectory "$SMPROGRAMS\XCC"
	CreateShortCut "$SMPROGRAMS\XCC\Game Spy.lnk" "$INSTDIR\XCC Game Spy.exe"
	CreateShortCut "$SMPROGRAMS\XCC\Game Spy Player.lnk" "$INSTDIR\XCC Game Spy Player.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Game Spy" "DisplayName" "XCC Game Spy ${VERSION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Game Spy" "UninstallString" '"$INSTDIR\Uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Game Spy" "NoModify" 1
	WriteRegStr HKLM "Software\XCC\Game Spy" "InstallDir" "$INSTDIR"
SectionEnd

Section "Uninstall"
	SetShellVarContext all
	Delete "$SMPROGRAMS\XCC\Game Spy.lnk"
	Delete "$SMPROGRAMS\XCC\Game Spy Player.lnk"
	RmDir "$SMPROGRAMS\XCC"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Game Spy"
	DeleteRegKey HKLM "Software\XCC\Game Spy"
	DeleteRegKey /ifempty HKLM "Software\XCC"
	RMDir /r "$INSTDIR"
	RMDir "$PROGRAMFILES\XCC"
SectionEnd
