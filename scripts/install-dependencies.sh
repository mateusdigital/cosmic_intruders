#!/usr/bin/env bash
set -e;

##
## Emscripten
##

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";

pushd "${ROOT_DIR}";
    rm -rf emsdk;
    git clone https://github.com/emscripten-core/emsdk.git;

    pushd emsdk
        git pull;

        ./emsdk install  latest;
        ./emsdk activate latest;
        
        source "${ROOT_DIR}/emsdk/emsdk_env.sh";
    popd # emsdk
popd # "${ROOT_DIR}";


##
## SDL 2
##

sudo apt-get update   -y;
sudo apt-get install  -y \
    libsdl2-2.0-0        \
    libsdl2-doc          \
    libsdl2-gfx-dev      \
    libsdl2-image-2.0-0  \
    libsdl2-mixer-2.0-0  \
    libsdl2-net-2.0-0    \
    libsdl2-ttf-2.0-0    \
    libsdl2-dev          \
    libsdl2-gfx-1.0-0    \
    libsdl2-gfx-doc      \
    libsdl2-image-dev    \
    libsdl2-mixer-dev    \
    libsdl2-net-dev      \
    libsdl2-ttf-dev      \
    ;