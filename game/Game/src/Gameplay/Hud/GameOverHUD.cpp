//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : GameOverHUD.cpp                                               //
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
#include "Game/include/GamePlay/Hud/GameOverHUD.h"
// CosmicIntruders.
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/GamePlay/GameManager/GameManager.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kText_GameOver  = "G A M E  O V E R";
constexpr auto kDuration_Animation   = 1.5f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
GameOverHUD::GameOverHUD() :
    // Members.
    m_animationCompleted(false),
    m_delayCompleted    (false),
    m_pText(nullptr)
{
    //--------------------------------------------------------------------------
    // Create Typewriter.
     m_pText = Cooper::make_unique<Typewritter>(
        kText_GameOver,
        GameUtils::GameFontPath(),
        GameUtils::GameFontSize()
    );

    //--------------------------------------------------------------------------
    // Set properties.
    auto screen_size = m_pGraphicsRef->GetScreenSize();
    m_pText->Position(screen_size * 0.5f);
    m_pText->Color   (Cooper::Math::ColorWhite);

    //--------------------------------------------------------------------------
    // Configure.
    m_pText->Configure(
        kDuration_Animation,
        [this](){
            m_delay.Start();
            m_animationCompleted = true;
        }
    );

    //--------------------------------------------------------------------------
    // Create the delay tween.
    //   This will let the Game Over text appears a little more.
    m_delay.From(0).To(1).In(1).OnFinish([this](){ m_delayCompleted = true; });
}

//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void GameOverHUD::Update()
{
    m_pText->Update();
    if(m_animationCompleted)
        m_delay.Update(m_pGameRef->GetTimer()->DeltaTime());
}

void GameOverHUD::Render()
{
    m_pText->Render();
}
