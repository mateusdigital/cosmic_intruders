//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ScoreHUD.h                                                    //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
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
