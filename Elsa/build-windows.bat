REM Build script for the Elsa engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the C files
SET Filenames=
FOR /R %%f in (*.c) do (
    SET Filenames=!Filenames! %%f
)

SET Assembly=Elsa
SET CompilerFlags=-g -shared -Wvarargs -Wall -Werror 
SET IncludeFlags=-Isrc -Ivendor -I%VULKAN_SDK%/Include
SET LinkerFlags=-luser32 -lgdi32 -lkernel32 -lvulkan-1 -L%VULKAN_SDK%/Lib
SET Defines=-D_DEBUG -DELSA_EXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %Assembly%..."
clang %Filenames% %CompilerFlags% -o ../bin/%Assembly%.dll %Defines% %IncludeFlags% %LinkerFlags%