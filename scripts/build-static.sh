#!/usr/bin/env bash
##~---------------------------------------------------------------------------##
##                               *       +                                    ##
##                         '                  |                               ##
##                     ()    .-.,="``"=.    - o -                             ##
##                           '=/_       \     |                               ##
##                        *   |  '=._    |                                    ##
##                             \     `=./`,        '                          ##
##                          .   '=.__.=' `='      *                           ##
##                 +                         +                                ##
##                      O      *        '       .                             ##
##                                                                            ##
##  File      : build-static.sh                                               ##
##  Project   : cosmic_intruders                                              ##
##  Date      : 2023-05-13                                                    ##
##  License   : GPLv3                                                         ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2023                                         ##
##                                                                            ##
##  Description :                                                             ##
##    Builds the website for the project.                                     ##
##    Requires ./scripts/build-game --web to be ran first.                    ##
##---------------------------------------------------------------------------~##

set -e ## break on errors...

##------------------------------------------------------------------------------
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";
readonly OUTPUT_DIRECTORY="out";


##------------------------------------------------------------------------------
rm -rf "${ROOT_DIR}/${OUTPUT_DIRECTORY}";
mkdir -p "${ROOT_DIR}/${OUTPUT_DIRECTORY}";

cp -R "${ROOT_DIR}"/html/* "${ROOT_DIR}"/${OUTPUT_DIRECTORY};

cp "${ROOT_DIR}"/build-web-Release/game.data \
   "${ROOT_DIR}"/build-web-Release/game.js   \
   "${ROOT_DIR}"/build-web-Release/game.wasm \
   "${ROOT_DIR}"/${OUTPUT_DIRECTORY};

##------------------------------------------------------------------------------
echo "$0 done...";