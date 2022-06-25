set echo on

mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c")

Assembly="App"
CompilerFlags="-g -fdeclspec -fPIC -fno-objc-arc"
IncludeFlags="-I../Elsa/src -IVendor"
LinkerFlags="-L../bin/ -lElsa -Wl,-rpath,."
Defines="-D_DEBUG"

echo "Building $Assembly..."
clang $cFilenames $CompilerFlags -o ../bin/$Assembly $Defines $IncludeFlags $LinkerFlags