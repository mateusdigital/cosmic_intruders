//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : ISceneryObject.cpp                                            //
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
#include "Game/include/GamePlay/Scenery/ISceneryObject.h"
// std
#include <cstring>
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
ISceneryObject::ISceneryObject(
    const Cooper::Vec2 &pos,
    const Cooper::Vec2 &hitTextureSize,
    Uint32              normalColor,
    Uint32              hitColor) :
    // Members.
    m_normalColor(normalColor),
    m_hitColor   (   hitColor),
    //   Unmanaged Resources.
    m_pHitTexture(nullptr),
    m_pPixelsArr (nullptr),
    //   Weak References.
    m_pGraphicsRef(Cooper::Graphics::Instance())
{
    //--------------------------------------------------------------------------
    // Setup the Rects.
    m_localRect = Cooper::Math::MakeRect(
        Cooper::Vec2::Zero(),
        hitTextureSize
    );

    m_collisionRect = Cooper::Math::MakeRect(
        pos,
        hitTextureSize
    );

    //--------------------------------------------------------------------------
    // Create the Unmanaged Resources.
    CreateResources();
}

ISceneryObject::~ISceneryObject()
{
    DestroyResources();
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void ISceneryObject::Reset()
{
    //--------------------------------------------------------------------------
    // To make the ISceneryObject goes back to the default state is just
    // reset the pixels that controls the hit texture.
    ResetPixels     ();
    UpdateHitTexture();
}


// Helpers
bool ISceneryObject::TakeHitHelper(SDL_Rect hit_rect)
{
    MakeRectLocal(hit_rect);
    if(!IsBlockAlreadyHit(hit_rect))
    {
        HitBlock(hit_rect);
        UpdateHitTexture();

        return true;
    }

    return false;
}


//----------------------------------------------------------------------------//
// Render                                                                     //
//----------------------------------------------------------------------------//
void ISceneryObject::Render()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_pHitTexture, "Rendering a not valid Hit Texture.");
    COOPER_ASSERT(m_pPixelsArr,  "Rendering a not valid Pixel Array.");

    //--------------------------------------------------------------------------
    // Render the Hit texture.
    m_pGraphicsRef->RenderTexture(
        m_pHitTexture,
        m_localRect,
        m_collisionRect,
        0,
        SDL_Point{}
    );
}


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Pixel.
void ISceneryObject::HitPixel(int x, int y)
{
    COOPER_ASSERT(
        x >= 0 && x < m_localRect.w,
        "Invalid X coord: %d",
        x
    );

    COOPER_ASSERT(
        y >= 0 && y < m_localRect.h,
        "Invalid Y coord: %d",
        y
    );

    int loc = (m_localRect.w * y) + x;
    if(loc < 0 || loc >= m_localRect.w * m_localRect.h)
        return;

    m_pPixelsArr[loc] = m_hitColor;
}

void ISceneryObject::HitBlock(SDL_Rect rect)
{
    CalculateRect(rect);
    for(int y = rect.y; y < (rect.y + rect.h); ++y)
    {
        for(int x = rect.x; x < (rect.x + rect.w); ++x)
            HitPixel(x, y);
    }
}

bool ISceneryObject::IsPixelAlreadyHit(int x, int y)
{
    int loc = (m_localRect.w * y) + x;

    if(loc < 0 || loc >= m_localRect.w * m_localRect.h)
        return true;

    auto v = m_pPixelsArr[loc];
    return v == m_hitColor;
}

bool ISceneryObject::IsBlockAlreadyHit(SDL_Rect rect)
{
    CalculateRect(rect);
    for(int y = rect.y; y < (rect.y + rect.h); ++y)
    {
        for(int x = rect.x; x < (rect.x + rect.w); ++x)
        {
            if(!IsPixelAlreadyHit(x, y))
                return false;
        }
    }

    return true;
}

void ISceneryObject::ResetPixels()
{
    //--------------------------------------------------------------------------
    // Reset the all values on the array to m_normalColor.
    std::memset(
        m_pPixelsArr,
        m_normalColor,
        sizeof(Uint32) * m_localRect.w * m_localRect.h
    );
}


//------------------------------------------------------------------------------
// Rectangle.
void ISceneryObject::CalculateRect(SDL_Rect &rect)
{
    SDL_Rect intersect_rect{};

    SDL_IntersectRect(&m_localRect, &rect, &intersect_rect);
    rect = intersect_rect;
}

void ISceneryObject::MakeRectLocal(SDL_Rect &rect)
{
    //--------------------------------------------------------------------------
    // Transform the Hit Rect coordinates into the local space of the shield.
    auto local_hit_rect = SDL_Rect {
        rect.x - m_collisionRect.x,
        rect.y - m_collisionRect.y,
        rect.w,
        rect.h
    };

    rect = local_hit_rect;
}


//------------------------------------------------------------------------------
// Texture.
void ISceneryObject::UpdateHitTexture()
{
    COOPER_ASSERT(m_pHitTexture, "Hit texture can't be null");

    SDL_UpdateTexture(
        m_pHitTexture,
        nullptr,
        m_pPixelsArr,
        m_localRect.w * sizeof(Uint32)
    );
}

//------------------------------------------------------------------------------
// Resources.
void ISceneryObject::CreateResources()
{
    //--------------------------------------------------------------------------
    // Pixels - This is the actual pixels in the Hit Texture.
    m_pPixelsArr = new Uint32[m_localRect.w* m_localRect.h];


    //--------------------------------------------------------------------------
    // Hit Texture.
    m_pHitTexture = m_pGraphicsRef->CreateTexture(
        m_localRect.w,
        m_localRect.h
    );

    SDL_SetTextureBlendMode(m_pHitTexture, SDL_BLENDMODE_BLEND);
}

void ISceneryObject::DestroyResources()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_pHitTexture, "Destroying a not valid Hit Texture.");
    COOPER_ASSERT(m_pPixelsArr,  "Destroying a not valid Pixel Array.");

    //--------------------------------------------------------------------------
    // Pixels Array.
    delete m_pPixelsArr;
    m_pPixelsArr = nullptr;

    //--------------------------------------------------------------------------
    // Hit Texture.
    SDL_DestroyTexture(m_pHitTexture);
    m_pHitTexture = nullptr;
}
