//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : ScoreHUD.h                                                    //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once
// std
#include <array>
// Cooper
#include "Cooper/Cooper.h"

namespace CosmicIntruders {

class ScoreHUD
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(ScoreHUD);

    //--------------------------------------------------------------------------
    // Just to make the code more sweet!
    enum class ScoreTypes { One, HI, Two };

    //--------------------------------------------------------------------------
    // Original game has the limitation of score - So we're following it here.
    static constexpr int kScoreMax = 9999;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     ScoreHUD(int score1, int score2);
    ~ScoreHUD() override = default;


    //------------------------------------------------------------------------//
    // Score Functions                                                        //
    //------------------------------------------------------------------------//
public:
    // Setter.
    void Score(int value, ScoreTypes scoreType);

    // Getter.
    inline int Score(ScoreTypes scoreType) const
    {
        return m_scores[int(scoreType)];
    }

    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Render() override;


    //------------------------------------------------------------------------//
    // Score Text Functions                                                   //
    //------------------------------------------------------------------------//
private:
    void InitScoreTexts();
    void UpdateScoreText(int scoreIndex);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    std::array<int,                      3> m_scores;
    std::array<Cooper::TextEntity::UPtr, 3> m_scoreLabels;
    std::array<Cooper::TextEntity::UPtr, 3> m_scoreValues;

}; //class ScoreHUD
}  //namespace CosmicIntruders
