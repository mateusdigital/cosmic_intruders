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
