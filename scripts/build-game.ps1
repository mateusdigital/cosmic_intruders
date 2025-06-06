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
##  File      : build-game.ps1                                                ##
##  Project   : cosmic_intruders                                              ##
##  Date      : 2023-06-06                                                    ##
##  License   : GPLv3                                                         ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2023                                         ##
##                                                                            ##
##  Description :                                                             ##
##    This builds the game using mingw -                                      ##
##       It tries to replicate the most of ./scripts/build-game.sh            ##
##    Requires that mingw to be located at: C:/MinGW                          ##
##---------------------------------------------------------------------------~##

$env:Path+=";C:/MinGW/bin";

if (Test-Path "./build-pc-Release") {
    Remove-Item "./build-pc-Release" -Recurse -Force;
}
New-Item "./build-pc-Release" -Type Directory -Force;

g++.exe                                                                                 `
    (Get-ChildItem -Path . -Filter *.cpp -Recurse -ErrorAction SilentlyContinue -Force) `
    -std=c++14                                                                `
                                                                              `
    -I./lib/SDL2-devel-2.26.5-mingw/i686-w64-mingw32/include/SDL2             `
    -I./lib/SDL2_image-2.6.3-mingw/i686-w64-mingw32/include/SDL2              `
    -I./lib/SDL2_mixer-2.6.3-mingw/i686-w64-mingw32/include/SDL2              `
    -I./lib/SDL2_ttf-2.20.2-mingw/i686-w64-mingw32/include/SDL2               `
                                                                              `
    -I./lib                                                                   `
    -I./lib/Cooper                                                            `
    -I./lib/Cooper/Cooper                                                     `
    -I./game                                                                  `
                                                                              `
    -L./lib/SDL2-devel-2.26.5-mingw/i686-w64-mingw32/lib                      `
    -L./lib/SDL2_image-2.6.3-mingw/i686-w64-mingw32/lib                       `
    -L./lib/SDL2_mixer-2.6.3-mingw/i686-w64-mingw32/lib                       `
    -L./lib/SDL2_ttf-2.20.2-mingw/i686-w64-mingw32/lib                        `
                                                                              `
    -lmingw32                                                                 `
    -mwindows                                                                 `
                                                                              `
    -lSDL2main                                                                `
    -lSDL2                                                                    `
    -lSDL2_mixer                                                              `
    -lSDL2_ttf                                                                `
    -lSDL2_image                                                              `
                                                                              `
    -DGAME_VERSION="`"${GAME_VERSION}`""                                      `
    -o cosmic-intruders                                                       `
    ;

##------------------------------------------------------------------------------
Copy-Item (Get-ChildItem -Path ./lib/SDL2-devel-2.26.5-mingw/i686-w64-mingw32/  -Filter *.dll -Recurse -ErrorAction SilentlyContinue -Force) ./build-pc-Release
Copy-Item (Get-ChildItem -Path ./lib/SDL2_image-2.6.3-mingw/i686-w64-mingw32/   -Filter *.dll -Recurse -ErrorAction SilentlyContinue -Force) ./build-pc-Release
Copy-Item (Get-ChildItem -Path ./lib/SDL2_mixer-2.6.3-mingw/i686-w64-mingw32/   -Filter *.dll -Recurse -ErrorAction SilentlyContinue -Force) ./build-pc-Release
Copy-Item (Get-ChildItem -Path ./lib/SDL2_ttf-2.20.2-mingw/i686-w64-mingw32/    -Filter *.dll -Recurse -ErrorAction SilentlyContinue -Force) ./build-pc-Release
Copy-Item ./lib/libgcc_s_dw2-1.dll ./build-pc-Release
Copy-Item ./lib/libstdc++-6.dll    ./build-pc-Release

Move-Item ./cosmic-intruders.exe ./build-pc-Release
