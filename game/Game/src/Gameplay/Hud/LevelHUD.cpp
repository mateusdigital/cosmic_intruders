//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : LevelHUD.cpp                                                  //
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
#include "Game/include/GamePlay/Hud/LevelHUD.h"
// CosmicIntruders.
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kTextFormat_Level       = "L E V E L - %d";
constexpr auto kDuration_AnimationStep = 1.0f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
LevelHUD::LevelHUD() :
    // Members.
    m_pLevelText(nullptr),
    m_pStartText(nullptr),
    m_animationIndex    (0),
    m_animationCompleted(false)
{
    for(int i = 0; i < m_animationTexts.size(); ++i)
        m_animationTexts[i] = nullptr;

    InitLevelTexts();
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void LevelHUD::Setup(int playerIndex, int levelIndex)
{
    //--------------------------------------------------------------------------
    // We don't need show anything....
    if(!GameManager::Instance()->LevelNeedsInitialization())
        return;

    //--------------------------------------------------------------------------
    // Set the new level text.
    m_pLevelText->Contents(
        Cooper::StringUtils::Format(kTextFormat_Level, levelIndex + 1)
    );

    //--------------------------------------------------------------------------
    // Update the array pointer to the player index.
    // So the animation will show the text for the player.
    m_animationTexts[1] = m_playerReadyTexts[playerIndex].get();
}

void LevelHUD::Start()
{
    //--------------------------------------------------------------------------
    // We need show the Level HUD this time - So configure its animation....
    if(GameManager::Instance()->LevelNeedsInitialization())
    {
        m_animationTimer.Reset();

        m_animationIndex     = 0;
        m_animationCompleted = false;
    }
    //--------------------------------------------------------------------------
    // No need to show the Level HUD - So let's mark it as completed.
    // This way the stuff that depends on its completion will run normaly...
    else
    {
        m_animationCompleted = true;
    }
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void LevelHUD::Update()
{
    if(m_animationCompleted)
        return;

    m_animationTimer.Update();
    if(m_animationTimer.TotalTime() >= kDuration_AnimationStep)
    {
        m_animationTimer.Reset();
        if(++m_animationIndex >= m_animationTexts.size())
            m_animationCompleted = true;
    }
}

void LevelHUD::Render()
{
    if(m_animationCompleted)
        return;

    COOPER_ASSERT(
        m_animationTexts[m_animationIndex],
        "m_animationTexts[%d} is null.",
        m_animationIndex
    );

    m_animationTexts[m_animationIndex]->Render();
}



//----------------------------------------------------------------------------//
// Text Functions                                                             //
//----------------------------------------------------------------------------//
void LevelHUD::InitLevelTexts()
{
    //--------------------------------------------------------------------------
    // To reduce verbosity...
    using namespace Cooper;

    //--------------------------------------------------------------------------
    // Cache the values since they're equal for all labels.
    const auto &path        = GameUtils::GameFontPath();
    const auto &size        = GameUtils::GameFontSize();
    const auto &screen_size = m_pGraphicsRef->GetScreenSize();
    const auto &color       = Cooper::Math::ColorWhite;

    //--------------------------------------------------------------------------
    // Start Text.
    m_pStartText = make_unique<TextEntity>(path, size, "S T A R T", color);
    m_pStartText->Position(screen_size * Vec2::Half());

    //--------------------------------------------------------------------------
    // Level Text.
    m_pLevelText = make_unique<TextEntity>(path, size, "", color);
    m_pLevelText->Position(screen_size * Vec2::Half());

    //--------------------------------------------------------------------------
    // Ready Texts.
    //   Message: "P L A Y E R < 1 > - G E T  R E A D Y"
    for(int i = 0; i < 2; ++i)
    {
        auto contents = StringUtils::Format(
            "P L A Y E R < %d >  -  G E T  R E A D Y",
            i+1
        );

        m_playerReadyTexts[i] = make_unique<TextEntity>(
            path,
            size,
            contents,
            color
        );
        m_playerReadyTexts[i]->Position(screen_size * Vec2::Half());
    }

    //--------------------------------------------------------------------------
    // Set the animation array.
    m_animationTexts[0] = m_pLevelText.get();
    m_animationTexts[1] = m_playerReadyTexts[0].get();
    m_animationTexts[2] = m_pStartText.get();
}
