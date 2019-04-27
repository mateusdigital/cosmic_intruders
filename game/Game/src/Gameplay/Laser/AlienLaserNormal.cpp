//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : AlienLaserNormal.cpp                                          //
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
#include "Game/include/GamePlay/Laser/AlienLaserNormal.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto kAtlasName_Alive      = "AlienLaser_Alive";
constexpr auto kAtlasName_Explode    = "AlienLaser_Explode";
constexpr auto kAtlasName_Horizontal = "AlienLaser_Horizontal";
//------------------------------------------------------------------------------
// Speed
constexpr auto kSpeed_Base = Cooper::Vec2(0, 300);
// Scaling
constexpr auto kScale_HorizontalTime = 4;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
AlienLaserNormal::AlienLaserNormal() :
    // Base.
    AlienLaser(kSpeed_Base)
{
    // Empty..
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void AlienLaserNormal::Reset()
{
    AlienLaser::Reset();

    m_pVertTexture->RenderRect(m_aliveRect);
    m_pHorzTexture->Visible(true);
}

void AlienLaserNormal::Explode()
{
    AlienLaser::Explode();

    m_pVertTexture->RenderRect(m_explodingRect);
    m_pHorzTexture->Visible(false);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void AlienLaserNormal::UpdateAlive()
{
    AlienLaser::UpdateAlive();

    //--------------------------------------------------------------------------
    // Makes the horizontal texture moves.
    auto delta = m_pGameRef->GetTimer()->DeltaTime() * kScale_HorizontalTime;
    m_horizontalMoveTime += delta;
    if(m_horizontalMoveTime > 1.0f)
        m_horizontalMoveTime = 0.0f;

    auto pos_y = (m_verticalTextureHeight * m_horizontalMoveTime)
                 - m_verticalTextureHalfHeight;

    m_pHorzTexture->Position(0, pos_y);

}

void AlienLaserNormal::Render()
{
    if(Dead())
        return;

    m_pVertTexture->Render();
    m_pHorzTexture->Render();
}


//----------------------------------------------------------------------------//
// Init Functions                                                             //
//----------------------------------------------------------------------------//
void AlienLaserNormal::Init()
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the textures.
    m_pVertTexture = p_atlas->Texture(kAtlasName_Alive     );
    m_pHorzTexture = p_atlas->Texture(kAtlasName_Horizontal);

    //--------------------------------------------------------------------------
    // Setup the Rectangles.
    m_aliveRect     = m_pVertTexture->RenderRect();
    m_explodingRect = p_atlas->Rectangle(kAtlasName_Explode);

    //--------------------------------------------------------------------------
    // Set the horizontal texture control values.
    m_horizontalMoveTime        = 0;
    m_verticalTextureHeight     = m_pVertTexture->Size().y;
    m_verticalTextureHalfHeight = m_verticalTextureHeight * 0.5f;

    //--------------------------------------------------------------------------
    // Setup hierarchy.
    m_pVertTexture->Parent(this);
    Size(m_pVertTexture->Size());

    m_pHorzTexture->Parent(this);
    m_pHorzTexture->Position(0, -m_verticalTextureHalfHeight);
}
