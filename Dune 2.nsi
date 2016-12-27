Name "Dune 2"
Outfile "Dune-2.exe"
InstallDir "$PROGRAMFILES\Dune 2"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "atre.pak"
	File "credits.eng"
	File "dune.cfg"
	File "dune.pak"
	File "dune2.exe"
	File "english.pak"
	File "finale.pak"
	File "hark.pak"
	File "herc.pak"
	File "intro.pak"
	File "introvoc.pak"
	File "mentat.pak"
	File "merc.pak"
	File "onetime.dat"
	File "opendune.exe"
	File "options.cfg"
	File "ordos.pak"
	File "scenario.pak"
	File "setup.exe"
	File "setupeng.dip"
	File "sound.pak"
	File "voc.pak"
	File "xtre.pak"
	CreateShortCut "$SMPROGRAMS\Dune 2.lnk" "$INSTDIR\OpenDune.exe"
	WriteRegStr HKLM "Software\Westwood\Dune 2" "InstallPath" "$INSTDIR\OpenDune.exe"
SectionEnd
