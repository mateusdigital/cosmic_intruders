//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Rect.h                                                        //
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
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr SDL_Rect RectZero = {0, 0, 0, 0};


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
constexpr inline SDL_Rect MakeRect(float x, float y, float w, float h) noexcept
{
    return SDL_Rect{ int(x), int(y), int(w), int(h) };
}

constexpr inline SDL_Rect MakeRect(int x, int y, int w, int h) noexcept
{
    return SDL_Rect{ x, y, w, h };
}

constexpr inline SDL_Rect MakeRect(const Vec2 &pos, const Vec2 &size) noexcept
{
    return SDL_Rect{ int(pos.x), int(pos.y), int(size.x), int(size.y) };
}

} // namespace Math
} // namespace Cooper
