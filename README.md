
build hhmain (hh.ru task) - set -DBUILD_HHTEST=OFF
build my own test - set -DBUILD_HHTEST=ON

#### Build & Run
```
mkdir build 
cd build
cmake -DCMAKE_CXX_COMPILER=g++-13 -DBUILD_HHTEST=OFF -G "Unix Makefiles" .. 
cmake --build .  
./hhmain
```