//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Alien.h                                                       //
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
class Formation;
class LaserHolder;

class Alien
    : public IGamePlayObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    // Enums.
    enum class Types { Blocker= 1, Shooter = 2, Mage = 3 };

    // Typedefs.
    COOPER_SMART_PTRS_OF(Alien);

    //--------------------------------------------------------------------------
    //  How many frames our move animation is composed.
    constexpr static int kFramesCount = 2;
    constexpr static int kSoundsCount = 4;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Alien(
        Types               type,
        const Cooper::Vec2 &position,
        const Bounds       &moveBounds,
        Formation          *pFormation);


    //------------------------------------------------------------------------//
    // Type / Value Functions                                                 //
    //------------------------------------------------------------------------//
public:
    inline Types Type() const { return m_type; }

    inline int ScoreValue() const { return int(m_type) * 10; }


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Explode() override;


    //------------------------------------------------------------------------//
    // Shoot Functions                                                        //
    //------------------------------------------------------------------------//
public:
    bool WantsToShoot();
    void Shoot();

private:
    void SetupShootChange();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void UpdateAlive    () override;
    void UpdateExploding() override;

    void Render() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    // Control.
    Types m_type;

    // Display.
    Cooper::TextureEntity::UPtr        m_pTexture;
    std::array<SDL_Rect, kFramesCount> m_aliveFramesRects;
    SDL_Rect                           m_explosionRect;
    float                              m_explosionTime;

    // Shooting.
    float m_timeToShoot;

    //--------------------------------------------------------------------------
    // Weak References - Cached for performance.
    Formation   *m_pFormationRef;
    LaserHolder *m_pLaserHolderRef;

}; // class Alien
}  // namespace CosmicIntruders
