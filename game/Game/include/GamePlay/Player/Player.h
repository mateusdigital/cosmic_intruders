//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Player.h                                                      //
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
#include <functional> //std::function
// Cooper
#include "Cooper/Cooper.h"
// Cosmic Intruders
#include "Game/include/GamePlay/Level/Level.h"

namespace CosmicIntruders {

class Player
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    // Typedefs.
    COOPER_SMART_PTRS_OF(Player);

    // Constants.
    static const int kIndex_One;
    static const int kIndex_Two;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Player(int index);


    //------------------------------------------------------------------------//
    // Index Functions                                                        //
    //------------------------------------------------------------------------//
public:
    inline int Index() { return m_index; }


    //------------------------------------------------------------------------//
    // Lives Functions                                                        //
    //------------------------------------------------------------------------//
public:
    inline int  Lives     () const { return m_lives; }
    inline void AddLive   ()       { ++m_lives;      }
    inline void RemoveLive()       { --m_lives ;     }

    inline bool GameOver() const { return m_lives == 0; }


    //------------------------------------------------------------------------//
    // Score Functions                                                        //
    //------------------------------------------------------------------------//
public:
    inline int  CurrentScore() const { return m_score;    }
    inline void AddScore(int amount) { m_score += amount; }


    //------------------------------------------------------------------------//
    // Level Functions                                                        //
    //------------------------------------------------------------------------//
public:
    inline int  CurrentLevel() const { return m_levelIndex; };

    inline void AddLevel()
    {
        ++m_levelIndex;
        m_pLevel->Setup();
    }


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void StartLevel();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    inline void Update() { m_pLevel->Update(); }
    inline void Render() { m_pLevel->Render(); }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Control.
    int m_index;
    int m_levelIndex;
    int m_lives;
    int m_score;

    // Objects.
    Level::UPtr m_pLevel;

}; // class Player
}  // namespace CosmicIntruders
