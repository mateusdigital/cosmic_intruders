//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AliensLaser.h                                                 //
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
#include "Game/include/GamePlay/Laser/ILaser.h"

namespace CosmicIntruders {

class AlienLaser
    : public ILaser
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(AlienLaser);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     explicit AlienLaser(const Cooper::Vec2 &speed);
    ~AlienLaser() override = default;


    //------------------------------------------------------------------------//
    // Score                                                                  //
    //------------------------------------------------------------------------//
public:
    virtual int  ScoreValue() const = 0;
    virtual bool IsPowered () const = 0;

    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
public:
    virtual void Init() = 0;

}; // class AlienLaserNormal
}  // namespace CosmicIntruders
