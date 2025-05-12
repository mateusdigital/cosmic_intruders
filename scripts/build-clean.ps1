##----------------------------------------------------------------------------##
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
##  File      : build-clean.ps1                                               ##
##  Project   : cosmic_intruders                                              ##
##  Date      : 2025-05-09                                                    ##
##  License   : See project's COPYING.TXT for full info.                      ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2025                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##----------------------------------------------------------------------------##


Remove-Item -Path "./build" -Recurse -Force -ErrorAction SilentlyContinue;
Remove-Item -Path "./dist"  -Recurse -Force -ErrorAction SilentlyContinue;
Remove-Item -Path "./out"   -Recurse -Force -ErrorAction SilentlyContinue;