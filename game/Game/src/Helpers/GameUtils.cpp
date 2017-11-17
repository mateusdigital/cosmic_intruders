//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameUtils.cpp                                                 //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Variables                                                                  //
//----------------------------------------------------------------------------//
namespace {
    std::unique_ptr<CoreRandom::Random> m_pCoreRandom;
    Cooper::Graphics*                   m_pGraphicsRef;
}


//----------------------------------------------------------------------------//
// Init                                                                       //
//----------------------------------------------------------------------------//
void GameUtils::Init()
{
    m_pGraphicsRef = Cooper::Graphics::Instance();

    m_pCoreRandom  = Cooper::make_unique<CoreRandom::Random>(
        CoreRandom::Random::kRandomSeed
    );
}


//----------------------------------------------------------------------------//
// Random Number Functions                                                    //
//----------------------------------------------------------------------------//
int GameUtils::RandomInt(int min, int max)
{
    return m_pCoreRandom->next(min, max);
}

float GameUtils::RandomFloat()
{
    //COWNOTE(n2omatt): Not a good way to implement random floats
    // but for now it's what I have! Really have no time :'(
    //COWTODO(n2omatt): Implement random floats.
    constexpr auto kMax = 10000;
    return RandomInt(0, kMax) / float(kMax);
}

bool GameUtils::RandomBool()
{
    return m_pCoreRandom->nextBool();
}

//----------------------------------------------------------------------------//
// Movement Bounds Functions                                                  //
//----------------------------------------------------------------------------//
const Bounds& GameUtils::MoveBoundsCannon()
{
    static auto bounds = Bounds(
         90,
        m_pGraphicsRef->GetScreenSize().y - 75,
        m_pGraphicsRef->GetScreenSize().x - 95,
        m_pGraphicsRef->GetScreenSize().y
    );

    return bounds;
}

const Bounds& GameUtils::MoveBoundsLaser()
{
    static auto bounds = Bounds(
         20,
         80,
        m_pGraphicsRef->GetScreenSize().x -  20,
        m_pGraphicsRef->GetScreenSize().y
    );

    return bounds;
}

const Bounds& GameUtils::MoveBoundsFormation()
{
    static auto bounds = Bounds(
        65,
        150,
        m_pGraphicsRef->GetScreenSize().x - 65,
        m_pGraphicsRef->GetScreenSize().y
    );

    return bounds;
}

const Bounds& GameUtils::MoveBoundsUFO()
{
    static auto bounds = Bounds(
        0,
        100,
        m_pGraphicsRef->GetScreenSize().x,
        200
    );

    return bounds;
}
