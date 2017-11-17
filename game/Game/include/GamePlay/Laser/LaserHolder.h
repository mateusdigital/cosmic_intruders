//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : LaserHolder.h                                                 //
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
// std
#include <vector>
#include <functional> //std::function
// Copper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/GamePlay/Laser/AlienLaser.h"
#include "Game/include/GamePlay/Laser/CannonLaser.h"


namespace CosmicIntruders {

class LaserHolder
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    // Typedefs.
    COOPER_SMART_PTRS_OF(LaserHolder);

    // Constants.
    static constexpr auto kAlienLasersMax  = 3;
    static constexpr auto kCannonLasersMax = 1;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    LaserHolder();


    //------------------------------------------------------------------------//
    // Lasers Functions                                                       //
    //------------------------------------------------------------------------//
public:
    CannonLaser* SpawnCannonLaser();
    AlienLaser * SpawnAlienLaser (bool powered);

    void KillAll();


    //------------------------------------------------------------------------//
    // Collections                                                            //
    //------------------------------------------------------------------------//
public:
    inline const std::vector<CannonLaser::SPtr>& CannonLasers()
    {
        return m_cannonLasers;
    }

    inline const std::vector<AlienLaser::SPtr>& AlienLasers()
    {
        return m_alienLasers;
    }


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update();
    void Render();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    std::vector<CannonLaser::SPtr> m_cannonLasers;
    std::vector<AlienLaser ::SPtr> m_alienLasers;

    int m_cannonLasersCount;
    int m_alienLasersCount;

}; // class LaserHolder
}  // namespace CosmicIntruders
