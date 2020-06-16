##~---------------------------------------------------------------------------##
##                        _      _                 _   _                      ##
##                    ___| |_ __| |_ __ ___   __ _| |_| |_                    ##
##                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   ##
##                   \__ \ || (_| | | | | | | (_| | |_| |_                    ##
##                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   ##
##                                                                            ##
##  File      : build.sh                                                      ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : stdmatt <stdmatt@pixelwizards.io>                             ##
##  Copyright : stdmatt - 2017 - 2019                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
SCRIPT_DIR="$(pw_get_script_dir)";
PLATFORM_NAME="web";
BUILD_DIR="${PROJECT_BUILD_DIR}/${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}";

LIBS_ROOT_DIR="${PROJECT_ROOT}/lib/Cooper";
GAME_ROOT_DIR="${PROJECT_ROOT}/game";
ASSETS_DIR="${PROJECT_ROOT}/assets";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
## Create build dir.
mkdir -p "$BUILD_DIR";

##
## Decide the flags that we gonna pass to em++
CXX_FLAGS="-O3 -DNDEBUG";
if [ "$PROJECT_BUILD_MODE" == "debug" ]; then
    CXX_FLAGS="-g -DCOOPER_DEBUG";
fi;

##
## Log
echo "Web Build";
echo "Building at: ${BUILD_DIR}";
mkdir -p "$BUILD_DIR";

##
## Run the em++.
em++ $CXX_FLAGS                                 \
    -O3                                         \
    -std=c++14                                  \
    -I"$LIBS_ROOT_DIR"                          \
    -I"$LIBS_ROOT_DIR"/Cooper                   \
    -I"$GAME_ROOT_DIR"                          \
    -lidbfs.js                                  \
    -DEMSCRIPTEN                                \
    -o "$BUILD_DIR"/CosmicIntruders.html        \
    $(find "$LIBS_ROOT_DIR" -iname "*.cpp")     \
    $(find "$GAME_ROOT_DIR" -iname "*.cpp")     \
    --embed-file "./assets"                     \
    -s WASM=0                                   \
    -s USE_SDL=2                                \
    -s USE_SDL_TTF=2                            \
    -s USE_SDL_IMAGE=2                          \
    -s SDL2_IMAGE_FORMATS='["png"]'             \
    -s LEGACY_GL_EMULATION=0                    \
    -s NO_EXIT_RUNTIME=1                        \

echo $(pw_FG "Done...");

##
## Copy the "assets" files to the build folder
cp -R $PROJECT_ROOT/release_files/web/* $BUILD_DIR;
