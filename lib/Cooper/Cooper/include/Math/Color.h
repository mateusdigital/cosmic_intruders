//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Color.h                                                       //
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

namespace Cooper { namespace Math {

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// B/W Colors.
constexpr SDL_Color ColorWhite = SDL_Color{255, 255, 255, 255};
constexpr SDL_Color ColorBlack = SDL_Color{  0,   0,   0, 255};

//------------------------------------------------------------------------------
// Primary Colors.
constexpr SDL_Color ColorRed   = SDL_Color{ 255,   0,   0, 255};
constexpr SDL_Color ColorGreen = SDL_Color{   0, 255,   0, 255};
constexpr SDL_Color ColorBlue  = SDL_Color{   0,   0, 255, 255};

//------------------------------------------------------------------------------
// Secondary Colors.
constexpr SDL_Color ColorCyan    = SDL_Color{  0, 255, 255, 255};
constexpr SDL_Color ColorMagenta = SDL_Color{255,   0, 255, 255};
constexpr SDL_Color ColorYellow  = SDL_Color{255, 255,   0, 255};


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
constexpr inline SDL_Color MakeColor(int r, int g, int b, int a = 255) noexcept
{
    return SDL_Color {
        Uint8(r),
        Uint8(g),
        Uint8(b),
        Uint8(a)
    };
}

} // namespace Math
} // namespace Cooper
