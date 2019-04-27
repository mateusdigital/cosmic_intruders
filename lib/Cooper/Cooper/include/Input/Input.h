//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Input.h                                                       //
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
#include <string>
// SDL
#include <SDL.h>
// Cooper
#include "include/Macros/Macros.h"
#include "include/Math/Math.h"

namespace Cooper {

// "class-like" namespace.
namespace Input
{
    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                    //
    //------------------------------------------------------------------------//
    void Init    ();
    void Shutdown();

    bool Initialized();

    void Update    ();
    void PostUpdate();


    //------------------------------------------------------------------------//
    // Keyboard Functions                                                     //
    //------------------------------------------------------------------------//
    //--------------------------------------------------------------------------
    // Check if there is any keyboard input on this frame.
    bool HasKeyboardInput();

    //--------------------------------------------------------------------------
    // True every time that key is down.
    bool KeyDown(SDL_Scancode key);

    //--------------------------------------------------------------------------
    // True only on the frame that key is down.
    bool KeyPress(SDL_Scancode key);

    //--------------------------------------------------------------------------
    // True only on the frame that key is up.
    bool KeyRelease(SDL_Scancode key);


    //------------------------------------------------------------------------//
    // Mouse Functions                                                        //
    //------------------------------------------------------------------------//
    //--------------------------------------------------------------------------
    // Check if there is any mouse input on this frame.
    bool HasMouseInput();

    //--------------------------------------------------------------------------
    // The position of mouse - Relative to the screen.
    const Vec2& MousePosition();

    //COWTODO(n2omatt): Should we use a enumeration to better reading?
    //--------------------------------------------------------------------------
    // True every time that button is down.
    bool MouseButtonDown(int button);

    //--------------------------------------------------------------------------
    // True only on the frame that button is down.
    bool MouseButtonPress(int button);

    //--------------------------------------------------------------------------
    // True only on the frame that button is up.
    bool MouseButtonRelease(int button);

} //namespace Input
} //namespace Cooper
