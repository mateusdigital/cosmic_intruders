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
##---------------------------------------------------------------------------~##

set -e; ## break on errors.

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
readonly SCRIPT_ROOT_DIR="$(dirname "$SCRIPT_DIR")";

if [ ! -z "$WINDOWS_REPO_ROOT" ]; then
    echo "Windows hack build...";
    readonly ROOT_DIR="$WINDOWS_REPO_ROOT";
    readonly PLATFORM_NAME="windows";
else
    readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";
    readonly PLATFORM_NAME="gnu_linux";
fi;

if [ -n "$(uname -a | grep -i "Darwin")" ]; then
    PLATFORM_NAME="macOS";
fi;

readonly PROJECT_NAME="cosmic-intruders";
readonly PROJECT_VERSION="$(git describe --abbrev=0 --tags)";
readonly FULL_PROJECT_NAME="${PROJECT_NAME}_${PROJECT_VERSION}";

readonly OUTPUT_DIR="${SCRIPT_ROOT_DIR}/dist/${FULL_PROJECT_NAME}";
readonly ZIP_FULL_PATH="${SCRIPT_ROOT_DIR}/dist/${FULL_PROJECT_NAME}_${PLATFORM_NAME}.zip";


echo "$0 ==> Generating release zip ($PLATFORM_NAME)...";

## Create the directory.
rm    -rf   "${OUTPUT_DIR}";
mkdir -p "${OUTPUT_DIR}";

## Copy resources.
cp -v    "${ROOT_DIR}/build-pc-Release/"*               "${OUTPUT_DIR}";
cp -v -R "${ROOT_DIR}/assets/"                          "${OUTPUT_DIR}/assets";
cp -v    "${ROOT_DIR}/resources/readme-release.txt"     "${OUTPUT_DIR}";

## Generate zip.
pushd "${OUTPUT_DIR}"
    zip -r "${ZIP_FULL_PATH}" .;
popd

echo "$0 ==> Done...";