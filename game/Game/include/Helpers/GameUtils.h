//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : GameUtils.h                                                   //
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
// CosmicIntruders
#include "Game/include/Helpers/Bounds.h"

namespace CosmicIntruders {

struct GameUtils
{
    COOPER_DISALLOW_EVERYTHING(GameUtils);

    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    static const int   kDefaultLives;
    static const char* kBaseAssetsPath;
    static const char* kWindowCaption;


    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
    static void Init();


    //--------------------------------------------------------------------------
    // Random Number Functions                                                //
    //--------------------------------------------------------------------------
    static int   RandomInt  (int min, int max);
    static float RandomFloat();
    static bool  RandomBool ();


    //------------------------------------------------------------------------//
    // Font Functions                                                         //
    //------------------------------------------------------------------------//
    static constexpr inline int GameFontSize() { return 24; }

    static inline const std::string& GameFontPath()
    {
        static auto path = Cooper::RES::Fullpath("Fonts/space_invaders.ttf");
        return path;
    }


    //------------------------------------------------------------------------//
    // Atlas Functions                                                        //
    //------------------------------------------------------------------------//
    static inline const std::string& GameAtlasPath()
    {
        static auto path = Cooper::RES::Fullpath("Atlases/GameAtlas.ss");
        return path;
    }

    static inline const std::string& SplashAtlasPath()
    {
        static auto path = Cooper::RES::Fullpath("Atlases/SplashAtlas.ss");
        return path;
    }


    //------------------------------------------------------------------------//
    // Sound Functions                                                        //
    //------------------------------------------------------------------------//
    static inline std::string GetSoundsPath(const std::string &name)
    {
        static auto path = Cooper::RES::Fullpath("Sounds/");
        return path + name;
    }


    //------------------------------------------------------------------------//
    // Movement Bounds Functions                                              //
    //------------------------------------------------------------------------//
    static const Bounds& MoveBoundsCannon   ();
    static const Bounds& MoveBoundsLaser    ();
    static const Bounds& MoveBoundsFormation();
    static const Bounds& MoveBoundsUFO      ();


}; // struct GameUtils
}  // namespace CosmicIntruders
