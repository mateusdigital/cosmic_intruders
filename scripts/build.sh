##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : build.sh                                                      ##
##  Project   : CosmicIntruders                                               ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
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
SCRIPT_DIR="$(pw_get_script_dir)";
PROJECT_ROOT=$(pw_realpath "$SCRIPT_DIR/..");
BUILD_DIR=$(pw_realpath "$SCRIPT_DIR/../build");
RELEASES_DIR=$(pw_realpath "$SCRIPT_DIR/../releases");

MODE="debug";
PLATFORM="desktop";
MAKE_ZIP="false";
VERSION="";
PLATFORM_BUILD_SCRIPT="";


##----------------------------------------------------------------------------##
## Functions                                                                  ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
show_help()
{
    cat << END_TEXT
Usage:
    build.sh
      -h | --help                        - Show this info.
      -c | --clean                       - Cleans the build files.
      -m | --mode     <*debug | release> - Compile mode.
      -p | --platform <*desktop | web>   - Target platform.
      -z | --zip                         - Generate the release zip file.

    Options marked with * is assumed to be the default if none is given.

    [Windows] builds requires that the VsDevCmd.bat path be correctly set.
    [Web] builds requires that emscripten to be correctly set.
END_TEXT

    exit $1
}


##------------------------------------------------------------------------------
clean()
{
    echo "Cleaning files...";

    echo "   Build path: $(pw_FC $BUILD_DIR)";
    rm -vrf "$BUILD_DIR"

    echo "   Releases path: $(pw_FC $RELEASES_DIR)";
    rm -vrf "$RELEASES_DIR"

    exit 0;
}


##------------------------------------------------------------------------------
parse_cmd_line()
{
    for FLAG in $@; do
        shift;
        case $FLAG in
            -h | --help     ) show_help 0;     ;;
            -c | --clean    ) clean;           ;;
            -m | --mode     ) MODE="$1";       ;;
            -p | --platform ) PLATFORM="$1";   ;;
            -z | --zip      ) MAKE_ZIP="true"; ;;
            -v | --version  ) VERSION="$1"     ;;
        esac
    done;
}

##------------------------------------------------------------------------------
validate_options()
{
    MODE=$(pw_to_lower $MODE);
    PLATFORM=$(pw_to_lower $PLATFORM);

    ##
    ## Check if MODE is valid.
    test $MODE == "debug"   || \
    test $MODE == "release" || \
         pw_log_fatal "Invalid mode: ($MODE)";

    ##
    ## Check if platform is valid.
    PLATFORM_BUILD_SCRIPT="${SCRIPT_DIR}/build/build_${PLATFORM}.sh";
    test -f "$PLATFORM_BUILD_SCRIPT" ||
        pw_log_fatal "Invalid platform: ($PLATFORM)";

    ##
    ## Check if version number is valid.
    if [ "$MAKE_ZIP" == "true" ]; then
        local GREP_RESULT=$(  \
            echo "$VERSION" | \
            grep "^[[:digit:]]\.[[:digit:]]\.[[:digit:]]$" \
        );

        test -z "$GREP_RESULT" && pw_log_fatal "Version number is invalid: ($VERSION)";
    fi;
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd "$PROJECT_ROOT";

##
## Parse the command line arguments.
parse_cmd_line "$@";
validate_options;

##
## Log ;D
echo "Cosmic Intruders";
echo "Build Script directory : $(pw_FC $SCRIPT_DIR)";
echo "Compile mode           : $(pw_FC $MODE      )";
echo "Target platform        : $(pw_FC $PLATFORM  )";
echo "Generate release zip   : $(pw_FC $MAKE_ZIP  )";
echo "Current version        : $(pw_FC $VERSION   )";
echo "";

##
## Call the actual build script.
echo "Calling: $(pw_FM $PLATFORM_BUILD_SCRIPT)";
"$PLATFORM_BUILD_SCRIPT" "$MODE" "$BUILD_DIR" "$PROJECT_ROOT";



## @todo(stdmatt): Check how to zip files....
# ##----------------------------------------------------------------------------##
# ## Make zip                                                                   ##
# ##----------------------------------------------------------------------------##
# if [ "$MAKE_ZIP" == "true" ]; then
#     echo "Make Zip - Version ($VERSION)";

#     ##--------------------------------------------------------------------------
#     ## Create the target directory.
#     ZIP_NAME="${PLATFORM}_${MODE}_v${VERSION}";
#     TARGET_PATH="../$ZIP_NAME";

#     rm -rf "$TARGET_PATH"; ## Clean
#     mkdir  "$TARGET_PATH"; ## Create new.

#     ##--------------------------------------------------------------------------
#     ## Copy the files.
#     test -f "./files_to_zip.sh" || pw_log_fatal "Missing file: (files_to_zip.sh)";

#     FILES_TO_ZIP=$(./files_to_zip.sh "$PLATFORM");
#     for ITEM in $FILES_TO_ZIP; do
#         ##----------------------------------------------------------------------
#         ## Directory - Copy its contents.
#         if [ -d "$ITEM" ]; then
#             echo "Copying ($ITEM) -> ($TARGET_PATH)";
#             cp -R $ITEM $TARGET_PATH;
#         ##----------------------------------------------------------------------
#         ## Regular file - Just copy it.
#         else
#             echo "Copying ($CP_PATH) -> ($TARGET_PATH)";
#             cp  $ITEM $TARGET_PATH;
#         fi;
#     done;

#     ##--------------------------------------------------------------------------
#     ## Make the zip.
#     cd "${TARGET_PATH}";            ## Need to make the contents more nicer.
#     zip -rv "${ZIP_NAME}.zip" ".";  ## Zip everything on this folder.
#     mv "${ZIP_NAME}.zip" "../";     ## Put the .zip on the right place.
#     cd - > /dev/null                ## Go back...
# fi;
