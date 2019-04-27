//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Storage.cpp (Emscripten)                                      //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#ifdef EMSCRIPTEN
// Header
#include "Game/include/Helpers/Storage.h"
// std
#include <stdio.h>
// Emscripten
#include <emscripten.h>
#include <emscripten/bind.h>
// Cooper
#include <Cooper/Cooper.h>

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kPath_Storage = "/persistent_data/score.txt";

int load_helper()
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

void save_helper(int value)
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

    //--------------------------------------------------------------------------
    // Synchronize the filesystem.
    EM_ASM(
        FS.syncfs(false, function (err) { assert(!err); });
    );
}



//----------------------------------------------------------------------------//
// Init                                                                       //
//----------------------------------------------------------------------------//
void Storage::Init()
{
    EM_ASM(
        //----------------------------------------------------------------------
        // Directory to hold our data.
        FS.mkdir('/persistent_data');
        FS.mount(IDBFS,{},'/persistent_data');

        //----------------------------------------------------------------------
        // To check if data is sync...
        Module.syncdone = 0;

        //----------------------------------------------------------------------
        // Synchronize.
        FS.syncfs(
            true,
            function(err) {
                assert(!err);
                Module.syncdone = 1;
            }
        );
    );
}


//----------------------------------------------------------------------------//
// Save / Load                                                                //
//----------------------------------------------------------------------------//
int  Storage::LoadHighScore()          { return load_helper(); }
void Storage::SaveHighScore(int value) { save_helper(value);   }

#endif //ifdef EMSCRIPTEN
