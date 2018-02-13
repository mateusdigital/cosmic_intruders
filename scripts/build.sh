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
## Vars                                                                       ##
##----------------------------------------------------------------------------##
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";

MODE="debug";
PLATFORM="gnu";
MAKE_ZIP="false";


##----------------------------------------------------------------------------##
## Helper Functions                                                           ##
##----------------------------------------------------------------------------##
to_lower()
{
    echo $(echo $1 | tr [:upper:] [:lower:]);
}

fatal()
{
    echo "[FATAL] $@";
    exit 1;
}


##----------------------------------------------------------------------------##
## Functions                                                                  ##
##----------------------------------------------------------------------------##
show_help()
{
    echo -e "Usage:                                                          \n\
    build.sh                                                                 \n\
      -h | --help                            - Show this info.               \n\
      -m | --mode     <*debug | release>     - Compile mode.                 \n\
      -p | --platform <*gnu | web | windows> - Target platform.              \n\
      -z | --zip                             - Generate the release zip file.\n\
                                                                             \n\
    Options marked with * is assumed to be the default if none is given.     \n\
                                                                             \n\
    [Windows] builds requires that the VsDevCmd.bat path be correctly set.   \n\
    [Web] builds requires that emscripten to be correctly set.               \n\
    "

    exit $1
}


parse_cmd_line()
{
    for FLAG in $@; do
        shift;
        case $FLAG in
            -h | --help     ) show_help 0;     ;;
            -m | --mode     ) MODE="$1";       ;;
            -p | --platform ) PLATFORM="$1";   ;;
            -z | --zip      ) MAKE_ZIP="true"; ;;
        esac
    done;
}


validate_options()
{
    MODE=$(to_lower $MODE);
    PLATFORM=$(to_lower $PLATFORM);

    ##--------------------------------------------------------------------------
    ## Check if MODE is valid.
    test $MODE == "debug"   || \
    test $MODE == "release" || \
         fatal "Invalid mode: ($MODE)";

    ##--------------------------------------------------------------------------
    ## Check if platform is valid.
    test $PLATFORM == "gnu"     || \
    test $PLATFORM == "windows" || \
    test $PLATFORM == "web"     || \
        fatal "Invalid platform: ($PLATFORM)";
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
parse_cmd_line "$@";
validate_options;

cd $SCRIPT_DIR;

##------------------------------------------------------------------------------
## Log ;D
echo "-------------------------------------------------------------------------";
echo "Build Script directory: ($SCRIPT_DIR)";
echo "Compile mode          : ($MODE)";
echo "Target platform       : ($PLATFORM)";
echo "Generate release zip  : ($MAKE_ZIP)";

##------------------------------------------------------------------------------
## GNU/Linux
if [ "$PLATFORM" == "gnu" ]; then
    ## Just call the correct build script...
    ./build/build_gnu_linux.sh $MODE

##------------------------------------------------------------------------------
## Web
elif [ "$PLATFORM" == "web" ]; then
    ## Just call the correct build script...
    ./build/build_web.sh $MODE

##------------------------------------------------------------------------------
## Windows.
elif [ "$PLATFORM" == "windows" ]; then
    ## We need this awful hack because the cmd.exe refuses to run the script
    ## if we only pass the relative path. Don't blame me...
    CURR_WINDOWS_PATH=$(                                                       \
        powershell.exe -Command \& \{                                          \
            [io.path]::combine\(                                               \
                [environment]::CurrentDirectory,                               \
                \"build/build_windows.bat\"                                    \
             \)                                                                \
        \}
    );
    CURR_WINDOWS_PATH=$(echo "$CURR_WINDOWS_PATH" | sed s@\\\\@/@g);
    cmd.exe /C ${CURR_WINDOWS_PATH} ${MODE}
fi;


files_to_zip()
{
    echo "build/windows/CosmicIntruders.exe                     \
          assets                                                \
          lib/Cooper/windows/VS/SDL2_ttf-2.0.14/lib/x86/*.dll   \
          lib/Cooper/windows/VS/SDL2_image-2.0.2/lib/x86/*.dll  \
          lib/Cooper/windows/VS/SDL2-2.0.7/lib/x86/*.dll"
}

##------------------------------------------------------------------------------
## Make the zip package.
mkdir -p ../zip
for ITEM in $(files_to_zip); do
    RECURSE="";
    test -d "../$ITEM" && RECURSE="-R";

    cp $RECURSE ../$ITEM ../zip
done
