//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Game.cpp                                                      //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/Game/Game.h"
// Cooper
#include "include/Graphics/Graphics.h"
#include "include/Input/Input.h"
#include "include/Log/Log.h"
//----------------------------------------------------------------------------//
// Conditional Headers
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
#endif //EMSCRIPTEN

// Usings
using namespace Cooper;


//----------------------------------------------------------------------------//
// Singleton                                                                  //
//----------------------------------------------------------------------------//
Game::Game()
{
    //Empty...
}

Game::~Game()
{
    //Empty...
}


//----------------------------------------------------------------------------//
// Lifecycle Functions.                                                       //
//----------------------------------------------------------------------------//
void Game::Init(int /** targetFPS **/)
{
    COOPER_ASSERT(!Instance()->m_initialized, "Game is already initialized.");

    //--------------------------------------------------------------------------
    // Cache stuff for performance.
    Instance()->m_pGraphics = Graphics::Instance();

    //--------------------------------------------------------------------------
    // Other stuff.
    Instance()->m_initialized = true;
}

void Game::Shutdown()
{
    COOPER_ASSERT(Instance()->m_initialized, "Game isn't initialized.");

    //--------------------------------------------------------------------------
    //  Complete denitialization.
    Instance()->m_initialized = false;
    Instance()->m_running     = false;
    Instance()->m_pGraphics   = nullptr;
}

bool Game::Initialized()
{
    return Instance()->m_initialized;
}


void Game::InnerRun()
{
    Game::Instance()->m_timer.Update();

    Game::Instance()->m_fpsTime += Game::Instance()->m_timer.DeltaTime();
    Game::Instance()->m_fpsFrames++;

    //--------------------------------------------------------------------------
    // Update the SDL event queue.
    static SDL_Event s_event {};
    while(SDL_PollEvent(&s_event) != 0)
    {
        if(s_event.type == SDL_QUIT)
            Game::Instance()->m_running = false;
    }

    //--------------------------------------------------------------------------
    // Process the game.
    Game::Instance()->PreUpdate ();
    Game::Instance()->Update    ();
    Game::Instance()->PostUpdate();

    Game::Instance()->Render();

    //--------------------------------------------------------------------------
    // Show the FPS info.
    if(Game::Instance()->m_fpsTime >= 1.0f)
    {
        Cooper::Log::I("FPS: %d", Game::Instance()->m_fpsFrames);
        Game::Instance()->m_fpsTime   = 0;
        Game::Instance()->m_fpsFrames = 0;
    }
}

void Game::Run()
{
    COOPER_ASSERT(Instance()->m_initialized, "Game isn't initialized.");

    Instance()->m_running = true;
    Instance()->m_timer.Reset();

    Instance()->m_fpsFrames = 0;
    Instance()->m_fpsTime   = 0;

    //--------------------------------------------------------------------------
    // Emscripten main loop works differently, so we need to pass a function
    // pointer and it will call us back regularly making a game loop.
    // Reference:
    //   https://kripken.github.io/emscripten-site/docs/porting/emscripten-runtime-environment.html#browser-main-loop
    #ifdef EMSCRIPTEN

        emscripten_set_main_loop(Game::InnerRun, 0, 1);

    #else // EMSCRIPTEN

        while(Instance()->m_running)
        {
            Game::InnerRun();

        }//while(m_running)

    #endif //EMSCRIPTEN
}


//----------------------------------------------------------------------------//
// Update Functions.                                                          //
//----------------------------------------------------------------------------//
void Game::PreUpdate()
{
    //COWNOTE(n2omatt): Empty by now...
}

void Game::Update()
{
    Input::Update();

    m_pBaseEntity->Update();
    m_timer.Reset();
}

void Game::PostUpdate()
{
    Input::PostUpdate();
}


//----------------------------------------------------------------------------//
// Render Functions                                                           //
//----------------------------------------------------------------------------//
void Game::Render()
{
    m_pGraphics->Begin();
        m_pGraphics->Clear();
            m_pBaseEntity->Render();
        m_pGraphics->Present();
    m_pGraphics->End();
}
