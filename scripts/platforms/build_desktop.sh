
##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : build_desktop.sh                                              ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Feb 12, 2018                                                  ##
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
OS_NAME=$(pw_os_get_simple_name);

MODE="$1";
CMAKE_ROOT="$(pw_realpath $2)";
BUILD_DIR="$(pw_realpath $3/${OS_NAME}_${MODE})";
RELEASE_DIR="$(pw_realpath $4/${OS_NAME}_${MODE})";
MAKE_ZIP="$5";
VERSION="$6";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
echo "Desktop Build";
echo "  Build   at: $(pw_FC $BUILD_DIR)";
echo "  Release at: $(pw_FC $RELEASE_DIR)";

##
## Go to the build directory, this eases the cmake operations...
mkdir -p "$BUILD_DIR";

cd "$BUILD_DIR";
    cmake "$CMAKE_ROOT" -DCMAKE_BUILD_TYPE=$MODE
    cmake --build .
cd - > /dev/null

echo "$(pw_FG Done...)";

##
## Make the release file.
if [ "$MAKE_ZIP" == "true" ]; then
    mkdir -p "$RELEASE_DIR";
    cp    $BUILD_DIR/CosmicIntruders $RELEASE_DIR;
    cp -R $CMAKE_ROOT/assets         $RELEASE_DIR;

    cd "$RELEASE_DIR";
        ZIP_NAME="${OS_NAME}_${MODE}_${VERSION}.zip";
        zip -r $ZIP_NAME ./*
        mv $ZIP_NAME ../
    cd - > /dev/null
fi;
