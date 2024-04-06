<div align="Center">

# Raylib Game Template

</div>

## Overview:
This is the general-purpose raylib project template in C++

## Prerequesites:
- **[Git;](https://git-scm.com/)**
- **[CMake;](https://cmake.org/)**
- **[Build system of your choosing;](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id7)**

## Setup
### 1. Build For Desktop:
- Pull all the necessary submodules:
```bash
git submodule update --init
```
- Create a binary diretory:
```bash
mkdir bin
cd bin
```
- Use the following command:
```cmake
cmake ..
```
### 2. Build For WEB:
- Pull all the necessary submodules:
```bash
git submodule update --init
```
- Go to the emscripten submodule:
```bash
cd lib/emsdk
```
- Install and activate the emsdk following the **[Installation Instruction](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended)**:
```bash
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ../..
```
- Create a binary diretory:
```bash
mkdir bin
cd bin
```
- Use the following commands:
```bash
emcmake cmake .. -DPLATFORM=Web
emmake make
```
- To test your final executable (*.html, *.json, *.wasm, *.data, *.mem) you can use the following command:
```bash
emrun ./{game_title}.html
```

## Licence
This template is originally under the **[MIT Licence](https://github.com/itsYakub/RaylibGameTemplate/blob/main/LICENCE)**, but you can modify it to suite your needs. You can use **[licenses/license-templates](https://github.com/licenses/license-templates)** to get the free licence template.