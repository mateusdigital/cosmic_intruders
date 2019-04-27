//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : GameOverHUD.h                                                 //
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
// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/Helpers/Typewritter.h"

namespace CosmicIntruders {

class GameOverHUD
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(GameOverHUD);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    GameOverHUD();


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    inline void Start()
    {
        m_animationCompleted = false;
        m_delayCompleted     = false;
        m_pText->Start();
    }

    inline bool Completed() const {
        return m_animationCompleted && m_delayCompleted;
    }


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;
    void Render() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    bool m_animationCompleted;
    bool m_delayCompleted;

    Typewritter::UPtr    m_pText;
    Cooper::Tween<float> m_delay;

}; // class LevelHUD
}  // namespace CosmicIntruders
