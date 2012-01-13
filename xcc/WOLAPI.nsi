!define VERSION "0.0.0"

Name "WOLAPI ${VERSION}"
Outfile "WOLAPI-${VERSION}.exe"
InstallDir "$PROGRAMFILES\Red Alert 2"
InstallDirRegKey HKLM "Software\Westwood\Red Alert 2" "InstallPath"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "nl.cfg"
	File "wolapi.dll"
	File "wolapi.war"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
SectionEnd
