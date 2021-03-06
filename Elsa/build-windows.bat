REM Build script for the Elsa engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the C/CPP files
SET Filenames=
FOR /R %%f in (*.c, *.cpp) do (
    SET Filenames=!Filenames! %%f
)

SET Assembly=Elsa
SET CompilerFlags=-g -MD -shared -Wvarargs -Wall -Werror -Wno-unused-variable -Wno-nullability-completeness -Wgnu-folding-constant -Wno-missing-braces -fdeclspec -Wno-switch 
SET IncludeFlags=-Isrc -IVendor -I%VULKAN_SDK%/Include
SET LinkerFlags=-luser32 -lole32 -lvulkan-1 -lshaderc_shared -lmsvcrtd -L%VULKAN_SDK%/Lib
SET Defines=-D_DEBUG -DELSA_EXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %Assembly%..."
clang %Filenames% %CompilerFlags% -o ../bin/%Assembly%.dll %Defines% %IncludeFlags% %LinkerFlags%