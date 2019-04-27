//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : LaserHolder.cpp                                               //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "Game/include/GamePlay/Laser/LaserHolder.h"
// std
#include <algorithm> //std::find_if
// CosmicIntruders
#include "Game/include/GamePlay/Laser/AlienLaserNormal.h"
#include "Game/include/GamePlay/Laser/AlienLaserPowered.h"

//Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
LaserHolder::LaserHolder() :
    // Members
    m_cannonLasersCount(0),
    m_alienLasersCount (0)
{
    // Play nice with memory.
    m_cannonLasers.reserve(kCannonLasersMax);
    m_alienLasers .reserve(kAlienLasersMax );
}


//----------------------------------------------------------------------------//
// Lasers Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Cannon.
CannonLaser* LaserHolder::SpawnCannonLaser()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(
        m_cannonLasersCount >= 0 && m_cannonLasersCount <= kCannonLasersMax,
        "Invalid Cannon Laser Count: %d",
        m_cannonLasersCount
    );

    //--------------------------------------------------------------------------
    // Check if we already reach the shot limit.
    if(m_cannonLasersCount >= kCannonLasersMax)
        return nullptr;

    //--------------------------------------------------------------------------
    // Update the lasers count.
    ++m_cannonLasersCount;

    //--------------------------------------------------------------------------
    // Find the first laser available and return it.
    auto it = std::find_if(
        std::begin(m_cannonLasers),
        std::end  (m_cannonLasers),
        [](CannonLaser::SPtr pLaser){
            return pLaser->Dead();
        }
    );

    if(it != std::end(m_cannonLasers))
        return it->get();

    //--------------------------------------------------------------------------
    // No lasers available - Spawn a brand new one.
    auto p_laser = std::make_shared<CannonLaser>();
    p_laser->OnDeath([this](){
        --m_cannonLasersCount;
    });

    m_cannonLasers.push_back(p_laser);

    return p_laser.get();
}

//------------------------------------------------------------------------------
// Alien.
AlienLaser* LaserHolder::SpawnAlienLaser(bool powered)
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(
        m_alienLasersCount >= 0 && m_alienLasersCount<= kAlienLasersMax,
        "Invalid Aliens Laser Count: %d",
        m_alienLasersCount
    );

    //--------------------------------------------------------------------------
    // Check if we already reach the shot limit.
    if(m_alienLasersCount >= kAlienLasersMax)
        return nullptr;

    //--------------------------------------------------------------------------
    // Update the lasers count.
    ++m_alienLasersCount;

    //--------------------------------------------------------------------------
    // Find the first laser available and return it.
    auto it = std::find_if(
        std::begin(m_alienLasers),
        std::end  (m_alienLasers),
        [=](AlienLaser::SPtr pLaser){
            return pLaser->Dead() && (pLaser->IsPowered() == powered);
        }
    );

    if(it != std::end(m_alienLasers))
        return it->get();

    //--------------------------------------------------------------------------
    // No lasers available - Spawn a brand new one.
    AlienLaser::SPtr p_laser = nullptr;
    if(powered)
        p_laser = std::make_shared<AlienLaserPowered>();
    else
        p_laser = std::make_shared<AlienLaserNormal>();

    p_laser->Init();
    p_laser->OnDeath([this](){
         --m_alienLasersCount;
    });

    m_alienLasers.push_back(p_laser);

    return p_laser.get();
}


void LaserHolder::KillAll()
{
    // Cannon.
    for(const auto &p_laser : m_cannonLasers)
        p_laser->Kill();

    // Alien.
    for(const auto &p_laser : m_alienLasers)
        p_laser->Kill();
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void LaserHolder::Update()
{
    // Cannon.
    for(const auto &p_laser : m_cannonLasers)
        p_laser->Update();

    // Alien.
    for(const auto &p_laser : m_alienLasers)
        p_laser->Update();
}

void LaserHolder::Render()
{
    // Cannon.
    for(const auto &p_laser : m_cannonLasers)
        p_laser->Render();

    // Alien.
    for(const auto &p_laser : m_alienLasers)
        p_laser->Render();
}
