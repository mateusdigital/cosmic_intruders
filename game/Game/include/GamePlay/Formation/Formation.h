//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Formation.h                                                   //
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
#include <vector>
// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/GamePlay/Enemy/Alien.h"


namespace CosmicIntruders {
// Forward declarations.
class LaserHolder;

class Formation
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(Formation);

private:
    typedef std::vector<Alien::SPtr> AlienLine;
    typedef std::vector<AlienLine>   AlienGrid;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Formation(const Cooper::Vec2 &gridSize, int currLevel);


    //------------------------------------------------------------------------//
    // Aliens Functions                                                       //
    //------------------------------------------------------------------------//
public:
    inline const std::vector<Alien *>& Aliens() const
    {
        return m_aliensVec;
    }

    inline int AliensCount() const
    {
        return int(m_gridSize.x * m_gridSize.y);
    }

    inline int AliveAliensCount() const
    {
        return m_aliveAliensCount;
    }

    void CompleteExplosions();


    //------------------------------------------------------------------------//
    //  Start Animation Functions                                             //
    //------------------------------------------------------------------------//
public:
    inline bool StartAnimationCompleted() const
    {
        return m_startAnimationCompleted;
    }

    void StartStartAnimation();


    //------------------------------------------------------------------------//
    // Movement Functions                                                     //
    //------------------------------------------------------------------------//
public:
    // Getters.
    const Cooper::Vec2 MovementDirection() const { return m_moveDirection; }

    int MovementStep() const { return m_moveStep; }

    // Control.
    inline void Start() { m_allowedToMove = true;  }
    inline void Stop () { m_allowedToMove = false; }

    void MoveUp();

    // Helpers.
private:
    bool IsMovingDown() const { return m_moveDirection.x == 0; }

    bool CheckEdgeHit();

    void CalculateMoveTimer     ();
    void DecideNextMoveDirection();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;
    void Render() override;

    // Helpers.
private:
    void UpdateStartAnimation();
    void UpdateMovement      ();


    //------------------------------------------------------------------------//
    // Aliens Helper Functions                                                //
    //------------------------------------------------------------------------//
private:
    void SetupAliens(const Cooper::Vec2 &gridSize);

    inline bool ThereIsAlienBellow(int y, int x) const
    {
        // Invalid bounds.
        if(y+1 >= m_gridSize.y)
            return false;

        bool a = m_aliens[y+1][x]->Alive();
        return a;
    }

    void HandleAlienShooting(int row, int col);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    // Control.
    int m_currLevel;

    // Start Animation.
    Cooper::Timer m_startAnimationTimer;
    bool          m_startAnimationStarted;
    bool          m_startAnimationCompleted;
    int           m_startAnimationIndex;

    // Movement.
    float         m_moveAnimationTime;
    Cooper::Vec2  m_moveDirection;
    int           m_moveDirectionIndex;
    Bounds        m_moveBounds;
    int           m_moveStep;
    int           m_moveSoundStep;
    float         m_timeToMove;
    bool          m_allowedToMove;
    int           m_movedDownCount;
    float         m_killMultiplier;

    // Aliens.
    AlienGrid            m_aliens;
    Cooper::Vec2         m_gridSize;
    int                  m_aliveAliensCount;
    int                  m_killedAliensCount;
    std::vector<Alien *> m_aliensVec; //Weak Reference - Used as a projection.

    //--------------------------------------------------------------------------
    // Weak References - Cached for Performance.
    LaserHolder *pLaserHolderRef;

}; // class Formation
}  // namespace CosmicIntruders
