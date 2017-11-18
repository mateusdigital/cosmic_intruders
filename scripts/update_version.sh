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
## CONFIG                                                                     ##
##----------------------------------------------------------------------------##
PROJECT_NAME="COSMIC_INTRUDERS"
HEADER_FILE="game/Game/include/Helpers/Version.h" ## Relative to project root.


##----------------------------------------------------------------------------##
## Constants                                                                  ##
##----------------------------------------------------------------------------##
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
MAJOR=$(echo $@ | cut -d. -f1);
MINOR=$(echo $@ | cut -d. -f2);
REVISION=$(echo $@ | cut -d. -f3);


##----------------------------------------------------------------------------##
## Sanity                                                                     ##
##----------------------------------------------------------------------------##
## Thanks to Charles Duffy in SO:
##    http://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash
re='^[0-9]+$' #Check if is number.

if ! [[ $MAJOR =~ $re ]] ; then
   echo "MAJOR Not a number" >&2;
   exit 1
fi

if ! [[ $MINOR =~ $re ]] ; then
   echo "MINOR Not a number" >&2;
   exit 1
fi

if ! [[ $REVISION =~ $re ]] ; then
   echo "REVISION Not a number" >&2;
   exit 1
fi


##----------------------------------------------------------------------------##
## Update HEADER FILE                                                         ##
##----------------------------------------------------------------------------##
##----------------------------------------------------------------------------##
## Make sure that we're on project root.
cd "$SCRIPT_DIR/..";

##----------------------------------------------------------------------------##
## Make the update.
MAJOR_STR="#define ${PROJECT_NAME}_VERSION_MAJOR    ";
MINOR_STR="#define ${PROJECT_NAME}_VERSION_MINOR    ";
REVISION_STR="#define ${PROJECT_NAME}_VERSION_REVISION ";

cat $HEADER_FILE \
    | sed -e s/"$MAJOR_STR\".*\""/"$MAJOR_STR\"$MAJOR\""/g          \
    | sed -e s/"$MINOR_STR\".*\""/"$MINOR_STR\"$MINOR\""/g          \
    | sed -e s/"$REVISION_STR\".*\""/"$REVISION_STR\"$REVISION\""/g \
    > $HEADER_FILE.new;


##----------------------------------------------------------------------------##
## CHECKING                                                                   ##
##----------------------------------------------------------------------------##
## CHECK IF OPERATION WAS OK ##
cat $HEADER_FILE.new;

echo "Is this correct?[y/n]";
read CORRECT;

if [ "$CORRECT" = "y" ]; then
    echo "Updating the files..."
    mv $HEADER_FILE.new  $HEADER_FILE;
else
  rm $HEADER_FILE.new
fi;

