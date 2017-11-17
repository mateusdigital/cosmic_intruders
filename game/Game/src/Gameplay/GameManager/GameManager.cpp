//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameManager.cpp                                               //
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
#include "Game/include/GamePlay/GameManager/GameManager.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// Singleton                                                                  //
//----------------------------------------------------------------------------//
GameManager::GameManager() :
    // Members.
    m_initialized      (false),
    m_isMultiplayer    (false),
    m_isGameOver       (false),
    m_levelNeedsInit   (false),
    m_pScoreHUD     (nullptr),
    m_pLevelHUD     (nullptr),
    m_pLaserHolder  (nullptr),
    m_pPlayer1      (nullptr),
    m_pPlayer2      (nullptr),
    m_pCurrPlayerRef(nullptr) //Weak Reference.
{
    // Empty...
}

GameManager::~GameManager()
{
    //Empty...
}


//----------------------------------------------------------------------------//
// Lifecycle Functions                                                        //
//----------------------------------------------------------------------------//
void GameManager::Init(bool multiplayer)
{
    //--------------------------------------------------------------------------
    // Set the control values.
    m_initialized    = true;

    m_isMultiplayer  = multiplayer;
    m_isGameOver     = false;
    m_levelNeedsInit = true;

    //--------------------------------------------------------------------------
    // Create the Objects.
    CreateLaserHolder();
    CreateLevelHUD   ();
    CreateScoreHUD   ();
    CreateLivesHUD   ();
    CreateGameOverHUD();
    CreatePlayers    ();

    StartLevel();
}

void GameManager::Shutdown()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Update initialization state.
    m_initialized = false;

    //--------------------------------------------------------------------------
    // Set the pointers to null.
    m_pScoreHUD = nullptr;
    m_pLevelHUD = nullptr;

    m_pPlayer1       = nullptr;
    m_pPlayer2       = nullptr;
    m_pCurrPlayerRef = nullptr;

    m_pLaserHolder = nullptr;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void GameManager::Update()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Showing GameOver HUD.
    if(m_isGameOver)
    {
        m_pGameOverHUD->Update();
    }
    //--------------------------------------------------------------------------
    // GamePlay.
    else
    {
        m_pCurrPlayerRef->Update();
    }
}

void GameManager::Render()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    m_pScoreHUD->Render();

    //--------------------------------------------------------------------------
    // Showing GameOver HUD.
    if(m_isGameOver)
    {
        m_pGameOverHUD->Render();
    }
    //--------------------------------------------------------------------------
    // GamePlay.
    else
    {
        m_pLivesHUD->Render();
        m_pLevelHUD->Render();

        m_pCurrPlayerRef->Render();
    }
}


//----------------------------------------------------------------------------//
// Game Functions                                                             //
//----------------------------------------------------------------------------//
void GameManager::StartLevel()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Level HUD.
    m_pLevelHUD->Setup(
        m_pCurrPlayerRef->Index(),
        m_pCurrPlayerRef->CurrentLevel()
    );
    m_pLevelHUD->Start();

    //--------------------------------------------------------------------------
    // Player.
    m_pCurrPlayerRef->StartLevel();
}

void GameManager::EndLevel(bool playerDead)
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // The Level Animation will run always in:
    //   Multiplayer Game - This will let the player know who is the current.
    //   Level Advance    - So the player will know which level he's.
    m_levelNeedsInit = !playerDead || m_isMultiplayer;

    //--------------------------------------------------------------------------
    // If player didn't died, advances his level.
    if(!playerDead)
    {
        m_pCurrPlayerRef->AddLevel();
    }
    //--------------------------------------------------------------------------
    // Otherwise check if we reach the end of game.
    else
    {
        m_pCurrPlayerRef->RemoveLive();
        m_pLivesHUD->Lives(m_pCurrPlayerRef->Lives(), m_pCurrPlayerRef->Index());

        CheckGeneralGameOver();
    }

    //--------------------------------------------------------------------------
    // On multiplayer games each player plays alternately independent
    // of the result of the previous one.
    if(m_isMultiplayer)
        ChangeCurrentPlayer();

    //--------------------------------------------------------------------------
    // Start the level for the current player.
    StartLevel();
}


//----------------------------------------------------------------------------//
// Create Objects Functions                                                   //
//----------------------------------------------------------------------------//
void GameManager::CreateLaserHolder()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    m_pLaserHolder = Cooper::make_unique<LaserHolder>();
}

void GameManager::CreateScoreHUD()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    m_pScoreHUD = Cooper::make_unique<ScoreHUD>(0, 0);
}

void GameManager::CreateLevelHUD()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    m_pLevelHUD = Cooper::make_unique<LevelHUD>();
}

void GameManager::CreateLivesHUD()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Create the HUD.
    m_pLivesHUD = Cooper::make_unique<LivesHUD>(m_isMultiplayer);

    //--------------------------------------------------------------------------
    // Set the lives.
    m_pLivesHUD->Lives(GameUtils::kDefaultLives, Player::kIndex_One);
    if(m_isMultiplayer)
        m_pLivesHUD->Lives(GameUtils::kDefaultLives, Player::kIndex_Two);
}

void GameManager::CreateGameOverHUD()
{
    m_pGameOverHUD = Cooper::make_unique<GameOverHUD>();
}

void GameManager::CreatePlayers()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Player 1.
    m_pPlayer1 = Cooper::make_unique<Player>(Player::kIndex_One);

    //--------------------------------------------------------------------------
    // Player 2.
    if(IsMultiplayerGame())
        m_pPlayer2 = Cooper::make_unique<Player>(Player::kIndex_Two);

    //--------------------------------------------------------------------------
    // Current Player.
    m_pCurrPlayerRef = m_pPlayer1.get();
}


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
void GameManager::ChangeCurrentPlayer()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    //--------------------------------------------------------------------------
    // Game is single player mode, there's no need for a change.
    if(!m_isMultiplayer)
        return;

    //--------------------------------------------------------------------------
    // Gets the reference for the other player.
    auto p_other_player = (m_pCurrPlayerRef == m_pPlayer1.get())
        ? m_pPlayer2.get()
        : m_pPlayer1.get();

    //--------------------------------------------------------------------------
    // If the other player already reach game over we don't need change it.
    if(p_other_player->GameOver())
        return;

    //--------------------------------------------------------------------------
    // Change...
    m_pCurrPlayerRef = p_other_player;
}

void GameManager::CheckGeneralGameOver()
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COOPER_ASSERT(m_initialized, "GameManager isn't initialized.");

    if(!m_pCurrPlayerRef->GameOver())
    {
        m_isGameOver = false;
        return; // Don't need check any further.
    }

    if(!m_pPlayer1->GameOver())
    {
        m_isGameOver = false;
        return; // Don't need check any further.
    }

    if(m_isMultiplayer && !m_pPlayer2->GameOver())
    {
        m_isGameOver = false;
        return; // Don't need check any further.
    }

    m_pGameOverHUD->Start();
    m_isGameOver = true;
}
