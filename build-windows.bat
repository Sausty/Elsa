REM Build script for Windows
@ECHO OFF

IF NOT EXIST bin (
    MKDIR bin
)

REM Elsa
PUSHD Elsa
CALL build.bat 
POPD

REM App
PUSHD App
CALL build.bat
POPD

ECHO "All assemblies built successfully."