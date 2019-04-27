//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : SceneHelper.cpp                                               //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "Game/include/Helpers/SceneHelper.h"
// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/Scenes/SplashScene.h"
#include "Game/include/Scenes/MenuScene.h"
#include "Game/include/Scenes/GameScene.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
template <typename T>
void go_to_scene()
{
    auto p_scene = Cooper::make_unique<T>();
    Cooper::Game::Instance()->SetRootEntity(std::move(p_scene));
}

//----------------------------------------------------------------------------//
// Transition Functions                                                       //
//----------------------------------------------------------------------------//
void SceneHelper::GoToSplashScene() { go_to_scene<SplashScene>(); }
void SceneHelper::GoToMenuScene  () { go_to_scene<MenuScene>  (); }

void SceneHelper::GoToGameScene(bool multiplayer)
{
    auto p_scene = Cooper::make_unique<GameScene>(multiplayer);
    Cooper::Game::Instance()->SetRootEntity(std::move(p_scene));
}
