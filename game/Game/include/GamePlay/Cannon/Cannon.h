//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Cannon.h                                                      //
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
// std
#include <array>
// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/GamePlay/GamePlayObject/IGamePlayObject.h"


namespace CosmicIntruders {
// Forward declarations.
class LaserHolder;

class Cannon
    : public IGamePlayObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(Cannon);

    //--------------------------------------------------------------------------
    //  How many frames our move animation is composed.
    constexpr static int kFramesCount = 2;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Cannon(bool startsOnLeft);


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Reset  () override;
    void Explode() override;


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Move (const Cooper::Vec2 &moveVector);
    bool Shoot(bool shouldShoot);


    //------------------------------------------------------------------------//
    // Position Functions                                                     //
    //------------------------------------------------------------------------//
public:
    inline Cooper::Vec2 TurretPosition() const
    {
        return Position() + Cooper::Vec2(0, -30);
    }


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    // Update States.
    void UpdateAlive    () override;
    void UpdateExploding() override;

    // Render.
    void Render() override;

    //--------------------------------------------------------------------------
    // Update animation helpers.
    void UpdateAnimationExplosion();
    void UpdateAnimationInvisible();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Control.
    bool m_explosionFinished;
    bool m_startsOnLeft;

    // Display.
    Cooper::TextureEntity::UPtr m_pTexture;

    SDL_Rect                           m_aliveRect;
    std::array<SDL_Rect, kFramesCount> m_explosionRects;
    int                                m_animationIndex;

    // Timers.
    float m_explosionTime;
    float m_timeSinceLastFrameChange;

    float m_invisibleTime;


    //--------------------------------------------------------------------------
    // Weak References - Cached for performance.
    LaserHolder *m_pLaserHolderRef; //Used to spawn the lasers.

}; // class Cannon
}  // namespace CosmicIntruders
