#!/usr/bin/env bash

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh

##----------------------------------------------------------------------------##
## Constants                                                                  ##
##----------------------------------------------------------------------------##
PROJECT_NAME="cosmic-intruders";


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
## Dirs
SCRIPT_DIR="$(pw_get_script_dir)";
PROJECT_ROOT=$(pw_abspath "$SCRIPT_DIR/..");
BUILD_DIR=$(pw_abspath "$PROJECT_ROOT/build");
DIST_DIR=$(pw_abspath "$PROJECT_ROOT/dist");

## Info
BUILD_MODE="debug";
BUILD_PLATFORM="desktop";
PROJECT_VERSION="$(bump-the-version                        \
    "${PROJECT_ROOT}/game/Game/include/Helpers/Version.h"  \
    "#define COW_COSMIC_INTRUDERS_VERSION"                 \
    "show")";
DIST_FILES="                   \
    ${BUILD_DIR}/$PROJECT_NAME \
    ${PROJECT_ROOT}/assets/    \
";


##----------------------------------------------------------------------------##
## Functions                                                                  ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
show_help()
{
    cat << END_TEXT
Usage:
    build.sh
      --help                          - Show this info.
      --clean                         - Cleans the build files.
      --mode     <*debug   | release> - Compile mode.
      --platform <*desktop | web>     - Target platform.
      --dist                          - Generate the release zip file.

    Options marked with * is assumed to be the default if none is given.
    [Web] builds requires that emscripten to be correctly set.
END_TEXT

    exit $1
}


##------------------------------------------------------------------------------
clean()
{
    pw_func_log "Cleaning files...";

    pw_func_log "   Build path: $(pw_FC $BUILD_DIR)";
    rm -rf "${BUILD_DIR}";

    pw_func_log "   Dist path: $(pw_FC $DIST_DIR)";
    rm -rf "${DIST_DIR}"
}

pw_string_in()
{
    local NEEDLE="${@:1:1}";
    local HAYSTACK="${@:2:10000}"; ## @magic(stdmatt): Remove the magic numbers.
    for ITEM in $HAYSTACK; do
        if [ "$NEEDLE" == "$ITEM" ]; then
            echo "$NEEDLE";
            return 0;
        fi;
    done;
    echo "";
    return 1;
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd "${PROJECT_ROOT}";

##
## Parse the command line arguments.
if [ -n "$(pw_getopt_exists "--clean" "$@")" ]; then
    clean;
    exit 0;
fi;

MODE=$(pw_getopt_arg "--mode" "$@");
test -n "$MODE" && BUILD_MODE="$MODE";
test -z "$(pw_string_in "$BUILD_MODE" "release" "debug")" \
    && pw_log_fatal "Invalid build mode: ($BUILD_MODE)";

PLATFORM=$(pw_getopt_arg "--platform" "$@");
test -n "$PLATFORM" && BUILD_PLATFORM="$PLATFORM";
test -z "$(pw_string_in "$BUILD_PLATFORM" "web" "desktop")" \
    && pw_log_fatal "Invalid build platform: ($BUILD_PLATFORM)";


##
## Build ;D
echo "Bulding (${PROJECT_NAME})";
echo "Build Script directory : $(pw_FC $SCRIPT_DIR     )";
echo "Build directory        : $(pw_FC $BUILD_DIR      )";
echo "Dist  directory        : $(pw_FC $DIST_DIR       )";
echo "Build mode             : $(pw_FC $BUILD_MODE     )";
echo "Build platform         : $(pw_FC $BUILD_PLATFORM )";
echo "Current version        : $(pw_FC $PROJECT_VERSION)";
echo "";

mkdir -p "$BUILD_DIR";

## Call the correct build script for each platform.
export PROJECT_ROOT="$PROJECT_ROOT";
export PROJECT_NAME="$PROJECT_NAME";
export PROJECT_BUILD_DIR="$BUILD_DIR";
export PROJECT_DIST_DIR="$DIST_DIR";
export PROJECT_BUILD_MODE="$BUILD_MODE";
export PROJECT_VERSION="$PROJECT_VERSION";


if [ "$BUILD_PLATFORM" == "desktop" ]; then
    "${SCRIPT_DIR}/platforms/build_desktop.sh";
else
    "${SCRIPT_DIR}/platforms/build_web.sh";
fi;

if [ $? != 0 ]; then
    pw_log_fatal "Failed to build - Will not create the dist files...";
fi;

##
## Create the distribution file.
if [ -n "$(pw_getopt_exists "--dist" "$@")" ]; then
    if [ "$BUILD_PLATFORM" == "desktop" ]; then
        "${SCRIPT_DIR}/platforms/dist_desktop.sh";
    else
        "${SCRIPT_DIR}/platforms/dist_web.sh";
    fi;
fi;
