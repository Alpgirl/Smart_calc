#!/bin/bash

# Update the package list
sudo apt-get update

# Install the libgtest-dev package
sudo apt-get install libgtest-dev -y

# Navigate to the gtest source directory
cd /usr/src/googletest/googletest

# Create a build directory and navigate to it
sudo mkdir build
cd build

# Run CMake to configure the build
sudo cmake ..

# Build the Google Test library
sudo make

# Copy the generated library files to /usr/lib/
sudo cp libgtest* /usr/lib/

# Return to the parent directory
cd ..

# Remove the build directory
sudo rm -rf build

# Create the /usr/local/lib/googletest directory
sudo mkdir /usr/local/lib/googletest

# Create symbolic links for libgtest.a and libgtest_main.a in /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

# Print a message to indicate that the setup is complete
echo "Google Test (gtest) setup is complete."
