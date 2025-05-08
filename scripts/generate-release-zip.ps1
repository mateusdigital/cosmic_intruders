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
##  File      : generate-release-zip.ps1                                      ##
##  Project   : Same Game                                                     ##
##  Date      : 2024-03-21                                                    ##
##  License   : See project's COPYING.TXT for full info.                      ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2024                                         ##
##                                                                            ##
##  Description :                                                             ##
##    Generates the release zip file.                                         ##
##---------------------------------------------------------------------------~##


$ErrorActionPreference = "Stop";

## -----------------------------------------------------------------------------
$BUMP_VERSION    = "./thirdparty/bump-version-win.exe";

$PROJECT_NAME      = "cosmic-intruders";
$PROJECT_VERSION   = (& $BUMP_VERSION --show-version);
$FULL_PROJECT_NAME = "${PROJECT_NAME}-${PROJECT_VERSION}";


## -----------------------------------------------------------------------------
foreach ($item in $(Get-ChildItem "./build/*")) {
    $build_name     = $item.BaseName;
    $build_platform = $build_name.Replace("build-", "");

    $output_name = "${FULL_PROJECT_NAME}-${build_platform}";
    $dist_dir   = "./dist"
    $output_dir = "$dist_dir/$output_name";

    Write-Host "==> Build directory:  $item";
    Write-Host "==> Output directory: $output_dir";

    New-Item -Path $output_dir -ItemType Directory -Force;
    ## Copy the build files.
    Copy-Item -Path $item/* -Destination $output_dir/
    ## Copy resource files.
    Copy-Item -Path "resources/readme-release.txt" -Destination $output_dir;


    ## Make the zip
    $zip_fullpath = "${output_dir}.zip";

    Compress-Archive                      `
        -Path "$output_dir"               `
        -DestinationPath "$zip_fullpath"  `
        -Force;
}

# $ZIP_FULL_PATH = "./dist/${FULL_PROJECT_NAME}_${PLATFORM_NAME}.zip";


# Write-Output "==> Generating release zip ($PLATFORM_NAME)...";

# ## Create the directory.
# if(Test-Path "$output_dir") {
#     Remove-Item -Path "$output_dir" -Force -Recurse;
# }
# New-Item -ItemType Directory -Path "$output_dir";


# Write-Output "==> Done...";
