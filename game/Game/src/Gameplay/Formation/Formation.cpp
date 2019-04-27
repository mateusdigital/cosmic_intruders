//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Formation.cpp                                                 //
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
#include "Game/include/GamePlay/Formation/Formation.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/GamePlay/GameManager/GameManager.h"
#include "Game/include/GamePlay/Laser/LaserHolder.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Gaps
constexpr auto kGap_X                = 55;
constexpr auto kGap_Y                = 45;
//------------------------------------------------------------------------------
// Durations
constexpr auto kDuration_AlienAppear = 0.02f;
//------------------------------------------------------------------------------
// We're setting to -1 here because teh DecideMoveDirection will increment
// the index - So the first time that it runs it'll decide to the index 0
// which is the correct start index.
constexpr auto kStartMoveDirectionIndex = -1;
//------------------------------------------------------------------------------
// Sound Names - We use that to play the sounds.
constexpr auto kSoundName_StepFmt = "invader_step%d.wav";
//------------------------------------------------------------------------------
// Movement Directions.
constexpr auto kMoveDirection_Right = (Cooper::Vec2::Right() * 10);
constexpr auto kMoveDirection_Down  = (Cooper::Vec2::Down () * 30);
constexpr auto kMoveDirection_Left  = (Cooper::Vec2::Left () * 10);


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Formation::Formation(const Cooper::Vec2 &gridSize, int currLevel) :
    // Members.
    //   Control.
    m_currLevel(currLevel),
    //   Start Animation.
    //m_startAnimationTimer - Default initialized.
    m_startAnimationStarted  (false),
    m_startAnimationCompleted(false),
    m_startAnimationIndex    (    0),
    //   Movement.
    //m_moveAnimationTimer - Default initialized.
    m_moveDirection     (            Cooper::Vec2::Left()),
    m_moveDirectionIndex(        kStartMoveDirectionIndex),
    m_moveBounds        (GameUtils::MoveBoundsFormation()),
    m_moveStep          (                               0),
    m_moveSoundStep     (                               0),
    m_allowedToMove     (                           false),
    m_movedDownCount    (                               0),
    m_killMultiplier    (                               0),
    //m_timeToMove - Will be set on CalculateMoveTime().
    //   Aliens.
    //m_aliens        - Default initialized.
    m_gridSize         (gridSize),
    m_aliveAliensCount (int(gridSize.x * gridSize.y)),
    m_killedAliensCount(0),
    //   Weak References
    pLaserHolderRef(GameManager::Instance()->GetLaserHolder())
{
    //--------------------------------------------------------------------------
    // Setup the Aliens.
    SetupAliens(gridSize);

    //--------------------------------------------------------------------------
    // Setup Position / Size.
    Size  ((kGap_X * 11), kGap_Y * 5);
    Origin(0.0f, 0.0f);

    auto hwidth        = (Size().x * 0.5f);
    auto bounds_hwidth = (m_moveBounds.max.x - m_moveBounds.min.x) * 0.5f;
    Position(
        m_moveBounds.min.x + (bounds_hwidth - hwidth),
        m_moveBounds.min.y
    );

    //--------------------------------------------------------------------------
    // Finish the initialization.
    CalculateMoveTimer     ();
    DecideNextMoveDirection();
}


//----------------------------------------------------------------------------//
// Aliens Functions                                                           //
//----------------------------------------------------------------------------//
void Formation::CompleteExplosions()
{
    //--------------------------------------------------------------------------
    // Makes all Aliens that were exploding when the Level completes be
    // dead whe the Level starts again.
    for(const auto &p_alien : m_aliensVec)
        if(p_alien->Exploding())
            p_alien->Kill();
}


//----------------------------------------------------------------------------//
//  Start Animation Functions                                                 //
//----------------------------------------------------------------------------//
void Formation::StartStartAnimation()
{
    if(GameManager::Instance()->LevelNeedsInitialization())
    {
        //--------------------------------------------------------------------------
        // Setup the animation control values.
        m_startAnimationIndex     = 0;
        m_startAnimationStarted   = true;
        m_startAnimationCompleted = false;

        //--------------------------------------------------------------------------
        // Setup the timer.
        m_startAnimationTimer.Reset();

        //--------------------------------------------------------------------------
        // Make all aliens hidden.
        for(auto p_alien : m_aliensVec)
            p_alien->Visible(false);
    }
    else
    {
        m_startAnimationCompleted = true;
        m_allowedToMove           = true;
    }
}


