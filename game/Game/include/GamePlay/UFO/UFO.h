//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : UFO.h                                                         //
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
#include "Game/include/GamePlay/GamePlayObject/IGamePlayObject.h"


namespace CosmicIntruders {

class UFO
    : public IGamePlayObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(UFO);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    UFO();


    //------------------------------------------------------------------------//
    // Type / Value Functions                                                 //
    //------------------------------------------------------------------------//
public:
    inline int ScoreValue() const { return m_currScore; }

private:
    void CalculateAppearSettings();


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Reset  () override;
    void Explode() override;


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    // Update States.
    void UpdateAlive    () override;
    void UpdateExploding() override;
    void UpdateDead     () override;

    // Render.
    void Render() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Display.
    Cooper::TextureEntity::UPtr m_pTexture;
    Cooper::TextEntity   ::UPtr m_pScoreText;

    SDL_Rect m_aliveRect;
    SDL_Rect m_explosionRect;
    float    m_explosionTime;
    float    m_resetTime;
    int      m_currScore;

    Cooper::Vec2 m_moveVector;
}; // class UFO
}  // namespace CosmicIntruders
