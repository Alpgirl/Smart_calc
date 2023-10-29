#!/bin/bash


# Make a dir for gtest installation
mkdir /home/googletest
mkdir /home/googletest/googletest_build

cd /home/googletest
git clone https://github.com/google/googletest

sudo apt-get install check

cd googletest_build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/googletest ../googletest
make
make install

# Install the libgtest-dev package
#apt-get install libgtest-dev -y
#
#sudo apt-get install check
#
## Navigate to the gtest source directory
#cd /usr/src/googletest/googletest
#
## Create a build directory and navigate to it
#mkdir build
#cd build
#
## Run CMake to configure the build
#cmake ..
#
## Build the Google Test library
#make
#
## Copy the generated library files to /usr/lib/
#cp libgtest* /usr/lib/
#
## Return to the parent directory
#cd ..
#
## Remove the build directory
#rm -rf build
#
## Create the /usr/local/lib/googletest directory
#mkdir /usr/local/lib/googletest
#
## Create symbolic links for libgtest.a and libgtest_main.a in /usr/local/lib/googletest
#ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
#ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
#
## Print a message to indicate that the setup is complete
echo "Google Test (gtest) setup is complete."
