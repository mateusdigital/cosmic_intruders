//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : LivesHUD.cpp                                                  //
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
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/GamePlay/Player/Player.h"
#include "Game/include/GamePlay/Hud/LivesHUD.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kAtlasName_Cannon = "Cannon_Alive";
constexpr auto kRelative_PosX   = 0.05f;
constexpr auto kRelative_PosY   = 0.97f;

constexpr auto kPadding_CannonX = 50;
constexpr auto kPadding_CannonY = -3;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
LivesHUD::LivesHUD(bool multiplayer) :
    m_multiplayerGame(multiplayer)
{
    Init();
}


//----------------------------------------------------------------------------//
// Lives Functions                                                            //
//----------------------------------------------------------------------------//
// Setter
void LivesHUD::Lives(int amount, int playerIndex)
{
    //COWNOTE(n2omatt): I know that this is junk.. but I'm in hurry...

    if(playerIndex == Player::kIndex_One)
    {
        m_pPlayer1Text->Contents(std::to_string(amount));

        for(int i = 0; i < kMaxVisibleCannons; ++i)
            m_player1Cannons[i]->Visible(i < amount -1);
    }
    else
    {
        m_pPlayer2Text->Contents(std::to_string(amount));

        for(int i = 0;  i < kMaxVisibleCannons; ++i)
            m_player2Cannons[i]->Visible(i < amount -1);
    }
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void LivesHUD::Render()
{
    //--------------------------------------------------------------------------
    // Player 1.
    m_pPlayer1Text->Render();

    for(const auto &p_cannon : m_player1Cannons)
        p_cannon->Render();


    //--------------------------------------------------------------------------
    // We're not in a multiplayer game.
    //  So don't spend cycles rendering stuff for player 2.
    if(!m_multiplayerGame)
        return;

    //--------------------------------------------------------------------------
    // Player 2.
    m_pPlayer2Text->Render();

    for(const auto &p_cannon : m_player2Cannons)
        p_cannon->Render();
}


//----------------------------------------------------------------------------//
// Lives Text Functions                                                       //
//----------------------------------------------------------------------------//
void LivesHUD::Init()
{
    //--------------------------------------------------------------------------
    // To reduce verbosity...
    using namespace Cooper;

    //--------------------------------------------------------------------------
    //  Cache the values since they're equal for all labels.
    const auto &path  = GameUtils::GameFontPath();
    const auto &size  = GameUtils::GameFontSize();
    const auto &color = Cooper::Math::ColorWhite;

    const auto &screen_size = m_pGraphicsRef->GetScreenSize();
    auto        p_atlas     = RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    //  Player 1.
    m_pPlayer1Text = make_unique<TextEntity>(
        path,
        size,
        std::to_string(GameUtils::kDefaultLives),
        color
    );
    m_pPlayer1Text->Position(screen_size * Vec2(kRelative_PosX, kRelative_PosY));

    for(int i = 0; i < kMaxVisibleCannons; ++i)
    {
        auto p_cannon = p_atlas->Texture(kAtlasName_Cannon);
        p_cannon->Parent(m_pPlayer1Text.get());
        p_cannon->Position(Vec2(kPadding_CannonX * (i+1), kPadding_CannonY));

        m_player1Cannons[i] = std::move(p_cannon);
    }

    //--------------------------------------------------------------------------
    // We're not in a multiplayer game.
    //  So don't spend cycles rendering stuff for player 2.
    if(!m_multiplayerGame)
        return;

    //--------------------------------------------------------------------------
    //  Player 2.
    m_pPlayer2Text = make_unique<TextEntity>(
        path,
        size,
        std::to_string(GameUtils::kDefaultLives),
        color
    );
    m_pPlayer2Text->Position(
        screen_size * Vec2(1.0f - kRelative_PosX, kRelative_PosY)
    );

    for(int i = 0; i < kMaxVisibleCannons; ++i)
    {
        auto p_cannon = p_atlas->Texture(kAtlasName_Cannon);
        p_cannon->Parent(m_pPlayer2Text.get());
        p_cannon->Position(Vec2(-kPadding_CannonX * (i+1), kPadding_CannonY));

        m_player2Cannons[i] = std::move(p_cannon);
    }
}
