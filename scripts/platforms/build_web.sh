
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
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/pixelwizards/shellscript_utils/main.sh


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
MODE="$1";
PROJECT_ROOT=$(pw_realpath "$2");
BUILD_DIR=$(pw_realpath "$3/web_${MODE}");
RELEASE_DIR="$(pw_realpath $4/web_${MODE})";
MAKE_ZIP="$5";
VERSION="$6";

LIBS_ROOT_DIR="./lib/Cooper";
GAME_ROOT_DIR="./game";
ASSETS_DIR="./assets";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
##
## Create build dir.
mkdir -p "$BUILD_DIR";

##
## Decide the flags that we gonna pass to em++
CXX_FLAGS="-O3 -DNDEBUG";
if [ "$MODE" == "debug" ]; then
    CXX_FLAGS="-g -DCOOPER_DEBUG";
fi;

##
## Log
echo "Web Build";

echo "MODE          : $(pw_FC $MODE)";
echo "GAME_ROOT_DIR : $(pw_FC $GAME_ROOT_DIR)";
echo "LIBS_ROOT_DIR : $(pw_FC $LIBS_ROOT_DIR)";
echo "ASSETS_DIR    : $(pw_FC $ASSETS_DIR)";

test -d "$GAME_ROOT_DIR" || pw_log_fatal "Missing directory: ($GAME_ROOT_DIR)";
test -d "$LIBS_ROOT_DIR" || pw_log_fatal "Missing directory: ($LIBS_ROOT_DIR)";
test -d "$ASSETS_DIR"    || pw_log_fatal "Missing directory: ($ASSETS_DIR)";


##
## Run the em++.
# em++ $CXX_FLAGS                                 \
#     -std=c++14                                  \
#     -I"$LIBS_ROOT_DIR"                          \
#     -I"$LIBS_ROOT_DIR"/Cooper                   \
#     -I"$GAME_ROOT_DIR"                          \
#     -o "$BUILD_DIR"/CosmicIntruders.html \
#     $(find "$LIBS_ROOT_DIR" -iname "*.cpp")     \
#     $(find "$GAME_ROOT_DIR" -iname "*.cpp")     \
#     --embed-file "$ASSETS_DIR"                  \
#     -s USE_SDL=2                                \
#     -s USE_SDL_TTF=2                            \
#     -s USE_SDL_IMAGE=2                          \
#     -s SDL2_IMAGE_FORMATS='["png"]'             \
#     -s LEGACY_GL_EMULATION=0                    \
#     -s NO_EXIT_RUNTIME=1

echo $(pw_FG "Done...");

##
## Copy the "assets" files to the build folder
cp -R $PROJECT_ROOT/release_files/web/* $BUILD_DIR;


##
## Make the release file.
if [ "$MAKE_ZIP" == "true" ]; then
    mkdir -p "$RELEASE_DIR";

    cp -R $BUILD_DIR/* $RELEASE_DIR;

    ## Memory file is generated only in -O>2 builds...
    if [ -e $BUILD_DIR/CosmicIntruders.html.mem ]; then
         cp $BUILD_DIR/CosmicIntruders.html.mem $RELEASE_DIR;
    fi;

    cd "$RELEASE_DIR";
        ZIP_NAME="web_${MODE}_${VERSION}.zip";
        zip -r $ZIP_NAME ./*
        mv $ZIP_NAME ../
    cd - > /dev/null
fi;


# package_web()
# {
#     ##--------------------------------------------------------------------------
#     ## Local vars.
#     local MODE="$1";
#     local TARGET="web";
#     local TARGET_PKG_DIR="$PKG_WEB_DIR";
#     local BUILD_DIR="$BUILD_WEB_DIR"
#     local TARGET_RESOURCES_DIR="$RESOURCES_DIR/$TARGET"




#     cp -R $TARGET_RESOURCES_DIR/* $TARGET_PKG_DIR/temp;

#     ##--------------------------------------------------------------------------
#     ## Make a zip.
#     echo "--> Creating zip file...";
#     cd $TARGET_PKG_DIR/temp;               ## Change the cwd for zip.
#         zip -r $TARGET_PKG_DIR/$MODE.zip . ## Run zip.
#     cd - 2> /dev/null                      ## Restore the cwd.

#     ##--------------------------------------------------------------------------
#     ## Clean temporary folder.
#     rm -rf $TARGET_PKG_DIR/temp;

#     ##--------------------------------------------------------------------------
#     echo "--> Done...";
# }