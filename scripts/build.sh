#!/usr/bin/env bash


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
ROOT_DIR="$(dirname "$SCRIPT_DIR")";

BUILD_DIR="${ROOT_DIR}/build";
DIST_DIR="${ROOT_DIR}/dist";

LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
GAME_ROOT_DIR="${ROOT_DIR}/game";
ASSETS_DIR="${ROOT_DIR}/assets";

BUILD_TYPE="Release";
BUILD_PC="";
BUILD_WEB="";
PACKAGE_BUILD="";

GAME_VERSION=$(cat "${ROOT_DIR}/game/version" | tr -d "\"");
PLATFORM_NAME=$(uname)


while true; do
    case "$1" in
        "--release" ) BUILD_TYPE="Release"; ;;
        "--debug"   ) BUILD_TYPE="Debug";   ;;
        "--pc"      ) BUILD_PC="true";      ;;
        "--web"     ) BUILD_WEB="true";     ;;
        "--package" ) PACKAGE_BUILD="true"; ;;
        *) show_help;                       ;;
    esac;
    shift;
    if [ $# -eq 0 ]; then 
        break;
    fi;
done;

## 
## Run Info
##

echo "SCRIPT_DIR    : $SCRIPT_DIR";
echo "ROOT_DIR      : $ROOT_DIR";
echo "BUILD_DIR     : $BUILD_DIR";
echo "DIST_DIR      : $DIST_DIR";
echo "BUILD_TYPE    : $BUILD_TYPE";
echo "PACKAGE_BUILD : $PACKAGE_BUILD";

##
## Build the game.
##

if [ -n "${BUILD_PC}" ]; then 
    cd "${ROOT_DIR}" || exit; ## Make things relatie to root is easier...
    mkdir -p "${BUILD_DIR}"                                  \
        && cd "${BUILD_DIR}"                                 \
        && cmake                                             \
            -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"               \
            -DGAME_VERSION="\"${GAME_VERSION}\""             \
            ..                                               \
        && cmake                                             \
            --build .                                        \
            --config "${BUILD_TYPE}"                         \
        ;
fi;


##
## Build for web.
##

if [ -n "${BUILD_WEB}" ]; then 
    ## Decide the flags that we gonna pass to em++
    CXX_FLAGS="-O3 -DNDEBUG";
    if [ "${BUILD_TYPE}" == "Debug" ]; then
        CXX_FLAGS="-g -DCOOPER_DEBUG";
    fi;

    SOURCES="$(find "$LIBS_ROOT_DIR" -iname "*.cpp") ";
    SOURCES+="$(find "$GAME_ROOT_DIR" -iname "*.cpp")"
    SOURCES="$(echo "$SOURCES" | tr [:space:] " ")";

    cd "${ROOT_DIR}"                                    \
        && em++                                         \
            ${CXX_FLAGS}                                \
            -O3                                         \
            -std=c++14                                  \
            -I"${LIBS_ROOT_DIR}"                        \
            -I"${LIBS_ROOT_DIR}/Cooper"                 \
            -I"${GAME_ROOT_DIR}"                        \
            -lidbfs.js                                  \
            -DEMSCRIPTEN                                \
            -o "${BUILD_DIR}/CosmicIntruders.html"      \
            "${SOURCES}"                                \
            --embed-file "./assets"                     \
            -s WASM=0                                   \
            -s USE_SDL=2                                \
            -s USE_SDL_TTF=2                            \
            -s USE_SDL_IMAGE=2                          \
            -s SDL2_IMAGE_FORMATS='["png"]'             \
            -s LEGACY_GL_EMULATION=0                    \
            -s NO_EXIT_RUNTIME=1                        \
        ;
fi;

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