#!/bin/sh

# Set up emscripten

if [[ -z "${EMSDK}" ]]; then
  if [[ ! -e ./emsdk/emsdk ]]; then
    echo "Installing emscripten..."
    echo ""
    git submodule init
    git submodule update
    cd emsdk && git pull
    ./emsdk install latest && ./emsdk activate latest
    cd ..
  fi
  cd emsdk
  source ./emsdk_env.sh
  cd ..
fi

# This applies a patch to fastcomp to make sure that the
# environment is set correctly for react environments
patch -N --verbose emsdk/fastcomp/emscripten/src/shell.js emscripten.patch

mkdir -p jsbuild && cd jsbuild && rm -rf *
emconfigure cmake .. -DNO_AES=1 -DARCH=default -DBUILD_WASM=1 -DBUILD_JS=0
make
emconfigure cmake .. -DNO_AES=1 -DARCH=default -DBUILD_WASM=0 -DBUILD_JS=1
make
