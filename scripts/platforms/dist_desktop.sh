##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
SCRIPT_DIR="$(pw_get_script_dir)";

PLATFORM_NAME="$(pw_os_get_simple_name)";
if [ "$PLATFORM_NAME" == "$(PW_OS_WSL)" ]; then
    PLATFORM_NAME="$(PW_OS_GNU_LINUX)";
fi;

BUILD_DIR="${PROJECT_BUILD_DIR}/${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}";
DIST_DIR="${PROJECT_DIST_DIR}/${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}";


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
rm -rf   "$DIST_DIR";
mkdir -p "$DIST_DIR";

cp    "$BUILD_DIR/$PROJECT_NAME" "$DIST_DIR";
cp -r "$PROJECT_ROOT/assets"     "$DIST_DIR";

echo "Creating zip file";
ZIP_FILENAME="${PROJECT_NAME}_${PLATFORM_NAME}_${PROJECT_VERSION}.zip";
pw_pushd "${DIST_DIR}";
    zip -r "${ZIP_FILENAME}" ".";
    mv "${ZIP_FILENAME}" "${PROJECT_DIST_DIR}";
pw_popd

echo "$(pw_FG Done...)";