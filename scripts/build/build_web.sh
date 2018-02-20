
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
source /usr/local/src/acow_shellscript_utils.sh


##------------------------------------------------------------------------------
## Local vars.
MODE="$1";
LIBS_ROOT_DIR="$(realpath ../lib/Cooper)";
GAME_ROOT_DIR="$(realpath ../game)";
ASSETS_DIR="$(realpath ../assets)";

TARGET_BUILD_DIR="$(realpath ../build/web)";


##------------------------------------------------------------------------------
## Create build dir.
mkdir -p "$TARGET_BUILD_DIR";

##------------------------------------------------------------------------------
## Decide the flags that we gonna pass to em++
CXX_FLAGS="-O3 -DNDEBUG";
if [ "$MODE" == "debug" ]; then
    CXX_FLAGS="-g -DCOOPER_DEBUG";
fi;

##------------------------------------------------------------------------------
## Log
center_text "Web Build";

echo "MODE          : ($MODE)";
echo "GAME_ROOT_DIR : ($GAME_ROOT_DIR)";
echo "LIBS_ROOT_DIR : ($LIBS_ROOT_DIR)";
echo "ASSETS_DIR    : ($ASSETS_DIR)";

test -d "$GAME_ROOT_DIR" || fatal "Missing directory: ($GAME_ROOT_DIR)";
test -d "$LIBS_ROOT_DIR" || fatal "Missing directory: ($LIBS_ROOT_DIR)";
test -d "$ASSETS_DIR"    || fatal "Missing directory: ($ASSETS_DIR)";


##------------------------------------------------------------------------------
## Run the em++.
em++ $CXX_FLAGS                                 \
    -std=c++14                                  \
    -I"$LIBS_ROOT_DIR"                          \
    -I"$LIBS_ROOT_DIR"/Cooper                   \
    -I"$GAME_ROOT_DIR"                          \
    -o "$TARGET_BUILD_DIR"/CosmicIntruders.html \
    $(find "$LIBS_ROOT_DIR" -iname "*.cpp")     \
    $(find "$GAME_ROOT_DIR" -iname "*.cpp")     \
    --embed-file "$ASSETS_DIR"                  \
    -s USE_SDL=2                                \
    -s USE_SDL_TTF=2                            \
    -s USE_SDL_IMAGE=2                          \
    -s SDL2_IMAGE_FORMATS='["png"]'             \
    -s LEGACY_GL_EMULATION=0                    \
    -s NO_EXIT_RUNTIME=1

center_text "-"

# package_web()
# {
#     ##--------------------------------------------------------------------------
#     ## Local vars.
#     local MODE="$1";
#     local TARGET="web";
#     local TARGET_PKG_DIR="$PKG_WEB_DIR";
#     local TARGET_BUILD_DIR="$BUILD_WEB_DIR"
#     local TARGET_RESOURCES_DIR="$RESOURCES_DIR/$TARGET"

#     ##--------------------------------------------------------------------------
#     ## Create package dir.
#     echo "--> Creating package directory...";
#     echo "    $TARGET_PKG_DIR";

#     ## This is a temp folder so make sure that is't clean.
#     rm -f $TARGET_PKG_DIR/temp;

#     mkdir -p "$TARGET_PKG_DIR";
#     mkdir -p "$TARGET_PKG_DIR/temp";

#     ##--------------------------------------------------------------------------
#     ## Copy the files.
#     echo "--> Copying files...";
#     cp $TARGET_BUILD_DIR/CosmicIntruders.js   $TARGET_PKG_DIR/temp;
#     cp $TARGET_BUILD_DIR/CosmicIntruders.html $TARGET_PKG_DIR/temp;

#     ## Memory file is generated only in -O >2 builds...
#     if [ -e $TARGET_BUILD_DIR/CosmicIntruders.html.mem ]; then
#          cp $TARGET_BUILD_DIR/CosmicIntruders.html.mem $TARGET_PKG_DIR/temp;
#     fi;

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
