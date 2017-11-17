//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ILaser.cpp                                                    //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

//Header
#include "Game/include/GamePlay/Laser/ILaser.h"

//Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
ILaser::ILaser(
    bool                explodeOnOutOfBounds,
    float               explodeTime,
    const Cooper::Vec2 &speed,
    const Bounds       &moveBounds) :
    // Base.
    IGamePlayObject(speed, moveBounds),
    // Members.
    m_outOfBoundsExplode (explodeOnOutOfBounds),
    m_explosionTime      (explodeTime),
    m_currExplositionTime(0)
{
    //Empty...
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void ILaser::Explode()
{
    IGamePlayObject::Explode();
    m_currExplositionTime = m_explosionTime;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void ILaser::UpdateAlive()
{
    IGamePlayObject::UpdateAlive();

    // Inside the playfield yet - Just continues...
    if(!IsOutsideMoveBounds())
        return;

    // Outsize of the playfield - So make the laser dead...
    (m_outOfBoundsExplode) ?  Explode() : Kill();
}

void ILaser::UpdateExploding()
{
    m_currExplositionTime -= m_pGameRef->Instance()->GetTimer()->DeltaTime();
    if(m_currExplositionTime <= 0)
        Kill();
}
