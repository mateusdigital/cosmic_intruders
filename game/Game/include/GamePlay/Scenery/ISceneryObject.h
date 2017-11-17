//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ISceneryObject.h                                              //
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
// Cooper
#include "Cooper/Cooper.h"


namespace CosmicIntruders {

class ISceneryObject
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit ISceneryObject(
        const Cooper::Vec2 &pos,
        const Cooper::Vec2 &hitTextureSize,
        Uint32              normalColor,
        Uint32              hitColor
    );

    virtual ~ISceneryObject();


    //------------------------------------------------------------------------//
    // Action Functions                                                       //
    //------------------------------------------------------------------------//
public:
    virtual void Reset();

    // Helpers
protected:
    inline bool CheckOverralCollision(const SDL_Rect &rect)
    {
        return SDL_HasIntersection(&m_collisionRect, &rect);
    }

    virtual bool TakeHitHelper(SDL_Rect hit_rect);

    inline void SetCollisionRect(const SDL_Rect &rect)
    {
        m_collisionRect = rect;
    }

    //------------------------------------------------------------------------//
    // Render                                                                 //
    //------------------------------------------------------------------------//
public:
    virtual void Render();


    //------------------------------------------------------------------------//
    // Helper Functions                                                       //
    //------------------------------------------------------------------------//
protected:
    //--------------------------------------------------------------------------
    // Pixel.
    void HitPixel(int x, int y);
    void HitBlock(SDL_Rect rect);

    bool IsPixelAlreadyHit(int x, int y);
    bool IsBlockAlreadyHit(SDL_Rect rect);

    void ResetPixels();

    //--------------------------------------------------------------------------
    // Rectangle.
    void MakeRectLocal(SDL_Rect &rect);
    void CalculateRect(SDL_Rect &rect);

    //--------------------------------------------------------------------------
    // Texture.
    void UpdateHitTexture();

    //--------------------------------------------------------------------------
    // Resources.
    void CreateResources ();
    void DestroyResources();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    SDL_Rect m_localRect;
    SDL_Rect m_collisionRect;

    Uint32 m_normalColor;
    Uint32 m_hitColor;

    // Unmanaged Resources.
    SDL_Texture *m_pHitTexture;
    Uint32      *m_pPixelsArr;

    //--------------------------------------------------------------------------
    // Weak references.
    Cooper::Graphics *m_pGraphicsRef; // Cached for performance.

}; // class UFO
}  // namespace CosmicIntruders
