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
##  File      : generate-releaze-zip.sh                                       ##
##  Project   : cosmic_intruderes                                             ##
##  Date      : 2023-06-05                                                    ##
##  License   : GPLv3                                                         ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2023                                         ##
##                                                                            ##
##  Description :                                                             ##
##    Generates the release zip file.                                         ##
##    Requires both ./scripts/build-game.sh and ./scripts/build-static.sh     ##
##    to be ran before this.                                                  ##
##---------------------------------------------------------------------------~##

set -e; ## break on errors.

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";

readonly PROJECT_NAME="cosmic-intruders";
readonly PROJECT_VERSION="$(git describe --abbrev=0 --tags)";
readonly FULL_PROJECT_NAME="${PROJECT_NAME}_${PROJECT_VERSION}";

readonly OUTPUT_DIR="${ROOT_DIR}/dist/${FULL_PROJECT_NAME}";
readonly ZIP_FULL_PATH="${ROOT_DIR}/dist/${FULL_PROJECT_NAME}.zip";

echo "$0 ==> Generating release zip...";

## Create the directory.
rm -rf   "${OUTPUT_DIR}";
mkdir -p "${OUTPUT_DIR}";

## Copy resources.
cp "${ROOT_DIR}/build/${FULL_PROJECT_NAME}.gb" "${OUTPUT_DIR}";
cp "${ROOT_DIR}/res/readme-release.txt"        "${OUTPUT_DIR}";

## Generate zip.
pushd "${OUTPUT_DIR}"
    zip -r "${ZIP_FULL_PATH}" .;
popd

echo "$0 ==> Done...";