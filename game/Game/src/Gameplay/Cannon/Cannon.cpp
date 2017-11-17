//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Cannon.cpp                                                    //
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
#include "Game/include/GamePlay/Cannon/Cannon.h"
// CosmicIntruders
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Speeds
constexpr auto kSpeed_Base = Cooper::Vec2(500, 0);
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto kAtlasName_Alive      = "Cannon_Alive";
constexpr auto kAtlasName_Exploding1 = "Cannon_Exploding1";
constexpr auto kAtlasName_Exploding2 = "Cannon_Exploding2";
//------------------------------------------------------------------------------
// Sound Names - We use that to play the sounds.
constexpr auto kSoundName_Shoot = "shoot_laser.wav";
constexpr auto kSoundName_Death = "player_death.wav";
//------------------------------------------------------------------------------
// Durations.
constexpr auto kDuration_ExplosionAnimation = 1.5f;
constexpr auto kDuration_FrameChange        = kDuration_ExplosionAnimation / 20;
constexpr auto kDuration_InvisibleAnimation = 1.0f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Cannon::Cannon(bool startsOnLeft) :
    // Base.
    IGamePlayObject(Cooper::Vec2::Zero(), GameUtils::MoveBoundsCannon()),
    // Members.
    m_startsOnLeft            (startsOnLeft),
    m_animationIndex          (0),
    m_timeSinceLastFrameChange(0),
    m_pLaserHolderRef         (GameManager::Instance()->GetLaserHolder())
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the texture and render rects.
    m_pTexture  = p_atlas->Texture(kAtlasName_Alive);
    m_aliveRect = m_pTexture->RenderRect();

    m_explosionRects[0] = p_atlas->Rectangle(kAtlasName_Exploding1);
    m_explosionRects[1] = p_atlas->Rectangle(kAtlasName_Exploding2);

    //--------------------------------------------------------------------------
    // Setup hierarchy.
    m_pTexture->Parent(this);
    Size    (m_pTexture->Size());
}

//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Cannon::Reset()
{
    IGamePlayObject::Reset();

    //--------------------------------------------------------------------------
    // Display.
    m_pTexture->RenderRect(m_aliveRect);
    m_pTexture->Visible   (true);

    //--------------------------------------------------------------------------
    // Position.
    const auto &bounds = GameUtils::MoveBoundsCannon();
    const auto &size   = Size();

    auto pos_x = (m_startsOnLeft)
        ? bounds.min.x + size.x
        : bounds.max.x - size.x;

    Position(pos_x,bounds.min.y);
}

void Cannon::Explode()
{
    IGamePlayObject::Explode();

    //--------------------------------------------------------------------------
    // Play Sounds.
    Cooper::Sound::PlaySound(GameUtils::GetSoundsPath(kSoundName_Death));

    //--------------------------------------------------------------------------
    // Setup the Explosion Animation.
    m_pTexture->RenderRect(m_explosionRects[0]);

    m_animationIndex    = 0;
    m_explosionFinished = false;

    m_explosionTime            = kDuration_ExplosionAnimation;
    m_invisibleTime            = kDuration_InvisibleAnimation;
    m_timeSinceLastFrameChange = kDuration_FrameChange;
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Cannon::Move(const Cooper::Vec2 &moveVector)
{
    Speed(kSpeed_Base * moveVector);
}

bool Cannon::Shoot(bool shouldShoot)
{
    if(!shouldShoot || !Alive())
        return false;

    //--------------------------------------------------------------------------
    // Spawn Lasers.
    auto p_laser = m_pLaserHolderRef->SpawnCannonLaser();

    // Cannot shoot!
    if(!p_laser)
        return false;

    //--------------------------------------------------------------------------
    // Play sound.
    Cooper::Sound::PlaySound(GameUtils::GetSoundsPath(kSoundName_Shoot));

    //--------------------------------------------------------------------------
    // Reset Lasers.
    p_laser->Position(TurretPosition());
    p_laser->Reset();

    return true;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void Cannon::UpdateAlive()
{
    //--------------------------------------------------------------------------
    // Base class is responsible for the actual movement...
    IGamePlayObject::UpdateAlive();

    //--------------------------------------------------------------------------
    // Check if we hit the boundaries.
    const auto &pos    = Position  ();
    const auto &bounds = MoveBounds();

         if(pos.x <= bounds.min.x) Position(bounds.min.x, pos.y);
    else if(pos.x >= bounds.max.x) Position(bounds.max.x, pos.y);
}

void Cannon::UpdateExploding()
{
    (m_explosionFinished)
        ? UpdateAnimationInvisible()
        : UpdateAnimationExplosion();
}


void Cannon::Render()
{
    if(!Dead())
        m_pTexture->Render();
}



//------------------------------------------------------------------------------
// Update animation helpers.
void Cannon::UpdateAnimationExplosion()
{
    auto delta = m_pGameRef->GetTimer()->DeltaTime();

    //--------------------------------------------------------------------------
    // Frame Change.
    m_timeSinceLastFrameChange -= delta;
    if(m_timeSinceLastFrameChange <= 0)
    {
        m_animationIndex           = (m_animationIndex + 1) % kFramesCount;
        m_timeSinceLastFrameChange = kDuration_FrameChange;

        m_pTexture->RenderRect(m_explosionRects[m_animationIndex]);
    }

    //--------------------------------------------------------------------------
    // Animation Done.
    m_explosionTime -= delta;
    if(m_explosionTime <= 0)
    {
        m_pTexture->Visible(false);
        m_explosionFinished = true;
    }
}

void Cannon::UpdateAnimationInvisible()
{
    //--------------------------------------------------------------------------
    // Animation Done.
    m_invisibleTime -= m_pGameRef->GetTimer()->DeltaTime();
    if(m_invisibleTime <= 0)
        Kill();
}
