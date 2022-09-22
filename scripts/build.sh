#!/usr/bin/env bash


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
ROOT_DIR="$(dirname "$SCRIPT_DIR")";

BUILD_DIR="${ROOT_DIR}/build";
DIST_DIR="${ROOT_DIR}/dist";

LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
GAME_ROOT_DIR="${ROOT_DIR}/game";
ASSETS_DIR="${ROOT_DIR}/assets";

PACKAGE_BUILD="";

GAME_NAME="cosmic-intruders";
GAME_VERSION=$(cat "${ROOT_DIR}/game/version" | tr -d "\""); ## without any quotes...
GAME_BUILD_TYPE="Release";
GAME_BUILD_TARGET="pc";
GAME_EMSCRIPTEN_TOOLCHAIN="${HOME}/.emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake";

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


##
## Build the game.
##

function build_game()
{
    local target_platform="$1";
    echo "Building game for platform: ${target_platform}";

    mkdir -p "${BUILD_DIR}"                                            \
        && cd "${BUILD_DIR}"                                           \
        && cmake                                                       \
            -DGAME_NAME="${GAME_NAME}"                                 \
            -DGAME_VERSION="\"${GAME_VERSION}\""                       \
            -DGAME_TARGET_PLATFORM="${target_platform}"                \
            -DCMAKE_BUILD_TYPE="${GAME_BUILD_TYPE}"                    \
            -DGAME_EMSCRIPTEN_TOOLCHAIN="${GAME_EMSCRIPTEN_TOOLCHAIN}" \
            ..                                                         \
        && cmake                                                       \
            --build .                                                  \
            --config "${BUILD_TYPE}"                                   \
        ;
}
export CMAKE_TOOLCHAIN_FILE="$HOME/.emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake";

test "${GAME_BUILD_TARGET}" == "pc"   && build_game "pc";
test "${GAME_BUILD_TARGET}" == "web"  && build_game "web";


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
