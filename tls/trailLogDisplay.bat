:: Helper script to trail the LogDisplay output file
PowerShell -NoExit -Command "Get-Content ..\bld\display.txt -Tail 1 -wait"