#!/usr/bin/env bash
set -euo pipefail

if [ ! -d azur ]; then
  echo "Azur submodule is missing. Run: git submodule update --init --recursive"
  exit 1
fi

if [ ! -f azur/3rdparty/CMakeLists.txt ]; then
  echo "Azur submodule is not initialized correctly."
  echo "Run: git submodule update --init --recursive"
  exit 1
fi

if [ -n "${FXSDK_CMAKE_MODULE_PATH:-}" ] && [ -f "$FXSDK_CMAKE_MODULE_PATH/FindAzur3rdParty.cmake" ]; then
  echo "Azur third-party CMake files are already installed."
  exit 0
fi

echo "Installing Azur third-party files for the fxSDK toolchain..."
fxsdk build-cp -c -B build-azur-3rdparty -S azur/3rdparty
make -C build-azur-3rdparty install -j"$(nproc)"

