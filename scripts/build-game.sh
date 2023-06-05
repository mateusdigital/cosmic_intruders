#!/usr/bin/env bash
##~---------------------------------------------------------------------------##
##                               *       +                                    ##
##                         '                  |                               ##
##                     ()    .-.,="``"=.    - o -                             ##
##                           '=/_       \     |                               ##
##                        *   |  '=._    |                                    ##
##                             \     `=./`,        '                          ##
##                          .   '=.__.=' `='      *                           ##
##                 +                         +                                ##
##                      O      *        '       .                             ##
##                                                                            ##
##  File      : build-game.sh                                                 ##
##  Project   : cosmic_intruders                                              ##
##  Date      : 2017-11-17                                                    ##
##  License   : GPLv3                                                         ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2017 - 2023                                  ##
##                                                                            ##
##  Description :                                                             ##
##    This script builds the pc and web version of Cosmic Intruders.          ##
##    Look for ./install-dependencies.sh to check what's required to          ##
##    run the build.                                                          ##
##---------------------------------------------------------------------------~##

set -e ## break on errors...

##------------------------------------------------------------------------------
function show_help() {
    echo "--release ) GAME_BUILD_TYPE=Release";
    echo "--debug   ) GAME_BUILD_TYPE=Debug";
    echo "--pc      ) GAME_BUILD_TARGET=pc";
    echo "--web     ) GAME_BUILD_TARGET=web";
    echo "--package ) PACKAGE_BUILD=true";
    exit 1;

}

##------------------------------------------------------------------------------
readonly SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";

readonly LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
readonly GAME_ROOT_DIR="${ROOT_DIR}/game";
readonly ASSETS_DIR="${ROOT_DIR}/assets";

readonly GAME_NAME="cosmic-intruders";
readonly GAME_VERSION="2.1.0";

##------------------------------------------------------------------------------
GAME_BUILD_TYPE="Release";
GAME_BUILD_TARGET="pc";
PACKAGE_BUILD="";
PLATFORM_NAME=$(uname)

while true; do
    case "$1" in
        "--release" ) GAME_BUILD_TYPE="Release"; ;;
        "--debug"   ) GAME_BUILD_TYPE="Debug";   ;;
        "--pc"      ) GAME_BUILD_TARGET="pc";    ;;
        "--web"     ) GAME_BUILD_TARGET="web";   ;;
        "--package" ) PACKAGE_BUILD="true";      ;;
        *) show_help;                            ;;
    esac;
    shift;
    if [ $# -eq 0 ]; then
        break;
    fi;
done;

readonly BUILD_DIR="${ROOT_DIR}/build-${GAME_BUILD_TARGET}-${GAME_BUILD_TYPE}";
readonly DIST_DIR="${ROOT_DIR}/dist-${GAME_BUILD_TARGET}-${GAME_BUILD_TYPE}";


##
## Build the game.
##

##------------------------------------------------------------------------------
function build_for_pc()
{
    echo "Building game for pc";

    mkdir -p "${BUILD_DIR}";

    ## @todo(mateus): Add debug option...
    g++                                                                           \
        $(find ${ROOT_DIR} -type d -name "emsdk" -prune -o -iname "*.cpp" -print) \
        $(sdl2-config --cflags)                                                   \
        -std=c++14                                                                \
                                                                                  \
        -I"${LIBS_ROOT_DIR}"                                                      \
        -I"${LIBS_ROOT_DIR}/Cooper"                                               \
        -I"${GAME_ROOT_DIR}"                                                      \
                                                                                  \
        -o "${BUILD_DIR}/game"                                                    \
                                                                                  \
        -lSDL2                                                                    \
        -lSDL2_mixer                                                              \
        -lSDL2_ttf                                                                \
        -lSDL2_image                                                              \
                                                                                  \
        -DGAME_VERSION="\"${GAME_VERSION}\""                                      \
    ;
}

##------------------------------------------------------------------------------
function build_for_web()
{
    source "${ROOT_DIR}/emsdk/emsdk_env.sh";

    local target_platform="$1";
    echo "Building game for web";

    mkdir -p "${BUILD_DIR}";

    ## @todo(mateus): Add debug option...
    em++                                                                          \
        $(find ${ROOT_DIR} -type d -name "emsdk" -prune -o -iname "*.cpp" -print) \
        -std=c++14                                                                \
        -Oz                                                                       \
                                                                                  \
        -I"${LIBS_ROOT_DIR}"                                                      \
        -I"${LIBS_ROOT_DIR}/Cooper"                                               \
        -I"${GAME_ROOT_DIR}"                                                      \
                                                                                  \
        -o "${BUILD_DIR}/game.html"                                               \
                                                                                  \
        -DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0                                     \
                                                                                  \
        -s ENVIRONMENT='web'                                                      \
        -s INLINING_LIMIT=1                                                       \
                                                                                  \
        -s ASSERTIONS=0                                                           \
        -s STACK_OVERFLOW_CHECK=0                                                 \
        -s SAFE_HEAP=0                                                            \
        -s LZ4=1                                                                  \
        -s DISABLE_EXCEPTION_CATCHING=1                                           \
        -s AGGRESSIVE_VARIABLE_ELIMINATION=1                                      \
                                                                                  \
        -s USE_SDL=2                                                              \
        -s USE_SDL_TTF=2                                                          \
        -s USE_SDL_IMAGE=2                                                        \
        -s SDL2_IMAGE_FORMATS='["png"]'                                           \
                                                                                  \
                                                                                  \
        -fno-exceptions                                                           \
        -fno-rtti                                                                 \
                                                                                  \
         -lidbfs.js                                                               \
                                                                                  \
        --preload-file assets-web/@assets                                         \
                                                                                  \
        -DGAME_VERSION="\"${GAME_VERSION}\""                                      \
    ;

    ls -lh "${BUILD_DIR}";
}

##------------------------------------------------------------------------------
test "${GAME_BUILD_TARGET}" == "pc"  && build_for_pc;
test "${GAME_BUILD_TARGET}" == "web" && build_for_web;
