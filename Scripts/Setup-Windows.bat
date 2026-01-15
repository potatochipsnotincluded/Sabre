@echo off

pushd ..
set "SABRE_INSTALL_LOC=%CD%"
setx SABRE_INSTALL_LOC "%SABRE_INSTALL_LOC%"
Vendor\Binaries\Premake\Windows\premake5.exe --file=Build.lua vs2022
popd
pause