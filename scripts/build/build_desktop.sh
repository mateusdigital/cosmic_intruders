
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
BUILD_DIR="$(pw_realpath $2/$OS_NAME)";
CMAKE_ROOT="$(pw_realpath $3)";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
echo "Desktop Build";

##
## Go to the build directory, this eases the cmake operations...
mkdir -p "$BUILD_DIR";
cd "$BUILD_DIR";

cmake "$CMAKE_ROOT" -DCMAKE_BUILD_TYPE=$MODE
cmake --build .

cd - > /dev/null
echo "$(pw_FG Done...)";
