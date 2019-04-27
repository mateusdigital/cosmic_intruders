//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Ground.cpp                                                    //
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
#include "Game/include/GamePlay/Scenery/Ground.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Colors
constexpr auto kPixel_NotHit = 0xFFFFFFFF; // White.
constexpr auto kPixel_Hit    = 0xFF000000; // Black.


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Ground::Ground(const Cooper::Vec2 &pos) :
    // Base
    ISceneryObject(
        pos,
        Cooper::Vec2(Cooper::Graphics::Instance()->GetScreenWidth(), 2),
        kPixel_NotHit,
        kPixel_Hit
    )
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Action Functions                                                           //
//----------------------------------------------------------------------------//
bool Ground::TakeHit(const SDL_Rect &rect)
{
    if(CheckOverralCollision(rect))
    {
        TakeHitHelper(rect);
        return true;
    }

    return false;
}
