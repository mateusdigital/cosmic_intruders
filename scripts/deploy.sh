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
##  File      : deploy.sh                                                     ##
##  Project   : cosmic_intruders                                              ##
##  Date      : Jun 01, 2023                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2023                                         ##
##                                                                            ##
##                                                                            ##
##  Description :                                                             ##
##   Deploys the output of scripts/build-static.sh to the remote server.      ##
##   Current user should have remote ssh keys installed on the server.        ##
##   Accepts:                                                                 ##
##     -d flag to reset the remote server.                                    ##
##---------------------------------------------------------------------------~##

set -e; ## break on errors


##
##  Directories
##

##------------------------------------------------------------------------------
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
readonly ROOT_DIR="$(dirname "$SCRIPT_DIR")";

readonly SOURCE_FOLDER="${ROOT_DIR}/out";
readonly REMOTE_SERVER="mateus@mateus.digital";
readonly REMOTE_FOLDER="/var/www/mateus.digital/html/cosmic_intruders";

## Delete
if [ "$1" == "-d" ]; then
      rsync -avzu                                       \
            "${SOURCE_FOLDER}/"                         \
            -e ssh "${REMOTE_SERVER}:${REMOTE_FOLDER}/" \
            --delete "${SOURCE_FOLDER}/"                \
      ;
else
      rsync -avzu                                      \
            "${SOURCE_FOLDER}/"                        \
            -e ssh "${REMOTE_SERVER}:${REMOTE_FOLDER}" \
      ;
fi;
