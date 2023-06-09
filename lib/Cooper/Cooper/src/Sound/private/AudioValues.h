//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AudioValues.h                                                  //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifndef EMSCRIPTEN

#pragma once

// SDL
#include <SDL.h>

namespace Cooper { namespace Private {

//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//
struct AudioValues
{
    Uint16 format;
    int    frequency;
    Uint8  channels;
    Uint16 samples;
};


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
AudioValues GetPlatformAudioValues();

} //namespace Cooper
} //namespace Private

#endif // EMSCRIPTEN