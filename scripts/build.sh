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
##    This script builds the game boy version of El Jamon Volador.            ##
##    As 29/05/23 it only can be built in macOS hosts, since the              ##
##    new version of the compiler on GNU doesn't produce a valid binary.      ##
##                                                                            ##
##---------------------------------------------------------------------------~##


readonly SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";

readonly LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
readonly GAME_ROOT_DIR="${ROOT_DIR}/game";
readonly ASSETS_DIR="${ROOT_DIR}/assets";

readonly GAME_NAME="cosmic-intruders";
readonly GAME_VERSION="2.1.0";

GAME_BUILD_TYPE="Release";
GAME_BUILD_TARGET="pc";
PACKAGE_BUILD="";
PLATFORM_NAME=$(uname)


function show_help() {
    echo "--release ) GAME_BUILD_TYPE=Release";
    echo "--debug   ) GAME_BUILD_TYPE=Debug";
    echo "--pc      ) GAME_BUILD_TARGET=pc";
    echo "--web     ) GAME_BUILD_TARGET=web";
    echo "--package ) PACKAGE_BUILD=true";
    exit 1;

}

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
                                                                                  \
        -I"${LIBS_ROOT_DIR}"                                                      \
        -I"${LIBS_ROOT_DIR}/Cooper"                                               \
        -I"${GAME_ROOT_DIR}"                                                      \
                                                                                  \
        -o "${BUILD_DIR}/game.html"                                               \
                                                                                  \
        -s USE_SDL=2                                                              \
        -s USE_SDL_MIXER=2                                                        \
        -s USE_SDL_TTF=2                                                          \
        -s USE_SDL_IMAGE=2                                                        \
        -s SDL2_IMAGE_FORMATS='["png"]'                                           \
                                                                                  \
         -lidbfs.js                                                               \
                                                                                  \
        --preload-file assets                                                     \
                                                                                  \
        -DGAME_VERSION="\"123\""                                                  \
    ;
}



test "${GAME_BUILD_TARGET}" == "pc"   && build_for_pc;
test "${GAME_BUILD_TARGET}" == "web"  && build_for_web;


##
## Package if needed...
##

if [ -n "$PACKAGE_BUILD" ]; then
    GAME_DIST_DIR="${DIST_DIR}/cosmic-intruders-${GAME_VERSION}-${PLATFORM_NAME}-${BUILD_TYPE}";
    GAME_ZIP_FILENAME="${DIST_DIR}/cosmic-intruders-${GAME_VERSION}-${PLATFORM_NAME}.zip";

    mkdir -p "${GAME_DIST_DIR}"                          \
        && cd  "${GAME_DIST_DIR}"                        \
        && cp     "${ROOT_DIR}/build/cosmic-intruders" . \
        && cp  -R "${ROOT_DIR}/assets"                 . \
        && zip -r "${GAME_ZIP_FILENAME}"               . \
    ;

    echo "Generated zip at: $GAME_ZIP_FILENAME";
fi;
