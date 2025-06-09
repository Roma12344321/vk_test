if not exist build (
    mkdir build
)

cd build

cmake ..

cd ..

cmake --build build

.\build\bin\vk_first.exe
