//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AliensLaser.cpp                                               //
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
#include "Game/include/GamePlay/Laser/AlienLaser.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Timer Durations.
constexpr float kDuration_Explosion = 0.5f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
AlienLaser::AlienLaser(const Cooper::Vec2 &speed) :
    // Base.
    ILaser(
        true,
        kDuration_Explosion,
        speed,
        GameUtils::MoveBoundsLaser())
{
    // Empty...
}
