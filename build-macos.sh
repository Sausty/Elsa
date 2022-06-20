set echo on

echo "Building everything..."

cd Elsa
chmod +x build-macos.sh
./build-macos.sh
cd ../

cd App
chmod +x build-macos.sh
source build-macos.sh
cd ../

echo "All assemblies built succesfully."