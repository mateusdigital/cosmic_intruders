//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Timer.cpp                                                     //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/Timer/Timer.h"
// Cooper
#include "include/Macros/Macros.h"

// Usings
using namespace Cooper;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Timer::Timer() :
    m_startTime   (0),
    m_frequency   (SDL_GetPerformanceFrequency()), // COWTODO(n2omatt): Should this be static?
    m_deltaTime   (0),
    m_totalTime   (0),
    m_timeScale   (1),
    m_initialized (false)
{
    //Empty...
}


//----------------------------------------------------------------------------//
// Control Functions                                                          //
//----------------------------------------------------------------------------//
void Timer::Reset()
{
    m_startTime = SDL_GetPerformanceCounter();
    m_deltaTime = 0;
    m_totalTime = 0;

    m_initialized = true;
}

void Timer::Update()
{
    COOPER_ASSERT(m_initialized, "Timer isn't initialized - Call Reset().");
    Restart();
}

float Timer::Restart()
{
    auto current = SDL_GetPerformanceCounter();
    auto elapsed = current - m_startTime;
    m_startTime  = current;

    m_deltaTime  = float(elapsed) / float(m_frequency);
    m_totalTime += m_deltaTime;

    return m_deltaTime;
}
