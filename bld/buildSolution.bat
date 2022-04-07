:: Helper script to (re)build the VS2022 solution
PowerShell -NoExit -Command "..\vendors\bin\Premake\premake5.exe vs2022; if($?){Exit}"