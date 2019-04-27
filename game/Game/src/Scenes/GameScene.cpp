//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : GameScene.cpp                                                 //
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
