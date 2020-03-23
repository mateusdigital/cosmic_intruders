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
# OS_NAME=$(pw_os_get_simple_name);

# MODE="$1";
# CMAKE_ROOT="$(pw_realpath $2)";
# BUILD_DIR="$(pw_realpath $3/${OS_NAME}_${MODE})";
# RELEASE_DIR="$(pw_realpath $4/${OS_NAME}_${MODE})";
# VERSION="$6";
SCRIPT_DIR="$(pw_get_script_dir)";
PLATFORM_NAME="$(pw_os_get_simple_name)";
BUILD_DIR="${PROJECT_BUILD_DIR}/${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}";

##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
echo "Desktop Build";
echo "Building at: ${BUILD_DIR}";

##
## Go to the build directory, this eases the cmake operations...
mkdir -p "$BUILD_DIR";

cmake "${SCRIPT_DIR}/CMakelists.txt"           \
    -B "${BUILD_DIR}"                           \
    -D -DCMAKE_BUILD_TYPE=$"PROJECT_BUILD_MODE";

cd "${BUILD_DIR}";
    cmake --build .
cd --;

echo "$(pw_FG Done...)";
