git submodule update --init --recursive
mkdir build-win
cd build-win
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
