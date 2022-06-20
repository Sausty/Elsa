REM Build script for Windows
@ECHO OFF

IF NOT EXIST bin (
    MKDIR bin
)

REM Elsa
PUSHD Elsa
CALL build-windows.bat 
POPD

REM App
PUSHD App
CALL build-windows.bat
POPD

ECHO "All assemblies built successfully."