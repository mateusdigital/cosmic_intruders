//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Shield.h                                                      //
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
// Cosmic Intruders
#include "Game/include/GamePlay/Scenery/ISceneryObject.h"

namespace CosmicIntruders {

class Shield
    : public ISceneryObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(Shield);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Shield(const Cooper::Vec2 &pos);

    ~Shield() override = default;


    //------------------------------------------------------------------------//
    // Action Functions                                                       //
    //------------------------------------------------------------------------//
public:
    bool TakeAlienHit(SDL_Rect hit_rect);
    bool TakeHit     (SDL_Rect hit_rect, int dmg, bool goingDown);

    void Reset() override;

    //------------------------------------------------------------------------//
    // Render                                                                 //
    //------------------------------------------------------------------------//
public:
    void Render() override ;

    //------------------------------------------------------------------------//
    // Helper Functions                                                       //
    //------------------------------------------------------------------------//
private:
    void InflateRect(SDL_Rect &rect, int dmg, bool goingDown);

    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Base Texture.
    Cooper::TextureEntity::UPtr m_pShieldTexture;

}; // class Shield
}  // namespace CosmicIntruders
