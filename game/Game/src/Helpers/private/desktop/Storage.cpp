//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Storage.cpp                                                   //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//


#ifndef EMSCRIPTEN
// Header
#include "Game/include/Helpers/Storage.h"
// std
#include <cstdio>
// Cooper
#include <Cooper/Cooper.h>

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kPath_Storage = "./score.txt";


//----------------------------------------------------------------------------//
// Init                                                                       //
//----------------------------------------------------------------------------//
void Storage::Init()
{
    //Empty on desktop...
}


//----------------------------------------------------------------------------//
// Save / Load                                                                //
//----------------------------------------------------------------------------//
int Storage::LoadHighScore()
{
    //--------------------------------------------------------------------------
    // Try to open the file, if it doesn't exists just returns.
    auto p_file = fopen(kPath_Storage, "r");
    if(!p_file) // No high scores.
        return 0;

    //--------------------------------------------------------------------------
    // File exists, so we have a high score - Read it.
    int value;

    fscanf(p_file, "%d", &value);
    fclose(p_file);
    p_file = nullptr;

    return value;
}

void Storage::SaveHighScore(int value)
{
    //--------------------------------------------------------------------------
    // Try to open the file, if it doesn't exists just returns.
    auto p_file = fopen(kPath_Storage, "w");
    if(!p_file) // Error occurred - Ignore it.
    {
        Cooper::Log::E(
            "Failed to save score: %d - Path: %s",
            value,
            kPath_Storage
        );

        return;
    }

    fprintf(p_file, "%d", value);
    fclose(p_file);
}

#endif //ifndef EMSCRIPTEN
