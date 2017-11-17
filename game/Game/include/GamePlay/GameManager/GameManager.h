//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameManager.h                                                 //
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

#include "Cooper/Cooper.h"
// Cosmic Intruders
#include "Game/include/GamePlay/Player/Player.h"
#include "Game/include/GamePlay/Hud/ScoreHUD.h"
#include "Game/include/GamePlay/Hud/LevelHUD.h"
#include "Game/include/GamePlay/Hud/LivesHUD.h"
#include "Game/include/GamePlay/Hud/GameOverHUD.h"
#include "Game/include/GamePlay/Laser/LaserHolder.h"

namespace CosmicIntruders {
class GameManager
{
    //------------------------------------------------------------------------//
    // Singleton                                                              //
    //------------------------------------------------------------------------//
public:
    COOPER_SINGLETON_OF(GameManager);


    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                    //
    //------------------------------------------------------------------------//
public:
    void Init(bool multiplayer);
    void Shutdown();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update();
    void Render();


    //------------------------------------------------------------------------//
    // Game Functions                                                         //
    //------------------------------------------------------------------------//
    // State.
public:
    inline bool IsMultiplayerGame() const { return m_isMultiplayer; }

    inline bool IsGameOver() const
    {
        return m_isGameOver && m_pGameOverHUD->Completed();
    }

    inline bool LevelNeedsInitialization() const { return m_levelNeedsInit; }

    // Control.
public:
    void StartLevel();
    void EndLevel  (bool playerDead);


    //------------------------------------------------------------------------//
    // Object Reference Getters                                               //
    //------------------------------------------------------------------------//
public:
    inline LaserHolder* GetLaserHolder() const { return m_pLaserHolder.get(); }
    inline LevelHUD   * GetLevelHUD   () const { return m_pLevelHUD   .get(); }
    inline ScoreHUD   * GetScoreHUD   () const { return m_pScoreHUD   .get(); }


    //------------------------------------------------------------------------//
    // Create Objects Functions                                               //
    //------------------------------------------------------------------------//
private:
    void CreateLaserHolder();
    void CreateScoreHUD   ();
    void CreateLevelHUD   ();
    void CreateLivesHUD   ();
    void CreateGameOverHUD();
    void CreatePlayers    ();


    //------------------------------------------------------------------------//
    // Helper Functions                                                       //
    //------------------------------------------------------------------------//
private:
    void ChangeCurrentPlayer();
    void CheckGeneralGameOver();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Control.
    bool m_initialized;
    bool m_isMultiplayer;
    bool m_isGameOver;
    bool m_levelNeedsInit;

    // Objects.
    ScoreHUD   ::UPtr m_pScoreHUD;
    LevelHUD   ::UPtr m_pLevelHUD;
    LivesHUD   ::UPtr m_pLivesHUD;
    GameOverHUD::UPtr m_pGameOverHUD;
    LaserHolder::UPtr m_pLaserHolder;

    Player::UPtr m_pPlayer1;
    Player::UPtr m_pPlayer2;
    Player      *m_pCurrPlayerRef; //Weak Reference.

}; // class GameManager
}  // namespace CosmicIntruders
