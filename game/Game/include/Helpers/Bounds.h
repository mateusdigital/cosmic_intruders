//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Bounds.h                                                      //
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

namespace CosmicIntruders {

struct Bounds
{
    //------------------------------------------------------------------------//
    // Public Vars                                                            //
    //------------------------------------------------------------------------//
    Cooper::Vec2 min;
    Cooper::Vec2 max;

    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
    inline Bounds(float x1, float y1, float x2, float y2) :
        min(x1, y1),
        max(x2, y2)
    {
        // Empty...
    }

}; // struct Bounds
}  // namespace CosmicIntruders
