//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Shield.h                                                      //
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
#include "Game/include/GamePlay/Scenery/Shield.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto kAtlasName_Shield = "Shield";
//------------------------------------------------------------------------------
// Colors.
constexpr auto kPixel_NotHit = 0x00000000;
constexpr auto kPixel_Hit    = 0xFF000000;
// Sizes.
constexpr auto kSize_Shield = Cooper::Vec2(80, 58);


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Shield::Shield(const Cooper::Vec2 &pos) :
    // Base
    ISceneryObject(pos, kSize_Shield, kPixel_NotHit, kPixel_Hit),
    // Members.
    //   Base Texture.
    m_pShieldTexture(nullptr)
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the Base Texture.
    m_pShieldTexture = p_atlas->Texture(kAtlasName_Shield);
    m_pShieldTexture->Position(pos);

    //--------------------------------------------------------------------------
    // Set the collision rect.
    SetCollisionRect(m_pShieldTexture->BoundingRect());
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Shield::Reset()
{
    ISceneryObject::Reset();

    //--------------------------------------------------------------------------
    // This makes the edges and bottom of the shield be already hit
    // so the collision mask will match the texture.
    static const auto hit_rects = {
        // Left side.
        Cooper::Math::MakeRect( 0,  0, 18,  4),
        Cooper::Math::MakeRect( 0,  4, 12,  4),
        Cooper::Math::MakeRect( 0,  8,  6,  4),

        // Bottom.
        Cooper::Math::MakeRect(20, 48, 38, 18),

        // Right side.
        Cooper::Math::MakeRect(64,  0, 18,  4),
        Cooper::Math::MakeRect(68,  4, 12,  4),
        Cooper::Math::MakeRect(72,  8, 12,  4),
    };


    auto padding_x = m_pShieldTexture->Position().x - m_pShieldTexture->Size().x * 0.5f ;
    auto padding_y = m_pShieldTexture->Position().y - m_pShieldTexture->Size().y * 0.5f ;
    for(auto rect : hit_rects)
    {
        rect.x += padding_x;
        rect.y += padding_y;
        TakeHitHelper(rect);
    }
}


bool Shield::TakeAlienHit(SDL_Rect hit_rect)
{
    if(!CheckOverralCollision(hit_rect))
        return false;

    return ISceneryObject::TakeHitHelper(hit_rect);
}

bool Shield::TakeHit(SDL_Rect hit_rect, int dmg, bool goingDown)
{
    if(!CheckOverralCollision(hit_rect))
        return false;

    MakeRectLocal(hit_rect);

    if(!IsBlockAlreadyHit(hit_rect))
    {
        InflateRect(hit_rect, dmg, goingDown);
        HitBlock(hit_rect);
        UpdateHitTexture();

        return true;
    }

    return false;
}


//----------------------------------------------------------------------------//
// Render                                                                     //
//----------------------------------------------------------------------------//
void Shield::Render()
{
    //--------------------------------------------------------------------------
    // Render the Shield Texture first, so the damage will be on top of it.
    m_pShieldTexture->Render();

    //--------------------------------------------------------------------------
    // Render the hit texture - It's managed by the base class.
    ISceneryObject::Render();
}


void Shield::InflateRect(SDL_Rect &rect, int dmg, bool goingDown)
{
    //COWTODO(n2omatt): This values are very arbitrary!
    // They do the job but isn't good at all :/
    if(goingDown)
    {
        rect.y += dmg / 2;
        rect.h += dmg;
        rect.x -= dmg;
        rect.w += dmg * 2;
    }
    else
    {
        rect.y -= dmg;
        rect.h += dmg;

        rect.x -= dmg / 2;
        rect.w += dmg;
    }
}