//----------------------------------------------------------------------------//
// Movement Functions                                                         //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Control
void Formation::MoveUp()
{
    //--------------------------------------------------------------------------
    // Already on top.
    if(m_movedDownCount <= 0)
    {
        Cooper::Log::D("Formation is already on top...");
        return;
    }


    //--------------------------------------------------------------------------
    // Give a chance to player...
    DoTranslate(kMoveDirection_Down * -1);
    m_moveAnimationTime = 0;

    --m_movedDownCount;
}


//------------------------------------------------------------------------------
// Helpers
bool Formation::CheckEdgeHit()
{
    if(IsMovingDown())
        return false;

    //COWTODO(n2omatt) We can do better by checking the columns instead
    // of the rows and taking in account which is the direction that we're
    // moving.
    for(int i =0; i < m_aliens.size(); ++i)
    {
        for(int j = 0; j < m_aliens[0].size(); ++j)
        {
            auto p_alien = m_aliens[i][j];
            if(p_alien->IsOutsideMoveBounds())
                return true;
        }
    }

    return false;
}

void Formation::DecideNextMoveDirection()
{
    static Cooper::Vec2 s_move_vectors[] = {
        kMoveDirection_Right,
        kMoveDirection_Down,
        kMoveDirection_Left,
        kMoveDirection_Down,
    };

    m_moveDirectionIndex = (m_moveDirectionIndex + 1) % 4;
    m_moveDirection      = s_move_vectors[m_moveDirectionIndex];

    if(m_moveDirectionIndex % 2 != 0)
        ++m_movedDownCount;

    Cooper::Log::D(
        "Move Direction is: %.2f, %2.f",
        m_moveDirection.x,
        m_moveDirection.y
    );
}

