#!/bin/bash

# Make a gtest installation
mkdir /home/googletest
mkdir /home/googletest/googletest_build

cd /home/googletest
git clone https://github.com/google/googletest

cd googletest_build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/googletest ../googletest
make
make install

echo "Google Test (gtest) setup is complete."
