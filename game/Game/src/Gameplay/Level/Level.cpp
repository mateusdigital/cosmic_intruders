//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Level.cpp                                                     //
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
#include "Game/include/GamePlay/Level/Level.h"
// CosmicIntruders
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/GamePlay/Hud/LevelHUD.h"
#include "Game/include/GamePlay/Hud/ScoreHUD.h"
#include "Game/include/GamePlay/Laser/LaserHolder.h"
#include "Game/include/GamePlay/Player/Player.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kAliens_Rows =  5;
constexpr auto kAliens_Cols = 11;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Level::Level(Player *pPlayerRef) :
    // Control.
    m_currentAnimationState(AnimationStates::NotAnimating),
    m_playerWasKilled      (false),
    m_levelWasStarted      (false),
    m_levelIsOver          (false),
    m_keyboardHasControl   ( true),
    // Objects.
    m_pCannon     (nullptr),
    m_pFormation  (nullptr),
    m_pUFO        (nullptr),
    // Weak references.
    m_pGameMgrRef    (GameManager::Instance()),
    m_pPlayerRef     (pPlayerRef),
    m_pScoreHUDRef   (m_pGameMgrRef->GetScoreHUD   ()),
    m_pLevelHUDRef   (m_pGameMgrRef->GetLevelHUD   ()),
    m_pLaserHolderRef(m_pGameMgrRef->GetLaserHolder())
{
    //Empty...
}

Level::~Level()
{
    //--------------------------------------------------------------------------
    // Weak references.
    m_pGameMgrRef     = nullptr;
    m_pPlayerRef      = nullptr;
    m_pScoreHUDRef    = nullptr;
    m_pLevelHUDRef    = nullptr;
    m_pLaserHolderRef = nullptr;
}


//----------------------------------------------------------------------------//
// Init Functions                                                             //
//----------------------------------------------------------------------------//
void Level::InitObjects()
{
    //--------------------------------------------------------------------------
    // Cannon.
    auto cannon_starts_on_left = m_pPlayerRef->Index() == Player::kIndex_One;
    m_pCannon = Cooper::make_unique<Cannon>(cannon_starts_on_left);
    m_pCannon->Reset();

    //--------------------------------------------------------------------------
    // Formation.
    m_pFormation = Cooper::make_unique<Formation>(
        Cooper::Vec2(kAliens_Cols, kAliens_Rows),
        m_pPlayerRef->CurrentLevel()
    );

    //--------------------------------------------------------------------------
    // UFO.
    m_pUFO = Cooper::make_unique<UFO>();
    m_pUFO->Kill();

    //--------------------------------------------------------------------------
    // Shields.
    const auto &screen_size = m_pGraphicsRef->GetScreenSize();
    for(int i = 0; i < m_shields.size(); ++i)
    {
        auto shield_pos = Cooper::Vec2(
            screen_size.x * (0.2f * (i+1)),
            m_pCannon->Position().y - 90 //COWNOTE(n2omatt): Arbritrary value ;D
        );

        auto p_shield = Cooper::make_unique<Shield>(shield_pos);
        p_shield->Reset();

        m_shields[i] = std::move(p_shield);
    }

    //--------------------------------------------------------------------------
    // Ground.
    m_pGround = Cooper::make_unique<Ground>(
        Cooper::Vec2(0, m_pCannon->Position().y + 25)
    );
    m_pGround->Reset();
}

