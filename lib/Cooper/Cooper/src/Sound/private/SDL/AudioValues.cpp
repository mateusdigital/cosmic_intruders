//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AudioValues.cpp (SDL)                                         //
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

// Header
#include "src/Sound/private/AudioValues.h"

// Usings
using namespace Cooper;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
Private::AudioValues Private::GetPlatformAudioValues()
{
    return AudioValues {
        /* .format    = */ AUDIO_F32,
        /* .frequency = */ 44100,
        /* .channels  = */ 2,
        /* .samples   = */ 512,
    };
}

#endif // EMSCRIPTEN
