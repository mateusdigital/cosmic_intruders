#!/usr/bin/env bash


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
ROOT_DIR="$(dirname "$SCRIPT_DIR")";

BUILD_DIR="${ROOT_DIR}/build";
DIST_DIR="${ROOT_DIR}/dist";

BUILD_TYPE="Release";
PACKAGE_BUILD="";

GAME_VERSION=$(cat "${ROOT_DIR}/game/version" | tr -d "\"");
PLATFORM_NAME=$(uname)

if [ "$1" == "--debug" ]; then 
    BUILD_TYPE="Debug";
elif [ "$1" == "--package" ]; then
    PACKAGE_BUILD="true";
fi;

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

## cd "${ROOT_DIR}" || exit; ## Make things relatie to root is easier...
## mkdir -p "${BUILD_DIR}"                                  \
##     && cd "${BUILD_DIR}"                                 \
##     && cmake                                             \
##         -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"               \
##         -DGAME_VERSION="\"${GAME_VERSION}\""             \
##         ..                                               \
##     && cmake                                             \
##         --build .                                        \
##         --config "${BUILD_TYPE}"                         \
##     ;


##
## Package if needed...
##

if [ "$PACKAGE_BUILD" == "true" ]; then 
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