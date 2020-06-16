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
##  Copyright : stdmatt - 2017 - 2019                                         ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

## External Vars...
## @TODO(stdmatt): Add  an output saying that we need to export this vars...
set(PROJECT_NAME $ENV{PROJECT_NAME})
set(PROJECT_ROOT $ENV{PROJECT_ROOT})

message("--->> ${PROJECT_ROOT} <<---")
cmake_minimum_required(VERSION 3.5)
project(${PROJECT_NAME})


##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release build.")
ENDIF()

IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("[Setting debug additional defines]")
    add_definitions(-DCOOPER_DEBUG)
ENDIF()

message("[Build type is configure to: ${CMAKE_BUILD_TYPE}]")


##----------------------------------------------------------------------------##
## Include Directories                                                        ##
##----------------------------------------------------------------------------##
include_directories(
    ## Cooper.
    ${PROJECT_ROOT}/lib/Cooper
    ## Game.
    ${PROJECT_ROOT}/game
)


##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
add_subdirectory(${PROJECT_ROOT}/lib/Cooper build)

set(SOURCE_FILES
    ${PROJECT_ROOT}/game/main.cpp

    ${PROJECT_ROOT}/game/Game/src/Gameplay/Cannon/Cannon.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Enemy/Alien.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Formation/Formation.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/GameManager/GameManager.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/GamePlayObject/IGamePlayObject.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Hud/GameOverHUD.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Hud/LevelHUD.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Hud/LivesHUD.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Hud/ScoreHUD.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/AlienLaser.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/AlienLaserNormal.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/AlienLaserPowered.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/CannonLaser.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/ILaser.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Laser/LaserHolder.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Level/Level.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Player/Player.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Scenery/Ground.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Scenery/ISceneryObject.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/Scenery/Shield.cpp
    ${PROJECT_ROOT}/game/Game/src/Gameplay/UFO/UFO.cpp
    ${PROJECT_ROOT}/game/Game/src/Helpers/GameUtils.cpp
    ${PROJECT_ROOT}/game/Game/src/Helpers/SceneHelper.cpp
    ${PROJECT_ROOT}/game/Game/src/Helpers/Typewritter.cpp
    ${PROJECT_ROOT}/game/Game/src/Scenes/GameScene.cpp
    ${PROJECT_ROOT}/game/Game/src/Scenes/MenuScene.cpp
    ${PROJECT_ROOT}/game/Game/src/Scenes/SplashScene.cpp
    ${PROJECT_ROOT}/game/Game/src/Helpers/private/desktop/Storage.cpp
    ${PROJECT_ROOT}/game/Game/src/Helpers/private/emscripten/Storage.cpp
)


##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


##----------------------------------------------------------------------------##
## Link Libraries                                                             ##
##----------------------------------------------------------------------------##
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Cooper)
