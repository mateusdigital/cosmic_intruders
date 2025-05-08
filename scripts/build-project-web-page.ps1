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
##  File      : build-static.ps1                                              ##
##  Project   : Same Game                                                     ##
##  Date      : 2024-03-21                                                    ##
##  License   : See project's COPYING.TXT for full info.                      ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2024                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

$ErrorActionPreference = "Stop"
Write-Output "==> Building Web Page...";

## -----------------------------------------------------------------------------
$GAME_VERSION     = (./thirdparty/bump-version-win.exe --show-version-full);
$OUTPUT_DIRECTORY = "./out/";

##------------------------------------------------------------------------------
Remove-Item -Recurse -Force "${OUTPUT_DIRECTORY}";
New-Item -Type Directory "${OUTPUT_DIRECTORY}" -Force;

## Our index
Copy-Item -Recurse "./html/*" "${OUTPUT_DIRECTORY}";

## Emscripten Files
Copy-Item                           `
    "./build-web-release/game.data" `
    "./build-web-release/game.js"   `
    "./build-web-release/game.wasm" `
    ${OUTPUT_DIRECTORY};


## Distribution files.
New-Item -Type Directory "${OUTPUT_DIRECTORY}/data";
Copy-Item "dist/"*.zip "${OUTPUT_DIRECTORY}/data";

Write-Output "==> done...";