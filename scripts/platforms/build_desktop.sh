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

cd "${BUILD_DIR}";
    if [ "$PROJECT_BUILD_MODE" == "debug" ]; then
        cmake "${SCRIPT_DIR}/CMakelists.txt"            \
            -B "${BUILD_DIR}"                           \
            -DCMAKE_BUILD_TYPE="Debug";
        cmake --build .
    else
        cmake "${SCRIPT_DIR}/CMakelists.txt"            \
            -B "${BUILD_DIR}"                           \
            -DCMAKE_BUILD_TYPE="Release";
        cmake --build . --config Release
    fi;
cd --;

echo "$(pw_FG Done...)";
