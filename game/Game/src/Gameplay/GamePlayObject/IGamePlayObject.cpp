//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : IGamePlayObject.cpp                                           //
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
#include "Game/include/GamePlay/GamePlayObject/IGamePlayObject.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
IGamePlayObject::IGamePlayObject(
    const Cooper::Vec2 &speed,
    const Bounds       &moveBounds) :
    // Members.
    m_state     (States::Dead),
    m_speed     (speed       ),
    m_moveBounds(moveBounds  )
{
    //Empty...
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void IGamePlayObject::Reset()
{
    m_state = States::Alive;
}

void IGamePlayObject::Explode()
{
    m_state = States::Exploding;
}

void IGamePlayObject::Kill()
{
    //Already dead - Don't do nothing.
    if(Dead())
        return;

    m_state = States::Dead;
    if(m_onDeath)
        m_onDeath();
}


//----------------------------------------------------------------------------//
// Movement Bounds Functions                                                  //
//----------------------------------------------------------------------------//
bool IGamePlayObject::IsOutsideMoveBounds() const
{
    if(!Alive())
        return false;

    const auto &pos   = Position();
    auto       hsize  = Size() * Origin();

    auto left   = (pos.x - hsize.x < m_moveBounds.min.x);
    auto right  = (pos.x + hsize.x > m_moveBounds.max.x);
    auto top    = (pos.y - hsize.y < m_moveBounds.min.y);
    auto bottom = (pos.y + hsize.y > m_moveBounds.max.y);

    return left || right || top || bottom;
}


//----------------------------------------------------------------------------//
// Collision Functions                                                        //
//----------------------------------------------------------------------------//
bool IGamePlayObject::CollidesWith(const IGamePlayObject *that) const
{
    if(!this->Alive() || !that->Alive())
        return false;

    auto r1 = this->BoundingRect();
    auto r2 = that->BoundingRect();

    return SDL_HasIntersection(&r1, &r2);
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void IGamePlayObject::Update()
{
    //--------------------------------------------------------------------------
    // Forward the update to correct state handler.
    switch(m_state)
    {
        case States::Alive     : UpdateAlive    (); break;
        case States::Exploding : UpdateExploding(); break;
        case States::Dead      : UpdateDead     (); break;
    }
}


void IGamePlayObject::UpdateAlive()
{
    //--------------------------------------------------------------------------
    // Update position.
    DoTranslate(m_speed * m_pGameRef->GetTimer()->DeltaTime());
}

void IGamePlayObject::UpdateDead()
{
    // Nothing to do...
}
