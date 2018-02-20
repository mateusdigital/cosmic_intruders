#!/bin/bash
##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : update_version.sh                                             ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2017                                             ##
##                                                                            ##
##  Description :                                                             ##
##    This will update the version of game.                                   ##
##    So each new release we should run this with the appropriated version    ##
##    numbers, to update the stuff in source files that depends on those      ##
##    numbers.                                                                ##
##                                                                            ##
##  Usage:                                                                    ##
##    ./version_update MAJOR.MINOR.REVISION                                   ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/acow_shellscript_utils.sh

##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd $(get_script_dir);

update_version                             \
    "COSMIC_INTRUDERS"                     \
    "$1"                                   \
    ../game/Game/include/Helpers/Version.h