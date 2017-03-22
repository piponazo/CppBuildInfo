#!/usr/bin/env bash

cd /tmp
wget https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz
tar xf cmake-3.7.2.tar.gz
cd cmake-3.7.2
./configure --parallel=4
make -j4
make install
cd ..
rm -rf cmake-*
