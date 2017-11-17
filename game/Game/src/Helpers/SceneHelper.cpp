//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : SceneHelper.cpp                                               //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
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
