//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : main.cpp                                                      //
//  Project   : Cosmic Intruders                                              //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/Helpers/SceneHelper.h"
#include "Game/include/Helpers/Storage.h"


//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    // Init
    Cooper::Log     ::Init();
    Cooper::Graphics::Init(
        800 * 0.7, 730 * 0.7,
        800, 730,
        CosmicIntruders::GameUtils::kWindowCaption
    );
    Cooper::RES     ::Init(CosmicIntruders::GameUtils::kBaseAssetsPath);
    Cooper::Input   ::Init();
    Cooper::Sound   ::Init();
    Cooper::Game    ::Init(60);

    #ifndef COOPER_DEBUG // Release Mode.
        Cooper::Log::SetLogLevel(Cooper::Log::LOG_LEVEL_NONE);
    #endif //COOPER_DEBUG

    //--------------------------------------------------------------------------
    // Run game.
    CosmicIntruders::GameUtils::Init();
    CosmicIntruders::Storage  ::Init();

    CosmicIntruders::SceneHelper::GoToSplashScene();
    Cooper::Game::Instance()->Run();

    //--------------------------------------------------------------------------
    // Shutdown
    Cooper::Game    ::Shutdown();
    Cooper::Input   ::Shutdown();
    Cooper::RES     ::Shutdown();
    Cooper::Graphics::Shutdown();
    Cooper::Log     ::Shutdown();

    return 0;
}
