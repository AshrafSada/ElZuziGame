# Goto built-in automatic variable in PowerShell, where the currently running script is located
Set-Location -Path $PSScriptRoot

# set include and libraries path
$includePath = ".\deps\include"
$libPath = ".\deps\lib"

# set libraries to link
$libs = "SDL3.lib"

# compile C command
CL /Zi /I"$includePath" /Fo:.\build\main.obj /Fd:.\build\mygame.pdb /Fe:.\build\mygame.exe .\src\main.c /link /DEBUG /LIBPATH:"$libPath" $libs

