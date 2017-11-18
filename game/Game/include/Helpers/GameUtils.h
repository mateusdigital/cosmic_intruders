//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameUtils.h                                                   //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
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
