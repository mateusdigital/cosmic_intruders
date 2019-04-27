//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AliensLaserPowered.h                                          //
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
#include "Game/include/GamePlay/Laser/AlienLaser.h"

namespace CosmicIntruders {

class AlienLaserPowered
    : public AlienLaser
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(AlienLaserPowered);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     AlienLaserPowered();
    ~AlienLaserPowered() override = default;


    //------------------------------------------------------------------------//
    // Score                                                                  //
    //------------------------------------------------------------------------//
public:
    inline int  ScoreValue() const override { return   10; }
    inline bool IsPowered () const override { return true; }


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
    void UpdateAlive() override;
    void Render     () override;


    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
protected:
    void Init() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    Cooper::TextureEntity::UPtr m_pTexture;

    float m_timeToFlip;

    SDL_Rect m_aliveRect;
    SDL_Rect m_explodingRect;

}; // class AlienLaserNormal
}  // namespace CosmicIntruders
