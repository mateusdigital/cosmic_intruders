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

## retrive build and version.
readonly VERSION="$(git describe --abbrev=0 --tags)";
readonly CURR_BUILD="$(cat "${ROOT_DIR}/.buildno")";
readonly NEXT_BUILD="$(( CURR_BUILD + 1 ))";


##------------------------------------------------------------------------------
rm -rf "${ROOT_DIR}/${OUTPUT_DIRECTORY}";
mkdir -p "${ROOT_DIR}/${OUTPUT_DIRECTORY}";

## Our index
cp -R "${ROOT_DIR}"/html/* "${ROOT_DIR}"/${OUTPUT_DIRECTORY};

## update the index with version and build number.
cat "${ROOT_DIR}/out/index.html"          \
    | sed s/"_version_"/"${VERSION}"/g    \
    | sed s/"_build_"/"${NEXT_BUILD}"/g   \
    > "${ROOT_DIR}/out/index.html.tmp"    \
    && mv                                 \
        "${ROOT_DIR}/out/index.html.tmp"  \
        "${ROOT_DIR}/out/index.html"      \
    ;

## Emscripten
cp "${ROOT_DIR}"/build-web-Release/game.data \
   "${ROOT_DIR}"/build-web-Release/game.js   \
   "${ROOT_DIR}"/build-web-Release/game.wasm \
   "${ROOT_DIR}"/${OUTPUT_DIRECTORY};



##------------------------------------------------------------------------------
echo "${NEXT_BUILD}" > "${ROOT_DIR}/.buildno"; ## update build no.
echo "$0 done...";
