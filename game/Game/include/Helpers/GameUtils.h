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

// class-like namespace.
namespace GameUtils
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    constexpr auto kDefaultLives = 3;

    constexpr auto kBaseAssetsPath = "./assets/";


    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
    void Init();


    //--------------------------------------------------------------------------
    // Random Number Functions                                                //
    //--------------------------------------------------------------------------
    int   RandomInt  (int min, int max);
    float RandomFloat();
    bool  RandomBool ();


    //------------------------------------------------------------------------//
    // Font Functions                                                         //
    //------------------------------------------------------------------------//
    constexpr inline int GameFontSize() { return 24; }

    inline const std::string& GameFontPath()
    {
        static auto path = Cooper::RES::Fullpath("Fonts/space_invaders.ttf");
        return path;
    }


    //------------------------------------------------------------------------//
    // Atlas Functions                                                        //
    //------------------------------------------------------------------------//
    inline const std::string& GameAtlasPath()
    {
        static auto path = Cooper::RES::Fullpath("Atlases/GameAtlas.ss");
        return path;
    }

    inline const std::string& SplashAtlasPath()
    {
        static auto path = Cooper::RES::Fullpath("Atlases/SplashAtlas.ss");
        return path;
    }


    //------------------------------------------------------------------------//
    // Sound Functions                                                        //
    //------------------------------------------------------------------------//
    inline std::string GetSoundsPath(const std::string &name)
    {
        static auto path = Cooper::RES::Fullpath("Sounds/");
        return path + name;
    }


    //------------------------------------------------------------------------//
    // Movement Bounds Functions                                              //
    //------------------------------------------------------------------------//
    const Bounds& MoveBoundsCannon   ();
    const Bounds& MoveBoundsLaser    ();
    const Bounds& MoveBoundsFormation();
    const Bounds& MoveBoundsUFO      ();


} // namespace GameUtils
} // namespace CosmicIntruders
