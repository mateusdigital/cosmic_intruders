##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : build.sh                                                      ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2017                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## "Constants"                                                                ##
##----------------------------------------------------------------------------##
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";

##------------------------------------------------------------------------------
## Build directories.
BUILD_DIR="$(realpath $SCRIPT_DIR/../build)";
BUILD_DESKTOP_DIR="$BUILD_DIR/desktop";
BUILD_WEB_DIR="$BUILD_DIR/web";

##------------------------------------------------------------------------------
## Packaging directories.
PKG_DIR="$(realpath $SCRIPT_DIR/../package)";
PKG_DESKTOP_DIR="$PKG_DIR/desktop";
PKG_WEB_DIR="$PKG_DIR/web";

##------------------------------------------------------------------------------
## Source files.
GAME_ROOT_DIR="$(realpath $SCRIPT_DIR/../game)";
LIBS_ROOT_DIR="$(realpath $SCRIPT_DIR/../lib)";

##------------------------------------------------------------------------------
## Assets / Resources.
ASSETS_DIR="$(realpath $SCRIPT_DIR/../assets)";
RESOURCES_DIR="$(realpath $SCRIPT_DIR/../resources)";


##----------------------------------------------------------------------------##
## Variables                                                                  ##
##----------------------------------------------------------------------------##
MODE="debug";
TARGET="gnu_linux";


##----------------------------------------------------------------------------##
## Desktop                                                                    ##
##----------------------------------------------------------------------------##
build_desktop()
{
    ##--------------------------------------------------------------------------
    ## Local vars.
    local MODE="$1";
    local TARGET="$2";
    local TARGET_BUILD_DIR="$BUILD_DESKTOP_DIR/$TARGET";

    ##--------------------------------------------------------------------------
    ## Create build dir.
    echo "--> Creating build directory...";
    echo "    $TARGET_BUILD_DIR";

    mkdir -p "$TARGET_BUILD_DIR";

    ##--------------------------------------------------------------------------
    ## Run CMAKE and make(3).
    echo "--> Building Cosmic Intruders...";
    echo "    Mode: $MODE | Target: $TARGET";

    cd "$TARGET_BUILD_DIR";      ## Change the cwd for cmake.
        cmake ../../../ && make; ## Run the cmake.
    cd - 2> /dev/null            ## Restore the cwd.

    ##--------------------------------------------------------------------------
    ## Done ;D
    echo "--> Done...";
}

