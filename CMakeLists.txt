##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : CMakeLists.txt                                                ##
##  Project   : Cosmic Intruders                                              ##
##  Date      : Nov 17, 2017                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2017                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

cmake_minimum_required(VERSION 3.7)
project(CosmicIntruders)

##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD                 14)


##----------------------------------------------------------------------------##
## Modules Definitions                                                        ##
##----------------------------------------------------------------------------##
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
##------------------------------------------------------------------------------
## Find packages scripts was taken from:
##   https://github.com/tcbrindle/sdl2-cmake-scripts
find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf   REQUIRED)


##----------------------------------------------------------------------------##
## Include Directories                                                        ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
## SDL2.
include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

##------------------------------------------------------------------------------
## Cooper.
include_directories(
    ${CMAKE_SOURCE_DIR}/lib
)
##------------------------------------------------------------------------------
## Game.
include_directories(
    ${CMAKE_SOURCE_DIR}/game
)


##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
set(SOURCE_FILES
    ./game/main.cpp

    ./game/Game/include/GamePlay/Cannon/Cannon.h
    ./game/Game/include/GamePlay/Enemy/Alien.h
    ./game/Game/include/GamePlay/Formation/Formation.h
    ./game/Game/include/GamePlay/GameManager/GameManager.h
    ./game/Game/include/GamePlay/GamePlayObject/IGamePlayObject.h
    ./game/Game/include/GamePlay/Hud/GameOverHUD.h
    ./game/Game/include/GamePlay/Hud/LevelHUD.h
    ./game/Game/include/GamePlay/Hud/LivesHUD.h
    ./game/Game/include/GamePlay/Hud/ScoreHUD.h
    ./game/Game/include/GamePlay/Laser/AlienLaser.h
    ./game/Game/include/GamePlay/Laser/AlienLaserNormal.h
    ./game/Game/include/GamePlay/Laser/AlienLaserPowered.h
    ./game/Game/include/GamePlay/Laser/CannonLaser.h
    ./game/Game/include/GamePlay/Laser/ILaser.h
    ./game/Game/include/GamePlay/Laser/LaserHolder.h
    ./game/Game/include/GamePlay/Level/Level.h
    ./game/Game/include/GamePlay/Player/Player.h
    ./game/Game/include/GamePlay/Scenery/Ground.h
    ./game/Game/include/GamePlay/Scenery/ISceneryObject.h
    ./game/Game/include/GamePlay/Scenery/Shield.h
    ./game/Game/include/GamePlay/UFO/UFO.h
    ./game/Game/include/Helpers/Bounds.h
    ./game/Game/include/Helpers/GameUtils.h
    ./game/Game/include/Helpers/SceneHelper.h
    ./game/Game/include/Helpers/Typewritter.h
    ./game/Game/include/Scenes/GameScene.h
    ./game/Game/include/Scenes/MenuScene.h
    ./game/Game/include/Scenes/SplashScene.h
    ./game/Game/include/Helpers/Storage.h
    ./game/Game/include/Helpers/Version.h

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


    ./lib/Cooper/Cooper.h
    ./lib/Cooper/include/Game/Entity.h
    ./lib/Cooper/include/Game/Game.h
    ./lib/Cooper/include/Game/RES.h
    ./lib/Cooper/include/Graphics/Graphics.h
    ./lib/Cooper/include/Graphics/TextEntity.h
    ./lib/Cooper/include/Graphics/TextureAtlas.h
    ./lib/Cooper/include/Graphics/TextureEntity.h
    ./lib/Cooper/include/Input/Input.h
    ./lib/Cooper/include/Log/Log.h
    ./lib/Cooper/include/Macros/Assert.h
    ./lib/Cooper/include/Macros/Disallow.h
    ./lib/Cooper/include/Macros/Macros.h
    ./lib/Cooper/include/Macros/private/MacrosHelpers.h
    ./lib/Cooper/include/Macros/Singleton.h
    ./lib/Cooper/include/Macros/SmartPointers.h
    ./lib/Cooper/include/Macros/Verify.h
    ./lib/Cooper/include/Math/Color.h
    ./lib/Cooper/include/Math/Constants.h
    ./lib/Cooper/include/Math/Math.h
    ./lib/Cooper/include/Math/Operations.h
    ./lib/Cooper/include/Math/Point.h
    ./lib/Cooper/include/Math/Rect.h
    ./lib/Cooper/include/Math/Tween.h
    ./lib/Cooper/include/Math/Vec2.h
    ./lib/Cooper/include/Memory/Memory.h
    ./lib/Cooper/include/Sound/Sound.h
    ./lib/Cooper/include/String/StringUtils.h
    ./lib/Cooper/include/Timer/Timer.h

    ./lib/Cooper/lib/CoreRandom/include/CoreRandom.h
    ./lib/Cooper/lib/CoreRandom/include/CoreRandom_Utils.h
    ./lib/Cooper/lib/CoreRandom/include/Random.h
    ./lib/Cooper/lib/CoreRandom/src/Random.cpp

    ./lib/Cooper/src/Game/Entity.cpp
    ./lib/Cooper/src/Game/Game.cpp
    ./lib/Cooper/src/Game/RES.cpp
    ./lib/Cooper/src/Graphics/Graphics.cpp
    ./lib/Cooper/src/Graphics/TextEntity.cpp
    ./lib/Cooper/src/Graphics/TextureAtlas.cpp
    ./lib/Cooper/src/Graphics/TextureEntity.cpp
    ./lib/Cooper/src/Input/Input.cpp
    ./lib/Cooper/src/Log/Log.cpp
    ./lib/Cooper/src/Macros/private/MacrosHelpers.cpp
    ./lib/Cooper/src/Sound/private/AudioLib.cpp
    ./lib/Cooper/src/Sound/private/AudioLib.h
    ./lib/Cooper/src/Sound/private/AudioValues.h
    ./lib/Cooper/src/Sound/private/emscripten/AudioValues.cpp
    ./lib/Cooper/src/Sound/private/SDL/AudioValues.cpp
    ./lib/Cooper/src/Sound/Sound.cpp
    ./lib/Cooper/src/String/StringUtils.cpp
    ./lib/Cooper/src/Timer/Timer.cpp
)


##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(CosmicIntruders ${SOURCE_FILES})
target_link_libraries(CosmicIntruders
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
