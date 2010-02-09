!define VERSION "0.0.3"

Name "XWIS Client ${VERSION}"
Outfile "XWIS_Client-${VERSION}.exe"
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