package_desktop()
{
    ##--------------------------------------------------------------------------
    ## Local vars.
    local MODE="$1";
    local TARGET="$2";
    local TARGET_PKG_DIR="$PKG_DESKTOP_DIR/$TARGET";
    local TARGET_BUILD_DIR="$BUILD_DESKTOP_DIR/$TARGET"
    local TARGET_RESOURCES_DIR="$RESOURCES_DIR/$TARGET"

    ##--------------------------------------------------------------------------
    ## Create package dir.
    echo "--> Creating package directory...";
    echo "    $TARGET_PKG_DIR";

    ## This is a temp folder so make sure that is't clean.
    rm -f $TARGET_PKG_DIR/temp;

    mkdir -p "$TARGET_PKG_DIR";
    mkdir -p "$TARGET_PKG_DIR/temp";

    ##--------------------------------------------------------------------------
    ## Decide the flags that we gonna pass to cmake
    CXX_FLAGS="-O3 -DNDEBUG";
    if [ "$MODE" == "debug" ]; then
        CXX_FLAGS="-g -DCOOPER_DEBUG";
    fi;

    ##--------------------------------------------------------------------------
    ## Copy the files.
    echo "--> Copying files...";
    cp    $TARGET_BUILD_DIR/CosmicIntruders $TARGET_PKG_DIR/temp;
    cp -R $ASSETS_DIR/                      $TARGET_PKG_DIR/temp;
    cp -R $TARGET_RESOURCES_DIR/*           $TARGET_PKG_DIR/temp;

    ##--------------------------------------------------------------------------
    ## Make a zip.
    echo "--> Creating zip file...";
    cd $TARGET_PKG_DIR/temp;               ## Change the cwd for zip.
        zip -r $TARGET_PKG_DIR/$MODE.zip . ## Run zip.
    cd - 2> /dev/null                      ## Restore the cwd.

    ##--------------------------------------------------------------------------
    ## Clean temporary folder.
    rm -rf $TARGET_PKG_DIR/temp;

    ##--------------------------------------------------------------------------
    echo "--> Done...";
}


##----------------------------------------------------------------------------##
## Build Web                                                                  ##
##----------------------------------------------------------------------------##
build_web()
{
    ##--------------------------------------------------------------------------
    ## Local vars.
    local MODE="$1";
    local TARGET_BUILD_DIR="$BUILD_WEB_DIR";

    ##--------------------------------------------------------------------------
    ## Create build dir.
    echo "--> Creating build directory...";
    echo "    $TARGET_BUILD_DIR";

    mkdir -p "$TARGET_BUILD_DIR";


    ##--------------------------------------------------------------------------
    ## Decide the flags that we gonna pass to em++
    CXX_FLAGS="-O3 -DNDEBUG";
    if [ "$MODE" == "debug" ]; then
        CXX_FLAGS="-g -DCOOPER_DEBUG";
    fi;

    ##--------------------------------------------------------------------------
    ## Run the em++.
    echo "--> Building Cosmic Intruders...";
    echo "    Mode: $MODE | Target: web";
    em++ $CXX_FLAGS                               \
        -std=c++14                                \
        -I$LIBS_ROOT_DIR                          \
        -I$GAME_ROOT_DIR                          \
        -o $TARGET_BUILD_DIR/CosmicIntruders.html \
         $(find $LIBS_ROOT_DIR -iname "*.cpp")    \
         $(find $GAME_ROOT_DIR -iname "*.cpp")    \
         --embed-file "./assets"                  \
         -s USE_SDL=2                             \
         -s USE_SDL_TTF=2                         \
         -s USE_SDL_IMAGE=2                       \
         -s SDL2_IMAGE_FORMATS='["png"]'          \
         -s LEGACY_GL_EMULATION=0                 \
         -s NO_EXIT_RUNTIME=1                     \


    ##--------------------------------------------------------------------------
    ## Done ;D
    echo "--> Done...";
}

package_web()
{
    ##--------------------------------------------------------------------------
    ## Local vars.
    local MODE="$1";
    local TARGET="web";
    local TARGET_PKG_DIR="$PKG_WEB_DIR";
    local TARGET_BUILD_DIR="$BUILD_WEB_DIR"
    local TARGET_RESOURCES_DIR="$RESOURCES_DIR/$TARGET"

    ##--------------------------------------------------------------------------
    ## Create package dir.
    echo "--> Creating package directory...";
    echo "    $TARGET_PKG_DIR";

    ## This is a temp folder so make sure that is't clean.
    rm -f $TARGET_PKG_DIR/temp;

    mkdir -p "$TARGET_PKG_DIR";
    mkdir -p "$TARGET_PKG_DIR/temp";

    ##--------------------------------------------------------------------------
    ## Copy the files.
    echo "--> Copying files...";
    cp $TARGET_BUILD_DIR/CosmicIntruders.js   $TARGET_PKG_DIR/temp;
    cp $TARGET_BUILD_DIR/CosmicIntruders.html $TARGET_PKG_DIR/temp;

    ## Memory file is generated only in -O >2 builds...
    if [ -e $TARGET_BUILD_DIR/CosmicIntruders.html.mem ]; then
         cp $TARGET_BUILD_DIR/CosmicIntruders.html.mem $TARGET_PKG_DIR/temp;
    fi;

    cp -R $TARGET_RESOURCES_DIR/* $TARGET_PKG_DIR/temp;

    ##--------------------------------------------------------------------------
    ## Make a zip.
    echo "--> Creating zip file...";
    cd $TARGET_PKG_DIR/temp;               ## Change the cwd for zip.
        zip -r $TARGET_PKG_DIR/$MODE.zip . ## Run zip.
    cd - 2> /dev/null                      ## Restore the cwd.

    ##--------------------------------------------------------------------------
    ## Clean temporary folder.
    rm -rf $TARGET_PKG_DIR/temp;

    ##--------------------------------------------------------------------------
    echo "--> Done...";
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
## Change the directory to project root.
cd $SCRIPT_DIR/..
pwd

##------------------------------------------------------------------------------
## Parse the options.
while getopts ":m:t:" opt; do
    case "$opt" in
        m) MODE=$OPTARG;     ;;
        t) TARGET=$OPTARG;    ;;
        :) echo "Invalid option: $OPTARG requires an argument" 1>&2 ;;
    esac
done

##------------------------------------------------------------------------------
## Check if the arguments are valid.
if [ "$MODE" != "release" ] && [ "$MODE" != "debug" ]; then
    echo "Invalid mode: ($MODE) - Modes: release | debug";
    exit 1;
fi;

if [ "$TARGET" != "gnu_linux" ] && [ "$TARGET" != "web" ]; then
    echo "Invalid target: ($TARGET) - Targets: gnu_linux | web";
    exit 1;
fi;

##------------------------------------------------------------------------------
## Build
if [ "$TARGET" == "web" ]; then
    build_web   "$MODE";
    package_web "$MODE";
else
    build_desktop   "$MODE" "$TARGET";
    package_desktop "$MODE" "$TARGET";
fi;
