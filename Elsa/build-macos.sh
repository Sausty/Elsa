set echo on

mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c" -o -name "*.m" -name "*.cpp")

Assembly="Elsa"
CompilerFlags="-g -shared -fdeclspec -fPIC -fno-objc-arc -fsanitize=address"
IncludeFlags="-Isrc"
LinkerFlags="-lobjc -framework AppKit -framework QuartzCore -framework GameController -framework CoreHaptics -framework Metal"
Defines="-D_DEBUG -DELSA_EXPORT"

echo "Building $Assembly..."
clang $cFilenames $CompilerFlags -o ../bin/lib$Assembly.so $Defines $IncludeFlags $LinkerFlags