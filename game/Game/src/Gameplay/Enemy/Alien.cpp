//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Alien.cpp                                                     //
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
#include "Game/include/GamePlay/Enemy/Alien.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/GamePlay/Formation/Formation.h"
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/GamePlay/Laser/LaserHolder.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Durations
constexpr auto kDuration_Explosion = 0.5f;
//------------------------------------------------------------------------------
// Sound Names - We use that to play the sounds.
constexpr auto kSoundName_Death = "invader_death.wav";
//------------------------------------------------------------------------------
// Shots Changes.
constexpr auto kShotChange_PoweredMin   =  1;
constexpr auto kShotChange_PoweredMax   = 10;
constexpr auto kShotChange_PoweredValue =  3;


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
std::string name_for_alien_type(Alien::Types type)
{
    if(type == Alien::Types::Shooter) return "AlienShooter_Frame%d";
    if(type == Alien::Types::Blocker) return "AlienBlocker_Frame%d";

    return "AlienMage_Frame%d";
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Alien::Alien(
    Types               type,
    const Cooper::Vec2 &position,
    const Bounds       &moveBounds,
    Formation          *pFormation) :
    // Base.
    IGamePlayObject(Cooper::Vec2::Zero(), moveBounds),
    // Members.
    m_type           (type),
    m_pFormationRef  (pFormation),
    m_pLaserHolderRef(GameManager::Instance()->GetLaserHolder())
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Get the texture with the alive render rect since it'll be default.
    //    But we need to set the alive rect as well since we only load
    //    one time but possible use them a lot.
    auto type_name      = name_for_alien_type(m_type);
    auto frame1_name    = Cooper::StringUtils::Format(type_name.c_str(), 1);
    auto frame2_name    = Cooper::StringUtils::Format(type_name.c_str(), 2);
    auto explosion_name = "Alien_Explosion";

    m_pTexture = p_atlas->Texture(frame1_name);

    m_aliveFramesRects[0] = m_pTexture->RenderRect();
    m_aliveFramesRects[1] = p_atlas->Rectangle(frame2_name);

    m_explosionRect = p_atlas->Rectangle(explosion_name);

    //--------------------------------------------------------------------------
    // Setup hierarchy and positioning.
    m_pTexture->Parent(this);

    Position(position);
    Size    (m_pTexture->Size());

    //--------------------------------------------------------------------------
    // Configure the values for the next Shoot.
    SetupShootChange();
}

//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Alien::Explode()
{
    IGamePlayObject::Explode();

    //--------------------------------------------------------------------------
    // Play Sound.
    Cooper::Sound::PlaySound(GameUtils::GetSoundsPath(kSoundName_Death));

    //--------------------------------------------------------------------------
    // Configure Explosion Time.
    m_explosionTime = kDuration_Explosion;

    //--------------------------------------------------------------------------
    // Configure the Render Rect.
    m_pTexture->RenderRect(m_explosionRect);
}


//----------------------------------------------------------------------------//
// Shoot Functions                                                            //
//----------------------------------------------------------------------------//
bool Alien::WantsToShoot()
{
    if(!Alive())
        return false;

    return m_timeToShoot < 0.0f;
}

void Alien::Shoot()
{
    //--------------------------------------------------------------------------
    // Check if Alien wants to shot a powered laser now.
    auto powered = GameUtils::RandomInt(
        kShotChange_PoweredMin,
        kShotChange_PoweredMax
    ) <= kShotChange_PoweredValue;

    //--------------------------------------------------------------------------
    // Spawn a new laser.
    auto p_laser = m_pLaserHolderRef->SpawnAlienLaser(powered);
    // Cannot shoot!
    if(!p_laser)
        return;

    p_laser->Position(Position());
    p_laser->Reset();

    //--------------------------------------------------------------------------
    // Setup stuff for our next shoot.
    SetupShootChange();
}

void Alien::SetupShootChange()
{
    auto rnd_float    = GameUtils::RandomFloat();
    auto aliens_alive = m_pFormationRef->AliveAliensCount();
    m_timeToShoot     = rnd_float * (aliens_alive / 4.0f)  + 1;

    Cooper::Log::D("Alien next wants to shoot in: %.2f", m_timeToShoot);
}



//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void Alien::UpdateAlive()
{
    IGamePlayObject::UpdateAlive();

    //--------------------------------------------------------------------------
    // Updates animation frame.
    auto frame_index = m_pFormationRef->MovementStep();
    m_pTexture->RenderRect(m_aliveFramesRects[frame_index]);

    //--------------------------------------------------------------------------
    // Updates Shoot Timer.
    m_timeToShoot -= m_pGameRef->GetTimer()->DeltaTime();
}

void Alien::UpdateExploding()
{
    m_explosionTime -= m_pGameRef->GetTimer()->DeltaTime();
    if(m_explosionTime <= 0.0f)
        Kill();
}


void Alien::Render()
{
    if(!Dead() && Visible())
        m_pTexture->Render();
}