void Formation::CalculateMoveTimer()
{
    //COWTODO(n2omatt): Remove Magic values...
    if(m_killedAliensCount != 0 && m_killedAliensCount % 6 == 0)
        m_killMultiplier = (m_killedAliensCount / 6.0f) / 15.0f;

    auto base_time = (1.2f - (m_currLevel / 10.0f));
    m_timeToMove = base_time- m_killMultiplier - (m_movedDownCount / 15.0f);
    m_timeToMove = std::max(0.050f, m_timeToMove);

    Cooper::Log::D("-------------------------");
    Cooper::Log::D(
        "Killed invaders: %d\nKill Scale: %.2f\nMoved Down: %d\nTime to move %.2f",
        m_killedAliensCount,
        m_killMultiplier,
        m_movedDownCount,
        m_timeToMove
    );
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void Formation::Update()
{
    //--------------------------------------------------------------------------
    // Updating the Start Animation.
    if(m_startAnimationStarted && !StartAnimationCompleted())
        UpdateStartAnimation();

    //--------------------------------------------------------------------------
    // Normal Update.
    else if(m_allowedToMove)
        UpdateMovement();
}

void Formation::Render()
{
    if(!Visible())
        return;

    //There's no need to render them.
    if(AliveAliensCount() == 0)
        return;

    for(const auto &line : m_aliens)
        for(const auto &p_alien : line)
            p_alien->Render();
}


//------------------------------------------------------------------------------
// Helpers
void Formation::UpdateStartAnimation()
{
    m_startAnimationTimer.Update();

    // Not enough time yet...
    if(m_startAnimationTimer.TotalTime() < kDuration_AlienAppear)
        return;

    for(; m_startAnimationIndex < AliensCount(); ++m_startAnimationIndex)
    {
        // Only take in account the aliens that aren't dead.
        if(!m_aliensVec[m_startAnimationIndex]->Dead())
        {
            m_aliensVec[m_startAnimationIndex]->Visible(true);
            ++m_startAnimationIndex;

            break;
        }
    }

    //--------------------------------------------------------------------------
    // Set the animation control values and timer.
    if(m_startAnimationIndex >= AliensCount())
    {
        //Now Aliens can move ;D
        m_startAnimationCompleted = true;
        m_allowedToMove           = true;
        m_moveAnimationTime       = m_timeToMove;
    }

    m_startAnimationTimer.Reset();
}

void Formation::UpdateMovement()
{
    //--------------------------------------------------------------------------
    // Check if already time to move - If so, move ;D
    m_moveAnimationTime -= m_pGameRef->GetTimer()->DeltaTime();
    if(m_moveAnimationTime <= 0)
    {
        // Play Sound.
        auto sound_name = Cooper::StringUtils::Format(
            kSoundName_StepFmt,
            m_moveSoundStep
        );
        Cooper::Sound::PlaySound(GameUtils::GetSoundsPath(sound_name));

        // Set the move control.
        m_moveAnimationTime = m_timeToMove;
        m_moveStep          = (m_moveStep      + 1) % Alien::kFramesCount;
        m_moveSoundStep     = (m_moveSoundStep + 1) % Alien::kSoundsCount;

        // Move.
        DoTranslate(MovementDirection());

        // Check if we need update the direction.
        if(IsMovingDown() || CheckEdgeHit())
        {
            DecideNextMoveDirection();
            CalculateMoveTimer     ();
        }
    }

    //--------------------------------------------------------------------------
    // Call the update for each Alien.
    for(int i =0; i < m_aliens.size(); ++i)
    {
        for(int j = 0; j < m_aliens[0].size(); ++j)
        {
            auto p_alien = m_aliens[i][j];
            p_alien->Update();

            HandleAlienShooting(i, j);
        }
    }
}


//----------------------------------------------------------------------------//
// Aliens Helper Functions                                                    //
//----------------------------------------------------------------------------//
void Formation::SetupAliens(const Cooper::Vec2 &gridSize)
{
    // Cache values.
    auto rows = int(gridSize.y);
    auto cols = int(gridSize.x);

    // Play nice with memory.
    m_aliens   .reserve(rows);
    m_aliensVec.reserve(rows * cols);

    // COWTODO(n2omatt): This isn't very flexible...
    Alien::Types enemies[] = {
        Alien::Types::Mage,
        Alien::Types::Mage,
        Alien::Types::Shooter,
        Alien::Types::Shooter,
        Alien::Types::Blocker,
    };

    // Calculate padding.
    auto padding_x  = kGap_X * 0.5f;
    auto padding_y  = kGap_Y * 0.5f;

    for(int i = 0; i < rows; ++i)
    {
        // Play nice with memory.
        m_aliens.emplace_back(AlienLine());
        m_aliens[i].reserve(cols);

        // Pre calculate the Y position for this row.
        auto curr_pos_y = (kGap_Y * i +padding_y);

        for(int j = 0; j < cols; ++j)
        {
            // Initialize the Alien.
            auto pos     = Cooper::Vec2(kGap_X * j + padding_x, curr_pos_y);
            auto type    = enemies[i];
            auto p_alien = std::make_shared<Alien>(type, pos, m_moveBounds, this);

            p_alien->Parent(this);
            // Makes the alien updates the Formation about its death.
            p_alien->OnDeath([this](){
                --m_aliveAliensCount ;
                ++m_killedAliensCount;
                CalculateMoveTimer();
            });

            p_alien->Visible(false);
            p_alien->Reset();

            m_aliens[i].push_back(p_alien);

            // This is a 'weak' reference view of all of your aliens.
            m_aliensVec.push_back(p_alien.get());
        }
    }
}

void Formation::HandleAlienShooting(int row, int col)
{
    // We don't want hurt our friends do we?
    if(ThereIsAlienBellow(row, col))
        return;

    // Alien doesn't wants to shoot now...
    auto p_alien = m_aliens[row][col];
    if(!p_alien->WantsToShoot())
        return;

    //--------------------------------------------------------------------------
    // Make alien shoot and configure the laser.
    p_alien->Shoot();
}
