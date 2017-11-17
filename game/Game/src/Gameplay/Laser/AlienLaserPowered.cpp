//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : AlienLaserPowered.cpp                                         //
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
#include "Game/include/GamePlay/Laser/AlienLaserPowered.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto kAtlasName_Alive   = "AlienLaserPowered_Alive";
constexpr auto kAtlasName_Explode = "AlienLaser_Explode";
//------------------------------------------------------------------------------
// Speed
constexpr auto kSpeed_Base = Cooper::Vec2(0, 400);
//------------------------------------------------------------------------------
// Durations
constexpr auto kDuration_Flip = 0.15f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
AlienLaserPowered::AlienLaserPowered() :
    // Base.
    AlienLaser(kSpeed_Base)
{
    // Empty..
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void AlienLaserPowered::Reset()
{
    AlienLaser::Reset();

    m_pTexture->RenderRect(m_aliveRect);
    m_timeToFlip = kDuration_Flip;
}

void AlienLaserPowered::Explode()
{
    AlienLaser::Explode();

    m_pTexture->RenderRect(m_explodingRect);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void AlienLaserPowered::UpdateAlive()
{
    AlienLaser::UpdateAlive();

    //--------------------------------------------------------------------------
    // This will make the Texture Flips...
    m_timeToFlip -= m_pGameRef->GetTimer()->DeltaTime();
    if(m_timeToFlip <= 0)
    {
        m_pTexture->FlipX(!m_pTexture->FlipX());
        m_timeToFlip = kDuration_Flip;
    }
}

void AlienLaserPowered::Render()
{
    if(Dead())
        return;

    m_pTexture->Render();
}


//----------------------------------------------------------------------------//
// Init Functions                                                             //
//----------------------------------------------------------------------------//
void AlienLaserPowered::Init()
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the textures.
    m_pTexture = p_atlas->Texture(kAtlasName_Alive);

    //--------------------------------------------------------------------------
    // Setup the Rectangles.
    m_aliveRect     = m_pTexture->RenderRect();
    m_explodingRect = p_atlas->Rectangle(kAtlasName_Explode);

    //--------------------------------------------------------------------------
    // Setup hierarchy.
    m_pTexture->Parent(this);
    Size(m_pTexture->Size());
}

