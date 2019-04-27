##~---------------------------------------------------------------------------##
##                        _      _                 _   _                      ##
##                    ___| |_ __| |_ __ ___   __ _| |_| |_                    ##
##                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   ##
##                   \__ \ || (_| | | | | | | (_| | |_| |_                    ##
##                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   ##
##                                                                            ##
##  File      : CMakeLists.txt                                                ##
##  Project   : CoreRandom                                                    ##
##  Date      : Feb 07, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : stdmatt <stdmatt@pixelwizards.io>                             ##
##  Copyright : stdmatt - 2018 - 2019                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##


cmake_minimum_required(VERSION 3.5)

add_library(CoreRandom
    CoreRandom/src/Random.cpp
)

target_include_directories(CoreRandom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
