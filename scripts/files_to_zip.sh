#!/usr/bin/env sh
##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : files_to_zip.sh                                               ##
##  Project   : CosmicIntruders                                               ##
##  Date      : Feb 19, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
FILES="";
PLATFORM="$1";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
## GNU/Linux
if [ "$PLATFORM" == "gnu_linux" ]; then
    ## Game.
    FILES+=" ../build/gnu_linux/CosmicIntruders ";
    FILES+=" ../assets ";
    ## Release stuff..
    FILES+=" ../release_files/gnu_linux/README.md ";

##------------------------------------------------------------------------------
## Web
elif [ "$PLATFORM" == "web" ]; then
    ## Game...
    FILES=+" ../build/web/CosmicIntruders.html.map ";
    FILES=+" ../build/web/CosmicIntruders.html.mem ";
    FILES=+" ../build/web/CosmicIntruders.js ";
    ## Release stuff...
    FILES+=" ../release_files/web/images ";
    FILES+=" ../release_files/web/svg ";
    FILES+=" ../release_files/web/index.html ";
fi;

echo "$FILES"
