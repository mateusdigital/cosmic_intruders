//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : IGamePlayObject.h                                             //
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

// Cooper
#include "Cooper/Cooper.h"
// Cosmic Intruders
#include "Game/include/Helpers/Bounds.h"

namespace CosmicIntruders {

class IGamePlayObject
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    // Enums.
    enum class States {
        Alive,
        Dead,
        Exploding
    };

    // Typedefs.
    COOPER_SMART_PTRS_OF(IGamePlayObject);
    typedef std::function<void ()> OnDeathCallback;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    IGamePlayObject(const Cooper::Vec2 &speed, const Bounds &moveBounds);


    //------------------------------------------------------------------------//
    // State Functions                                                        //
    //------------------------------------------------------------------------//
public:
    inline States State    () const { return m_state;                      }
    inline bool   Alive    () const { return m_state == States::Alive;     }
    inline bool   Dead     () const { return m_state == States::Dead;      }
    inline bool   Exploding() const { return m_state == States::Exploding; }


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    virtual void Reset  ();
    virtual void Explode();
    virtual void Kill   ();


    //------------------------------------------------------------------------//
    // Speed Functions                                                        //
    //------------------------------------------------------------------------//
public:
    // Getters.
    inline const Cooper::Vec2& Speed() const { return m_speed; }
    // Setters.
    inline void Speed(const Cooper::Vec2 &speed) { m_speed = speed; }


    //------------------------------------------------------------------------//
    // Movement Bounds Functions                                              //
    //------------------------------------------------------------------------//
public:
    // Getters.
    inline const Bounds& MoveBounds() const { return m_moveBounds; }
    // Setters.
    inline void MoveBounds(const Bounds &bounds) { m_moveBounds = bounds; }
    // Query.
    bool IsOutsideMoveBounds() const;


    //------------------------------------------------------------------------//
    // Collision Functions                                                    //
    //------------------------------------------------------------------------//
public:
    bool CollidesWith(const IGamePlayObject *that) const;


    //------------------------------------------------------------------------//
    // Callback Functions                                                     //
    //------------------------------------------------------------------------//
public:
    inline void OnDeath(const OnDeathCallback &c) { m_onDeath = c; }


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    //--------------------------------------------------------------------------
    //  Base Update.
    void Update() override;

    //--------------------------------------------------------------------------
    //  States Updates.
    virtual void UpdateAlive    ();
    virtual void UpdateExploding()  = 0;
    virtual void UpdateDead     ();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Control.
    States       m_state;
    // Movement.
    Cooper::Vec2 m_speed;
    Bounds       m_moveBounds;
    // Callbacks.
    OnDeathCallback m_onDeath;

}; // class IGamePlayObject
}  // namespace CosmicIntruders
