//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Ground.cpp                                                    //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
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
