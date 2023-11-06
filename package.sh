mkdir package-linux
cd package-linux
cmake ..
make
sudo make install

mkdir version
cd version
mkdir bin
mkdir assets
cp -r ../Release/* bin
cp -r ../../assets/* assets
tar -czvf ../../release.tar.gz .
cd ../../
