Name "XWIS Client"
Outfile "XWIS-Client.exe"
InstallDir "$PROGRAMFILES\XCC"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "Release\XWIS Client.exe"
	CreateShortCut "$SMPROGRAMS\XWIS Client.lnk" "$INSTDIR\XWIS Client.exe"
SectionEnd
