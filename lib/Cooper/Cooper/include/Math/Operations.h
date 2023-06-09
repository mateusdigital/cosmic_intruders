//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Operations.h                                                  //
//  Project   : Cooper                                                        //
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
#include <cmath>
// SDL
#include <SDL.h>
// Cooper
#include "include/Math/Vec2.h"


namespace Cooper { namespace Math {

//----------------------------------------------------------------------------//
// Clamp                                                                      //
//----------------------------------------------------------------------------//
template <typename T>
T Clamp(const T &v, const T &_min, const T &_max)
{
    //COWTODO(n2omatt): We might use std::min, std::max.
    //  So search about perfomance (I saw something on CPPCon...)
    if(v < _min) return _min;
    if(v > _max) return _max;

    return v;
}


//----------------------------------------------------------------------------//
// Lerp                                                                       //
//----------------------------------------------------------------------------//
inline float Lerp(float s, float e, float t)
{
    //Precise formula from wikipedia:
    //  https://en.wikipedia.org/wiki/Linear_interpolation
    return (1.0f - t) * s + (t * e);
}

} // namespace Math
} // namespace Cooper
