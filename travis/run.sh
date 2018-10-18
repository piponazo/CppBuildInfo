#!/bin/bash

set -e
set -x

source conan/bin/activate
mkdir build && cd build
conan install .. --build missing

cmake -DCMAKE_INSTALL_PREFIX=install -DCOMPILE_TESTS=ON ..
make -j2
bin/tests