void Level::SetupObjects()
{
    //COWTODO(n2omatt): Make a way to reset formation without create a new.
    m_pFormation = Cooper::make_unique<Formation>(
        Cooper::Vec2(kAliens_Cols, kAliens_Rows),
        m_pPlayerRef->CurrentLevel()
    );
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Level::Start()
{
    m_levelWasStarted = true;
    m_levelIsOver     = false;
    m_playerWasKilled = false;

    m_currentAnimationState = AnimationStates::LevelHUD;
    m_pCannon->Reset();

    //--------------------------------------------------------------------------
    // Start the level animation.
    if(GameManager::Instance()->LevelNeedsInitialization())
        m_pFormation->Visible(false);
}

void Level::End()
{
    m_levelWasStarted = false;
    m_levelIsOver     = true;

    m_pLaserHolderRef->KillAll();
    m_pFormation     ->CompleteExplosions();
    m_pFormation     ->MoveUp ();

    m_pGameMgrRef->EndLevel(m_playerWasKilled);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void Level::Update()
{
    switch(m_currentAnimationState)
    {
        case AnimationStates::NotAnimating : {
            UpdateGameplay();
        } break;

        case AnimationStates::LevelHUD : {
            UpdateAnimationLevelHUD();
        } break;

        case AnimationStates::Formation : {
            UpdateAnimationFormation();
        } break;

        case AnimationStates::CannonExploding : {
            UpdateAnimationPlayerDeath();
        } break;
    }
}

//------------------------------------------------------------------------------
// Update Helpers.
void Level::UpdateGameplay()
{
    //--------------------------------------------------------------------------
    // All Aliens Killed - End of level.
    if(m_pFormation->AliveAliensCount() <= 0)
    {
        End();
        return;
    }

    //--------------------------------------------------------------------------
    // This will decide if we're moving with keyboard or mouse.
    UpdateInput();

    //--------------------------------------------------------------------------
    // Cannon.
    m_pCannon->Move  (HandleMoveInput ());
    m_pCannon->Shoot (HandleShootInput());
    m_pCannon->Update();

    //--------------------------------------------------------------------------
    // Formation
    m_pFormation->Update();

    //--------------------------------------------------------------------------
    // Lasers.
    m_pLaserHolderRef->Update();

    //--------------------------------------------------------------------------
    // UFO.
    m_pUFO->Update();

    //--------------------------------------------------------------------------
    // Handle Collisions.
    HandleCollisions();
}

void Level::UpdateAnimationLevelHUD()
{
    m_pLevelHUDRef->Update();

    // Completed - Change state.
    if(m_pLevelHUDRef->Completed())
    {
        m_currentAnimationState = AnimationStates::Formation;
        m_pFormation->Visible(true);
        m_pFormation->StartStartAnimation();
    }
}

void Level::UpdateAnimationFormation()
{
    m_pFormation->Update();

    // Completed - Change State.
    if(m_pFormation->StartAnimationCompleted())
        m_currentAnimationState = AnimationStates::NotAnimating;
}

void Level::UpdateAnimationPlayerDeath()
{
    m_pCannon->Update();

    // Completed - Change State.
    if(!m_pCannon->Exploding())
    {
        m_currentAnimationState = AnimationStates::NotAnimating;
        End();
    }
}


void Level::Render()
{
    m_pGround->Render();

    for(const auto &p_shield : m_shields)
        p_shield->Render();

    m_pLaserHolderRef->Render();
    m_pFormation     ->Render();

    m_pCannon->Render();
    m_pUFO   ->Render();
}


//----------------------------------------------------------------------------//
// Input                                                                      //
//----------------------------------------------------------------------------//
void Level::UpdateInput()
{
    if(m_keyboardHasControl && Cooper::Input::HasMouseInput())
        m_keyboardHasControl = false;

    else if(!m_keyboardHasControl && Cooper::Input::HasKeyboardInput())
        m_keyboardHasControl = true;
}

Cooper::Vec2 Level::HandleMoveInput()
{
    auto move_vector = Cooper::Vec2::Zero();

    //--------------------------------------------------------------------------
    // Mouse Input
    if(!m_keyboardHasControl)
    {
        const auto &mouse_pos  = Cooper::Input::MousePosition();
        const auto &cannon_pos = m_pCannon->Position();

        auto delta = (mouse_pos.x - cannon_pos.x);

        if(std::abs(delta) < 5) // Too little input.
            return move_vector;

        if(delta < 0)
            move_vector.x -= 1;
        else
            move_vector.x += 1;
    }
    //--------------------------------------------------------------------------
    // Keyboard Input
    else
    {
        if(Cooper::Input::KeyDown(SDL_SCANCODE_LEFT))
            move_vector.x -= 1;
        if(Cooper::Input::KeyDown(SDL_SCANCODE_RIGHT))
            move_vector.x += 1;
    }

    return move_vector;
}

bool Level::HandleShootInput()
{
    //--------------------------------------------------------------------------
    // Mouse Input
    if(!m_keyboardHasControl && Cooper::Input::MouseButtonPress(0))
         return true;

    //--------------------------------------------------------------------------
    // Keyboard Input
    return Cooper::Input::KeyPress(SDL_SCANCODE_SPACE);
}


//----------------------------------------------------------------------------//
// Collisions                                                                 //
//----------------------------------------------------------------------------//
void Level::HandleCollisions()
{
    HandleCollisions_CannonLasers();
    HandleCollisions_AlienLasers ();
    HandleCollisions_Aliens      ();
}

void Level::HandleCollisions_CannonLasers()
{
    //--------------------------------------------------------------------------
    // Cache the collections.
    auto &cannon_lasers = m_pLaserHolderRef->CannonLasers();
    auto &alien_lasers  = m_pLaserHolderRef->AlienLasers ();
    auto &aliens        = m_pFormation     ->Aliens      ();

    for(const auto &p_laser : cannon_lasers)
    {
        if(!p_laser->Alive())
            continue;

        bool collided = false; // To exit early...

        //----------------------------------------------------------------------
        // Against UFO.
        if(p_laser->CollidesWith(m_pUFO.get()))
        {
            // Make the objects update state.
            m_pUFO->Explode();
            p_laser->Kill   ();

            // Update the scores.
            UpdateScore(m_pUFO->ScoreValue());

            collided = true;
        }

        if(collided)
            continue; // To exit early...


        //----------------------------------------------------------------------
        // Against Shields.
        for(const auto &p_shield : m_shields)
        {
            auto rect = p_laser->BoundingRect();
            if(!p_shield->TakeHit(rect, 10, false))
                continue;

            // Make the objects update state.
            p_laser->Explode();

            collided = true;
            break; // Already hit - No meaning in continue any further.
        }

        if(collided)
            continue; // To exit early...


        //----------------------------------------------------------------------
        // Against Aliens.
        for(const auto &p_alien : aliens)
        {
            if(!p_alien->Alive())
                continue;

            if(!p_alien->CollidesWith(p_laser.get()))
                continue;

            // Make the objects update state.
            p_alien->Explode();
            p_laser->Kill   ();

            // We need this because we don't want it to move anymore.
            p_alien->Parent(nullptr);

            // Update the scores.
            UpdateScore(p_alien->ScoreValue());

            collided = true;
            break; // Already hit - No meaning in continue any further.
        }

        if(collided)
            continue; // To exit early...


        //----------------------------------------------------------------------
        // Against Aliens' Lasers.
        for(const auto &p_alien_laser : alien_lasers)
        {
            if(!p_alien_laser->Alive())
                continue;

            if(!p_alien_laser->CollidesWith(p_laser.get()))
                continue;

            // Make the objects update state.
            p_alien_laser->Explode();
            p_laser      ->Kill   ();

            // Update the scores.
            UpdateScore(p_alien_laser->ScoreValue());

            collided = true;
            break; // Already hit - No meaning in continue any further.
        }

        if(collided)
            continue; // To exit early...
    }
}

void Level::HandleCollisions_AlienLasers()
{
    //--------------------------------------------------------------------------
    // Cache the collections.
    auto &cannon_lasers = m_pLaserHolderRef->CannonLasers();
    auto &alien_lasers  = m_pLaserHolderRef->AlienLasers ();
    auto &aliens        = m_pFormation     ->Aliens      ();

    //--------------------------------------------------------------------------
    // Alien Lasers.
    for(const auto &p_laser : alien_lasers)
    {
        if(!p_laser->Alive())
            continue;

        bool collided = false; // To exit early...

        //----------------------------------------------------------------------
        // Against Ground.
        if(m_pGround->TakeHit(p_laser->BoundingRect()))
        {
            p_laser->Explode();
            continue;
        }

        //----------------------------------------------------------------------
        // Against Shields.
        for(const auto &p_shield : m_shields)
        {
            auto rect = p_laser->BoundingRect();
            if(!p_shield->TakeHit(rect, p_laser->ScoreValue(), true))
                continue;

            // Make the objects update state.
            p_laser->Kill();

            collided = true;
            break; // Already hit - No meaning in continue any further.
        }

        if(collided)
            continue; // To exit early...


        //----------------------------------------------------------------------
        // Against Cannon.
        if(m_pCannon->CollidesWith(p_laser.get()))
        {
            // Make the objects update state.
            p_laser->Kill();

            // Change the current play state.
            PlayerWasHit();

            return; // Already hit - No meaning in continue any further.
        }
    }
}

void Level::HandleCollisions_Aliens()
{
    //--------------------------------------------------------------------------
    // Cache the collections.
    auto &aliens = m_pFormation->Aliens();

    //--------------------------------------------------------------------------
    // Aliens.
    //   Kill all aliens that collided with ground to give
    //   a better chance to player...
    bool collided_with_ground = false;
    for(const auto &p_alien : aliens)
    {
        if(!p_alien->Alive())
            continue;

        //----------------------------------------------------------------------
        // Against Ground
        if(m_pGround->TakeHit(p_alien->BoundingRect()))
        {
            // Make the objects update state.
            p_alien->Explode();
            collided_with_ground = true;
        }

        //----------------------------------------------------------------------
        // Against Shields.
        for(const auto &p_shield : m_shields)
        {
            auto rect = p_alien->BoundingRect();
            p_shield->TakeAlienHit(rect);
        }

        //----------------------------------------------------------------------
        // Against Cannon.
        if(p_alien->CollidesWith(m_pCannon.get()))
        {
            // Make the objects update state.
            p_alien->Explode();

            // Change the current play state.
            PlayerWasHit();

            return; // Already hit - No meaning in continue any further.
        }
    }

    // -------------------------------------------------------------------------
    // But kills the player too..
    if(collided_with_ground)
    {
        PlayerWasHit();
        return;
    }
}


//----------------------------------------------------------------------------//
// Score Functions                                                            //
//----------------------------------------------------------------------------//
void Level::UpdateScore(int amount)
{
    m_pPlayerRef->AddScore(amount);

    //--------------------------------------------------------------------------
    // Set which score we're updating.
    // Assume that's player one.
    auto score_type = ScoreHUD::ScoreTypes::One;
    if(m_pPlayerRef->Index() == Player::kIndex_Two)
        score_type = ScoreHUD::ScoreTypes::Two;

    //--------------------------------------------------------------------------
    // Update the score.
    m_pScoreHUDRef->Score(
        m_pPlayerRef->CurrentScore(),
        score_type
    );
}


//----------------------------------------------------------------------------//
// State Change Functions                                                     //
//----------------------------------------------------------------------------//
void Level::PlayerWasHit()
{
    //--------------------------------------------------------------------------
    // Make the objects update the states.
    m_pCannon        ->Explode();
    m_pFormation     ->Stop   ();
    m_pLaserHolderRef->KillAll();

    //--------------------------------------------------------------------------
    // Update the control values.
    m_playerWasKilled       = true;
    m_currentAnimationState = AnimationStates::CannonExploding;
}
