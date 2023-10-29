mkdir package-win
cd package-win
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
make install

mkdir version
cd version
mkdir bin
mkdir assets
xcopy /s/e ..\Release\ bin
xcopy /s/e ..\..\assets\ assets
Compress-Archive -Path . -DestinationPath ../../release.zip
cd ../../