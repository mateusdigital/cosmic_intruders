//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ScoreHUD.cpp                                                  //
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
#include "Game/include/GamePlay/Hud/ScoreHUD.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/Helpers/Storage.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kString_1  = "S C O R E < 1 >";
constexpr auto kString_HI = "H I  -  S C O R E ";
constexpr auto kString_2  = "S C O R E < 2 >";


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
ScoreHUD::ScoreHUD(int score1, int score2)
{
    auto high_score = Storage::LoadHighScore();

    //--------------------------------------------------------------------------
    // Initialize the Score Values.
    m_scores[0] = score1;
    m_scores[1] = high_score;
    m_scores[2] = score2;

    //--------------------------------------------------------------------------
    // Initialize the Text Entities.
    InitScoreTexts();
}


//----------------------------------------------------------------------------//
// Score Functions                                                            //
//----------------------------------------------------------------------------//
// Setter
void ScoreHUD::Score(int value, ScoreTypes scoreType)
{
    auto score_index = int(scoreType);
    m_scores[score_index] = value;

    auto score_hi_index = int(ScoreTypes::HI);
    if(value > m_scores[score_hi_index])
    {
        m_scores[score_hi_index] = value;
        UpdateScoreText(score_hi_index);
        Storage::SaveHighScore(value);
    }

    UpdateScoreText(score_index);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void ScoreHUD::Render()
{
    // Labels.
    for(int i = 0; i < 3; ++i)
    {
        m_scoreLabels[i]->Render();
        m_scoreValues[i]->Render();
    }
}


//----------------------------------------------------------------------------//
// Score Text Functions                                                       //
//----------------------------------------------------------------------------//
void ScoreHUD::InitScoreTexts()
{
    //--------------------------------------------------------------------------
    // To reduce verbosity...
    using namespace Cooper;

    constexpr int _1 = 0;
    constexpr int _2 = 2;
    constexpr int HI = 1;

    //--------------------------------------------------------------------------
    // Cache the values since they're equal for all labels.
    const auto &path        = GameUtils::GameFontPath();
    const auto &size        = GameUtils::GameFontSize();
    const auto &screen_size = m_pGraphicsRef->GetScreenSize();
    const auto &color       = Cooper::Math::ColorWhite;

    //--------------------------------------------------------------------------
    // Score Labels.
    m_scoreLabels[_1] = make_unique<TextEntity>(path, size, kString_1 , color);
    m_scoreLabels[HI] = make_unique<TextEntity>(path, size, kString_HI, color);
    m_scoreLabels[_2] = make_unique<TextEntity>(path, size, kString_2 , color);

    auto hi_score_size = m_scoreLabels[HI]->Size();

    //  Setup the hierarchy.
    m_scoreLabels[_1]->Parent(m_scoreLabels[HI].get());
    m_scoreLabels[_2]->Parent(m_scoreLabels[HI].get());

    //  Setup the origins.
    m_scoreLabels[_1]->Origin(Vec2(1.0f, 0.5f)); //Right.
    m_scoreLabels[_2]->Origin(Vec2(0.0f, 0.5f)); //Left.

    //  Setup the positions.
    m_scoreLabels[_1]->Position(Vec2(-30 - hi_score_size.x * 0.5f,0));
    m_scoreLabels[_2]->Position(Vec2(+30 + hi_score_size.x * 0.5f,0));
    m_scoreLabels[HI]->Position(screen_size * Vec2(0.5, 0.05));


    //--------------------------------------------------------------------------
    // Score Values.
    m_scoreValues[_1] = make_unique<TextEntity>(path, size, "0000", color);
    m_scoreValues[HI] = make_unique<TextEntity>(path, size, "0000", color);
    m_scoreValues[_2] = make_unique<TextEntity>(path, size, "0000", color);

    //  Setup the hierarchy.
    m_scoreValues[_1]->Parent(m_scoreLabels[_1].get());
    m_scoreValues[HI]->Parent(m_scoreLabels[HI].get());
    m_scoreValues[_2]->Parent(m_scoreLabels[_2].get());

    //  Setup the positions.
    m_scoreValues[_1]->Position(m_scoreLabels[_1]->Size() * Vec2(-0.5, 0) +  Vec2(0, 40));
    m_scoreValues[HI]->Position(m_scoreLabels[HI]->Size() * Vec2(0.0, 0)  +  Vec2(0, 40));
    m_scoreValues[_2]->Position(m_scoreLabels[_2]->Size() * Vec2(0.5, 0)  +  Vec2(0, 40));


    //--------------------------------------------------------------------------
    // Update all Texts...
    UpdateScoreText(_1);
    UpdateScoreText(HI);
    UpdateScoreText(_2);
}

void ScoreHUD::UpdateScoreText(int scoreIndex)
{
    auto value = m_scores[scoreIndex];
    if(value > kScoreMax)
        value = kScoreMax;

    m_scoreValues[scoreIndex]->Contents(
        Cooper::StringUtils::Format("%04d", value)
    );
}
