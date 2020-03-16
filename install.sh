mkdir build
cd build
../SDL2-2.0.10/autogen.sh
../SDL2-2.0.10/configure --prefix=$(pwd)/..
make prefix=$(pwd)/.. uninstall clean
make prefix=$(pwd)/..
make prefix=$(pwd)/.. install
cd ..
rm -rf build
rm -rf share
rm -f bin/sdl2-config