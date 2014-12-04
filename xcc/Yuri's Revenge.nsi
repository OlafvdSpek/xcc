Name "Yuri's Revenge"
Outfile "Yuri's-Revenge-Multiplayer.exe"
InstallDir "$PROGRAMFILES\Red Alert 2"
InstallDirRegKey HKLM "Software\Westwood\Red Alert 2" "InstallPath"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "expandmd01.mix"
	File "langmd.mix"
	File "mapsmd03.mix"
	File "movmd03.mix"
	File "mphmd.exe"
	File "multimd.mix"
	File "ra2md.mix"
	File "xyr.dll"
	File "yuri's revenge.exe"
	CreateShortCut "$SMPROGRAMS\Yuri's Revenge.lnk" "$INSTDIR\Yuri's Revenge.exe"
	WriteRegStr HKLM "Software\Westwood\Yuri's Revenge" "InstallPath" "$INSTDIR\Yuri's Revenge.exe"
	Exec "$INSTDIR\Yuri's Revenge.exe"
SectionEnd
