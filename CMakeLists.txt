##~---------------------------------------------------------------------------##
##                        _      _                 _   _                      ##
##                    ___| |_ __| |_ __ ___   __ _| |_| |_                    ##
##                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   ##
##                   \__ \ || (_| | | | | | | (_| | |_| |_                    ##
##                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   ##
##                                                                            ##
##  File      : CMakeLists.txt                                                ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : stdmatt <stdmatt@pixelwizards.io>                             ##
##  Copyright : stdmatt - 2017 - 2020                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Cmake   Definitions                                                        ##
##----------------------------------------------------------------------------##
cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_VERBOSE_MAKEFILE on)


##----------------------------------------------------------------------------##
## Project Definitions                                                        ##
##----------------------------------------------------------------------------##
set(PROJECT_NAME "cosmic-intruders")
project(${PROJECT_NAME})


##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(NOT CMAKE_BUILD_TYPE) ## Default to debug if nothing is given....
    message("[Setting build type to Debug]")
    set(CMAKE_BUILD_TYPE Debug)
endif()

IF(${CMAKE_BUILD_TYPE} MATCHES "Debug") ## Set additional defines for DEBUG
    message("[Setting debug additional defines]")
    add_definitions(-DCOOPER_DEBUG)
ENDIF()

## Game Version.
add_definitions(-DCOW_COSMIC_INTRUDERS_VERSION=${GAME_VERSION}) 


message("[Build type is configure to: ${CMAKE_BUILD_TYPE}]")
message("[Building version: ${GAME_VERSION}]")


##----------------------------------------------------------------------------##
## Include Directories                                                        ##
##----------------------------------------------------------------------------##
include_directories(
    ${CMAKE_SOURCE_DIR}/lib/Cooper
    ${CMAKE_SOURCE_DIR}/game
)

##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
add_subdirectory(lib/Cooper)

set(SOURCE_FILES
    ./game/main.cpp

    ./game/Game/src/Gameplay/Cannon/Cannon.cpp
    ./game/Game/src/Gameplay/Enemy/Alien.cpp
    ./game/Game/src/Gameplay/Formation/Formation.cpp
    ./game/Game/src/Gameplay/GameManager/GameManager.cpp
    ./game/Game/src/Gameplay/GamePlayObject/IGamePlayObject.cpp
    ./game/Game/src/Gameplay/Hud/GameOverHUD.cpp
    ./game/Game/src/Gameplay/Hud/LevelHUD.cpp
    ./game/Game/src/Gameplay/Hud/LivesHUD.cpp
    ./game/Game/src/Gameplay/Hud/ScoreHUD.cpp
    ./game/Game/src/Gameplay/Laser/AlienLaser.cpp
    ./game/Game/src/Gameplay/Laser/AlienLaserNormal.cpp
    ./game/Game/src/Gameplay/Laser/AlienLaserPowered.cpp
    ./game/Game/src/Gameplay/Laser/CannonLaser.cpp
    ./game/Game/src/Gameplay/Laser/ILaser.cpp
    ./game/Game/src/Gameplay/Laser/LaserHolder.cpp
    ./game/Game/src/Gameplay/Level/Level.cpp
    ./game/Game/src/Gameplay/Player/Player.cpp
    ./game/Game/src/Gameplay/Scenery/Ground.cpp
    ./game/Game/src/Gameplay/Scenery/ISceneryObject.cpp
    ./game/Game/src/Gameplay/Scenery/Shield.cpp
    ./game/Game/src/Gameplay/UFO/UFO.cpp
    ./game/Game/src/Helpers/GameUtils.cpp
    ./game/Game/src/Helpers/SceneHelper.cpp
    ./game/Game/src/Helpers/Typewritter.cpp
    ./game/Game/src/Scenes/GameScene.cpp
    ./game/Game/src/Scenes/MenuScene.cpp
    ./game/Game/src/Scenes/SplashScene.cpp
    ./game/Game/src/Helpers/private/desktop/Storage.cpp
    ./game/Game/src/Helpers/private/emscripten/Storage.cpp
)


##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


##----------------------------------------------------------------------------##
## Link Libraries                                                             ##
##----------------------------------------------------------------------------##
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Cooper)
