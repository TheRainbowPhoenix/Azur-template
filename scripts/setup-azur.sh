#!/usr/bin/env bash
set -euo pipefail

if [ ! -d azur ]; then
  echo "Azur submodule is missing. Run: git submodule update --init --recursive"
  exit 1
fi

if [ ! -f azur/azur/CMakeLists.txt ] || [ ! -f azur/libnum/CMakeLists.txt ]; then
  echo "Azur submodule is not initialized correctly."
  echo "Run: git submodule update --init --recursive"
  exit 1
fi

cd azur
fxsdk build-cp install


echo "Azur submodule is ready."
