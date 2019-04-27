//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Point.h                                                       //
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

//std
#include <cmath>
//SDL
#include <SDL.h>
//Cooper
#include "include/Math/Vec2.h"

namespace Cooper { namespace Math {

//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
constexpr inline SDL_Point MakePoint(float x, float y) noexcept
{
    return SDL_Point{ int(x), int(y) };
}

constexpr inline SDL_Point MakePoint(int x, int y) noexcept
{
    return SDL_Point{ x, y };
}

constexpr inline SDL_Point MakePoint(const Vec2 &v) noexcept
{
    return SDL_Point{ int(v.x), int(v.y) };
}

} // namespace Math
} // namespace Cooper
