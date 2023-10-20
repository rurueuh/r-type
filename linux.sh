git submodule update --init --recursive
mkdir build-linux
cd build-linux
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
