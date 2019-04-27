//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Player.cpp                                                    //
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
#include "Game/include/GamePlay/Player/Player.h"
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Enums / Constants / Typdefs                                                //
//----------------------------------------------------------------------------//
const int Player::kIndex_One = 0;
const int Player::kIndex_Two = 1;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Player::Player(int index) :
    // Members.
    m_index     (index),
    m_levelIndex(0),
    m_lives     (GameUtils::kDefaultLives),
    m_score     (0)
{
    m_pLevel = Cooper::make_unique<Level>(this);
    m_pLevel->Init();
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Player::StartLevel()
{
    m_pLevel->Start();
}
