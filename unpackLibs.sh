echo Start Unpacking...
tar -xf SDL2-2.0.3.tar.gz 
echo Archive unpacked...

echo Create Directiories...
mkdir libs_linux
mkdir libs_linux/include
mkdir libs_linux/lib
mkdir SISE2015/MakeFileBuild
echp Finished Creating Directories...

echo Compile SDL...
cd SDL2-2.0.3
./configure -q
make
make install
cd ..
echo Finished Compiling SDL...

echo Copy include and library files...
cp SDL2-2.0.3/include/* libs_linux/include/
cp /usr/local/lib/libSDL2* libs_linux/lib/
echo Finished copying files...

