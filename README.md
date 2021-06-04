# hse_evolution_project

# Инструкция по установке:

Before installing gRPC you can choose a directory to hold locally installed packages. This page assumes that the environment variable MY_INSTALL_DIR holds this directory path. For example:
- `export MY_INSTALL_DIR=$HOME/.local`
- directory exists
- `mkdir -p $MY_INSTALL_DIR`
- add the local `bin` folder to your path variable 
- `export PATH="$MY_INSTALL_DIR/bin:$PATH"`

If you do not want to do it, grpc will install globally after what there is no easy way to uninstall gRPC

After installing you should build gRPC, Protocol Buffers and Aseil you should build it

`$ cd grpc`

`$ mkdir -p cmake/build`

`$ pushd cmake/build`

`$ cmake -DgRPC_INSTALL=ON \

    -DgRPC_BUILD_TESTS=OFF \

      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \

      ../..`
      
`$ make -j`
`$ make install`
`$ popd`
`$ mkdir -p third_party/abseil-cpp/cmake/build`
`$ pushd third_party/abseil-cpp/cmake/build`
`$ cmake -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE \
      ../..`
`$ make -j`
`$ make install`
`$ popd`



if you dont have Abseil, you should download it from here - `https://github.com/abseil/abseil-cpp`


- Ubuntu
    - `sudo apt install -y cmake`
    - installation gRPC
    - `sudo apt install -y build-essential autoconf libtool pkg-config`
    - `sudo apt update`
    - `git clone --recurse-submodules -b v1.38.0 https://github.com/grpc/grpc`
    - installation SFML
    - `sudo apt install libsfml-dev`
    - download project
    - `git clone --recurse-submodules https://github.com/Slava314/hse_evolution_project`
- Mac
    - `brew update`
    - installation gRPC
    - `brew install cmake`
    - `brew install autoconf automake libtool pkg-config`
    - `git clone --recurse-submodules -b v1.38.0 https://github.com/grpc/grpc`
    - installation SFML
    - `brew install sfml`
    - `git clone --recurse-submodules https://github.com/Slava314/hse_evolution_project`

