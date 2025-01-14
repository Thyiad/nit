Nit
===

[![Travis-CI](https://travis-ci.org/rakhimov/nit.svg?branch=master)](https://travis-ci.org/rakhimov/nit)
[![Appveyor-CI](https://ci.appveyor.com/api/projects/status/y75jx0in3q4jx6c0?svg=true)](https://ci.appveyor.com/project/rakhimov/nit)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/15886/badge.svg)](https://scan.coverity.com/projects/rakhimov-nit)
[![codecov](https://codecov.io/gh/rakhimov/nit/branch/master/graph/badge.svg)](https://codecov.io/gh/rakhimov/nit)

Nit is a PokerStove fork aimed at rejuvenating the project.
The name "nit" is chosen because it is short (like "git")
and is a derogatory (like "git") poker term for hyper-tight-passive players
who only play premium starting hands.

PokerStove is a highly hand optimized C++ poker hand evaluation library.
The Win32 Hold'em GUI was first released in 2002,
and has been available as freeware since it's first release.

The core libraries of pokerstove are being open sourced.
The project is currently in the process of reviewing and publishing the code.
As code is reviewed and code sanitized further commits will be added.

## Libraries

### nit/eval

This is a c++ poker hand evaluation library.
The main design goals of the library are generality, extensibility, and ease of use.
There are evaluators for fourteen variants of poker.
Additionally, there are various card manipulation and query tools
built into the CardSet class.

## Programs

### nit-eval

A tool for poker hand evaluation.
It demonstrates how to use the nit/eval library,
and to create evaluators for the different variants of poker.

### nit-colex

A utility for viewing colexicographical index for sets of cards.

## Building

The nit comes with build scripts for cmake.
This should allow you to build it on any platform with minimal tweaking.

In order to build the libraries,
you'll need the following installed on your platform of choice:

* C++11 compliant compiler: gcc (>=4.8), clang (>=3.3), msvc (>=2015)
* boost, version 1.46 or higher
* cmake, version 3.1 or higher
* Python (optional), version 2.7+ or 3.3+

### Linux

To install the dependencies with apt get:

    apt-get install libboost-all-dev cmake

To build under linux using cmake,
create a build directory,
invoke cmake in the build directory, then build.

    git clone --recursive https://github.com/rakhimov/nit
    mkdir nit/build
    cd nit/build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

### macOS

To install the dependencies with [homebrew](http://brew.sh/):

    brew install cmake boost

The building instructions are the same as for [Linux](#linux)

### nit_release

基于node 14，在mac、win10 x64、centos stream上编译出来的产物
在node 16上用不了，用node 16也未编译成功，先不管了

### win

#### 生成解决方案

``` bash
# 安装依赖
npm install

# 生成 visual studio 解决方案，17 2022 是 visual studio 2022
cmake -G "Visual Studio 17 2022" -S . -B ./build
```

#### 修改代码

- 如果报nan.h找不到，在nit-addon -> 属性 -> VC++目录 -> 外部包含目录 里添加node_modules/nan
- 如果报node相关定义找不到，到 <https://nodejs.org/download/release/> headers文件下来，并且外部包含目录里添加对应的node header文件
- 如果报node.lib找不到,到 <https://nodejs.org/download/release/>下载node.lib下来
- 如果报 stage64\lib 找不到，就直接把名字里的x64删掉
