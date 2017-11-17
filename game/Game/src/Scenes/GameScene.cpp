//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameScene.cpp                                                 //
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
#include "Game/include/Scenes/GameScene.h"
// CosmicIntruders
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/Helpers/SceneHelper.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
GameScene::GameScene(bool multiplayer) :
    // Members
    m_pGameManagerRef(GameManager::Instance())
{
    //--------------------------------------------------------------------------
    // Set the background.
    m_pGraphicsRef->SetClearColor(Cooper::Math::ColorBlack);

    //--------------------------------------------------------------------------
    // Initialize the GameManager.
    m_pGameManagerRef->Init(multiplayer);
}

GameScene::~GameScene()
{
    //--------------------------------------------------------------------------
    // Let the Game Manager free the resources.
    m_pGameManagerRef->Shutdown();
    m_pGameManagerRef = nullptr;
}

//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void GameScene::Update()
{
    if(Cooper::Input::KeyDown(SDL_SCANCODE_ESCAPE))
    {
        SceneHelper::GoToMenuScene();
        return;
    }

    m_pGameManagerRef->Update();
    if(m_pGameManagerRef->IsGameOver())
    {
        SceneHelper::GoToMenuScene();
        return;
    }
}

void GameScene::Render()
{
    m_pGameManagerRef->Render();
}
