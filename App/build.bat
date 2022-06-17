REM Build script for the App
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the C files
SET Filenames=
FOR /R %%f in (*.c) do (
    SET Filenames=!Filenames! %%f
)

SET Assembly=App
SET CompilerFlags=-g 
SET IncludeFlags=-Isrc -I../Elsa/src
SET LinkerFlags=-luser32 -lgdi32 -lkernel32 -L../bin/ -lElsa.lib
SET Defines=-D_DEBUG 

ECHO "Building %Assembly%..."
clang %Filenames% %CompilerFlags% -o ../bin/%Assembly%.exe %Defines% %IncludeFlags% %LinkerFlags%