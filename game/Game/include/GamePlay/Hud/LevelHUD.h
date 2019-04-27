//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : LevelHUD.h                                                    //
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
//Cooper
#include "Cooper/Cooper.h"

namespace CosmicIntruders {

class LevelHUD
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(LevelHUD);

    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    LevelHUD();


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Setup(int playerIndex, int levelIndex);

    void Start();

    bool Completed() const { return m_animationCompleted; }


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;
    void Render() override;


    //------------------------------------------------------------------------//
    // Text Functions                                                         //
    //------------------------------------------------------------------------//
private:
    void InitLevelTexts();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Texts.
    std::array<Cooper::TextEntity::UPtr, 2> m_playerReadyTexts;
    Cooper::TextEntity::UPtr                m_pLevelText;
    Cooper::TextEntity::UPtr                m_pStartText;

    // Animation.
    std::array<Cooper::TextEntity*, 3> m_animationTexts; //Weak references.
    int           m_animationIndex;
    bool          m_animationCompleted;
    Cooper::Timer m_animationTimer;

}; // class LevelHUD
}  // namespace CosmicIntruders
