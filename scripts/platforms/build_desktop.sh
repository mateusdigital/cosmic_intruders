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
##  Copyright : stdmatt - 2017 - 2020                                         ##
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
PLATFORM_NAME="$(pw_os_get_simple_name)";
if [ "$PLATFORM_NAME" == "$(PW_OS_WSL)" ]; then
    PLATFORM_NAME="$(PW_OS_GNU_LINUX)";
fi;

BUILD_DIR="${PROJECT_BUILD_DIR}/${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
echo "Desktop Build";
echo "Building at: ${BUILD_DIR}";
mkdir -p "$BUILD_DIR";

cmake "${SCRIPT_DIR}/CMakelists.txt"            \
    -B "${BUILD_DIR}"                           \
    -D -DCMAKE_BUILD_TYPE="$PROJECT_BUILD_MODE";

cd "${BUILD_DIR}";
    cmake --build .
cd --;

echo "$(pw_FG Done...)";
