//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : UFO.cpp                                                       //
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
#include "Game/include/GamePlay/UFO/UFO.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Speeds
constexpr auto kSpeed_Base = Cooper::Vec2(250, 0);
//------------------------------------------------------------------------------
// Atlas Names - We use that to retrieve the info in the TextureAtlas.
constexpr auto kAtlasName_Alive     = "UFO_Alive";
constexpr auto kAtlasName_Exploding = "UFO_Explosion";
//------------------------------------------------------------------------------
// Sound Names - We use that to play the sounds.
constexpr auto kSoundName_Death = "ufo_killed.wav";
//------------------------------------------------------------------------------
// Durations.
constexpr auto kDuration_ExplosionAnimation = 1.0f;
//------------------------------------------------------------------------------
// Timing
constexpr auto kResetTime_Base =  5;
constexpr auto kResetTime_Min  =  0;
constexpr auto kResetTime_Max  = 25;
//------------------------------------------------------------------------------
// Score
constexpr auto kScoreValue_Min        =  50;
constexpr auto kScoreValue_Multiplier =  10;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
UFO::UFO() :
    // Base.
    IGamePlayObject(kSpeed_Base, GameUtils::MoveBoundsUFO()),
    // Members,
    //m_aliveRect     // - Default initialized.
    //m_explosionRect // - Default initialized.
    m_explosionTime(0.0f),
    m_resetTime    (0.0f),
    m_currScore    (   0)
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the texture and render rects.
    m_pTexture      = p_atlas->Texture(kAtlasName_Alive);
    m_aliveRect     = m_pTexture->RenderRect();
    m_explosionRect = p_atlas->Rectangle(kAtlasName_Exploding);

    //--------------------------------------------------------------------------
    // Setup Text.
    m_pScoreText = Cooper::make_unique<Cooper::TextEntity>(
        GameUtils::GameFontPath(),
        GameUtils::GameFontSize(),
        "999",
        Cooper::Math::ColorWhite
    );

    //--------------------------------------------------------------------------
    // Setup hierarchy.
    Size(m_pTexture->Size());

    m_pTexture->Parent(this);
    m_pTexture->Origin(Origin());

    m_pScoreText->Parent(this);

    //--------------------------------------------------------------------------
    // Setup timers.
    CalculateAppearSettings();
    Kill();
}

void UFO::CalculateAppearSettings()
{
    //COWTODO(n2omatt): Find better values...
    m_resetTime  = kResetTime_Base + GameUtils::RandomInt(
        kResetTime_Min, kResetTime_Max
    );

    m_currScore  = int(kScoreValue_Min + m_resetTime * kScoreValue_Multiplier);

    m_pScoreText->Contents(std::to_string(m_currScore));
    m_pScoreText->Color   (Cooper::Math::ColorWhite);
    m_pScoreText->Position(
        m_pScoreText->Size() * 0.5f - Size() * 0.5f
    ); // To center the text.

    Cooper::Log::D("UFO: %f", m_resetTime);
}

//------------------------------------------------------------------------//
// Control Functions                                                      //
//------------------------------------------------------------------------//
void UFO::Reset()
{
    IGamePlayObject::Reset();

    //--------------------------------------------------------------------------
    // Setup the Alive Animation.
    m_pTexture  ->RenderRect(m_aliveRect);
    m_pTexture  ->Visible(true );
    m_pScoreText->Visible(false);

    //--------------------------------------------------------------------------
    // Calculate the Position and Direction.
    CalculateAppearSettings();
    if(GameUtils::RandomBool())
    {
        Position(MoveBounds().max.x, MoveBounds().min.y);
        m_moveVector.x = -1;
    }
    else
    {
        Position(MoveBounds().min.x, MoveBounds().min.y);
        m_moveVector.x = 1;
    }

    Speed(kSpeed_Base * m_moveVector);
}

void UFO::Explode()
{
    IGamePlayObject::Explode();

    //--------------------------------------------------------------------------
    // Sound.
    Cooper::Sound::PlaySound(GameUtils::GetSoundsPath(kSoundName_Death));

    //--------------------------------------------------------------------------
    // Setup the Explosion Animation.
    m_pTexture->RenderRect(m_explosionRect);
    m_explosionTime = kDuration_ExplosionAnimation;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void UFO::UpdateAlive()
{
    IGamePlayObject::UpdateAlive();

    //--------------------------------------------------------------------------
    // Reach the other side without being hit.
    const auto &pos    = Position  ();
    const auto &size   = Size      ();
    const auto &bounds = MoveBounds();
    if(pos.x + (size.x * 0.5f) < bounds.min.x ||
       pos.x - (size.x * 0.5f) > bounds.max.x)
    {
        Kill();
    }
}


void UFO::UpdateExploding()
{
    //--------------------------------------------------------------------------
    // Update timing....
    m_explosionTime -= m_pGameRef->GetTimer()->DeltaTime();

    //--------------------------------------------------------------------------
    // Animation Done.
    if(m_explosionTime <= 0)
    {
        //----------------------------------------------------------------------
        // Showing the Explosion.
        //   So show the score label.
        if(m_pTexture->Visible())
        {
            m_explosionTime = kDuration_ExplosionAnimation;

            m_pTexture  ->Visible(false);
            m_pScoreText->Visible(true );
        }
        //----------------------------------------------------------------------
        // Showing the Score Label.
        //    End of the animation.
        else
        {
            Kill();
        }
    }
}

void UFO::UpdateDead()
{
    //--------------------------------------------------------------------------
    // Update timing....
    m_resetTime -= m_pGameRef->GetTimer()->DeltaTime();

    //--------------------------------------------------------------------------
    // Animation Done.
    if(m_resetTime <= 0)
        Reset();
}

void UFO::Render()
{
    //--------------------------------------------------------------------------
    // Nothing to Render.
    if(Dead())
        return;

    //--------------------------------------------------------------------------
    // Render the child objects.
    m_pTexture  ->Render();
    m_pScoreText->Render();
}
