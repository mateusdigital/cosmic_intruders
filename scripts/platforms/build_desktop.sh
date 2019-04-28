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
