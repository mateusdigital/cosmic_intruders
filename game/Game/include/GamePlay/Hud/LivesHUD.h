//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : LivesHUD.h                                                    //
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
// std
#include <array>
// Cooper
#include "Cooper/Cooper.h"

namespace CosmicIntruders {

class LivesHUD
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    // Typedefs.
    COOPER_SMART_PTRS_OF(LivesHUD);

    // Constants.
private:
    static constexpr auto kMaxVisibleCannons = 3;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     LivesHUD(bool multiplayer);
    ~LivesHUD() override = default;


    //------------------------------------------------------------------------//
    // Lives Functions                                                        //
    //------------------------------------------------------------------------//
public:
    // Setter.
    void Lives(int amount, int playerIndex);


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Render() override;


    //------------------------------------------------------------------------//
    // Init Functions                                                         //
    //------------------------------------------------------------------------//
private:
    void Init();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Control.
    bool m_multiplayerGame;

    // Player 1.
    Cooper::TextEntity::UPtr                                    m_pPlayer1Text;
    std::array<Cooper::TextureEntity::UPtr, kMaxVisibleCannons> m_player1Cannons;

    // Player 2.
    Cooper::TextEntity::UPtr                                    m_pPlayer2Text;
    std::array<Cooper::TextureEntity::UPtr, kMaxVisibleCannons> m_player2Cannons;

}; //class LivesHUD
}  //namespace CosmicIntruders
