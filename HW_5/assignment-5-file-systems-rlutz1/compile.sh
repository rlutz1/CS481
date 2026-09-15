git submodule init
git submodule update --remote

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
