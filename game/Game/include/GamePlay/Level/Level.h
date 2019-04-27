//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Level.h                                                       //
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
#include "Game/include/GamePlay/Cannon/Cannon.h"
#include "Game/include/GamePlay/Formation/Formation.h"
#include "Game/include/GamePlay/Scenery/Shield.h"
#include "Game/include/GamePlay/Scenery/Ground.h"
#include "Game/include/GamePlay/UFO/UFO.h"


namespace CosmicIntruders {
//Forward declarations.
class GameManager;
class LaserHolder;
class LevelHUD;
class Player;
class ScoreHUD;

class Level
    : Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(Level);

private:
    enum class AnimationStates {
        // Initial Animations.
        LevelHUD,
        Formation,
        // Player Death Animations.
        CannonExploding,
        // Not Animating.
        NotAnimating
    };


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     explicit Level(Player *pPlayerRef);
    ~Level() override;


    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
public:
    inline void Init () { InitObjects (); }
    inline void Setup() { SetupObjects(); }
private:
    void InitObjects ();
    void SetupObjects();


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void        Start      ();
    inline bool Started    () { return m_levelWasStarted; }
    inline bool IsLevelOver() { return m_levelIsOver;     }
private:
    void End();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;
    void Render() override;

    //--------------------------------------------------------------------------
    // Update Helpers.
private:
    void UpdateGameplay();

    void UpdateAnimationLevelHUD   ();
    void UpdateAnimationFormation  ();
    void UpdateAnimationPlayerDeath();


    //------------------------------------------------------------------------//
    // Input                                                                  //
    //------------------------------------------------------------------------//
private:
    void         UpdateInput     ();
    Cooper::Vec2 HandleMoveInput ();
    bool         HandleShootInput();


    //------------------------------------------------------------------------//
    // Collisions                                                             //
    //------------------------------------------------------------------------//
private:
    void HandleCollisions();

    void HandleCollisions_CannonLasers();
    void HandleCollisions_AlienLasers ();
    void HandleCollisions_Aliens      ();


    //------------------------------------------------------------------------//
    // Score Functions                                                        //
    //------------------------------------------------------------------------//
private:
    void UpdateScore(int amount);


    //------------------------------------------------------------------------//
    // State Change Functions                                                 //
    //------------------------------------------------------------------------//
private:
    void PlayerWasHit();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    //--------------------------------------------------------------------------
    // Control.
    AnimationStates m_currentAnimationState;
    bool            m_playerWasKilled;
    bool            m_levelWasStarted;
    bool            m_levelIsOver;
    bool            m_keyboardHasControl;

    //--------------------------------------------------------------------------
    // Objects.
    Cannon     ::UPtr m_pCannon;
    Formation  ::UPtr m_pFormation;
    UFO        ::UPtr m_pUFO;

    std::array<Shield::UPtr, 4> m_shields;
    Ground::UPtr                m_pGround;

    //--------------------------------------------------------------------------
    // Weak references - Cached for performance (and convenience)!
    GameManager *m_pGameMgrRef;
    Player      *m_pPlayerRef;
    ScoreHUD    *m_pScoreHUDRef;
    LevelHUD    *m_pLevelHUDRef;
    LaserHolder *m_pLaserHolderRef;

}; // class Level
}  // namespace CosmicIntruders
