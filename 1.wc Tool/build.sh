#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Check if the build directory exists
if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"  # Remove the build directory and its contents
fi

# Create a new build directory
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit  # Exit if the cd command fails

# Run CMake and build the project
cmake ..
make
