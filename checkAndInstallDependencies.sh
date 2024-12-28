#!/bin/bash

echo "Checking and installing dependencies"

CMAKE_VERSION="$(cmake --version | head -n 1 | cut -d ' ' -f 3)"
echo "Current CMake Version: " $CMAKE_VERSION
requiredVer="3.28.0"
 if [ "$(printf '%s\n' "$requiredVer" "$CMAKE_VERSION" | sort -V | head -n1)" = "$requiredVer" ]; then
        echo "Current CMake Version: " $CMAKE_VERSION
 else
        echo "Current CMake Version: " $CMAKE_VERSION
        echo "Version too low installing new version"
            sudo apt update
            sudo apt install -y cmake
 fi

 if command -v ninja &> /dev/null; then
    echo "Ninja is already installed."
 else
    echo "Installing Ninja..."
    sudo apt update
    sudo apt install -y ninja-build
 fi