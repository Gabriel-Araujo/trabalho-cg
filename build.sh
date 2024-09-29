#!/bin/bash

# se existir a pasta build, remove
if [ -d "build" ]; then
  rm -rf build
fi

mkdir build
cd build
cmake ..
make
./trabalho-cg
