mkdir build
cd build
../SDL2-2.0.10/configure
make prefix=$(pwd)/..
make prefix=$(pwd)/.. install
cd ..
rm -rf build