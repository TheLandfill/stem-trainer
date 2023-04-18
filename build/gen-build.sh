#!/usr/bin/env bash

cd build
mkdir -p Debug Release
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../
cd ../Release
cmake -DCMAKE_BUILD_TYPE=Release ../../
cd ../../
ln -s build/Release Release
ln -s build/Debug Debug
