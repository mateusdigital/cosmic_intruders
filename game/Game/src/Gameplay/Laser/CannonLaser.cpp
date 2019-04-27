//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : CannonLaser.cpp                                               //
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
#include "Game/include/GamePlay/Laser/CannonLaser.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Timer Durations.
constexpr float kDuration_Explosion = 0.25f;
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto  kAtlasName_Alive   = "CannonLaser_Alive";
constexpr auto  kAtlasName_Explode = "CannonLaser_Explode";
//------------------------------------------------------------------------------
// Speed
constexpr auto kSpeed_Base = Cooper::Vec2(0, -700);


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
CannonLaser::CannonLaser() :
    // Base.
    ILaser(
        true,
        kDuration_Explosion,
        kSpeed_Base,
        GameUtils::MoveBoundsLaser()
    )
{
    Init();
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void CannonLaser::Reset()
{
    ILaser::Reset();
    m_pTexture->RenderRect(m_aliveRect);
}

void CannonLaser::Explode()
{
    ILaser::Explode();
    m_pTexture->RenderRect(m_explodingRect);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void CannonLaser::Render()
{
    if(!Dead())
        m_pTexture->Render();
}


//----------------------------------------------------------------------------//
// Init Functions                                                             //
//----------------------------------------------------------------------------//
void CannonLaser::Init()
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Get the texture with the alive render rect since it'll be default.
    //    But we need to set the alive rect as well since we only load
    //    one time but possible use them a lot.
    m_pTexture  = p_atlas->Texture(kAtlasName_Alive);
    m_aliveRect = m_pTexture->RenderRect();

    //--------------------------------------------------------------------------
    // Load the exploding info too.
    m_explodingRect = p_atlas->Rectangle(kAtlasName_Explode);

    //--------------------------------------------------------------------------
    // Setup hierarchy.
    m_pTexture->Parent(this);
    Size(m_pTexture->Size());
}
