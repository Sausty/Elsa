set echo on

mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c" -o -name "*.m")

Assembly="Elsa"
CompilerFlags="-g -shared -fdeclspec -fPIC -fno-objc-arc"
IncludeFlags="-Isrc -IVendor"
LinkerFlags="-lobjc -framework AppKit -framework QuartzCore -framework GameController -framework CoreHaptics"
Defines="-D_DEBUG -DELSA_EXPORT"

echo "Building $Assembly..."
clang $cFilenames $CompilerFlags -o ../bin/lib$Assembly.so $Defines $IncludeFlags $LinkerFlags