//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Timer.h                                                       //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

// SDL
#include <SDL.h>

namespace Cooper {

class Timer
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     Timer();
    ~Timer() = default;


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    void Reset ();
    void Update();

    float Restart();


    //------------------------------------------------------------------------//
    // Delta Time                                                             //
    //------------------------------------------------------------------------//
public:
    inline float DeltaTime() const { return m_deltaTime; }


    //------------------------------------------------------------------------//
    // Total Time                                                             //
    //------------------------------------------------------------------------//
public:
    inline float TotalTime() const { return m_totalTime; }


    //------------------------------------------------------------------------//
    // Time Scale                                                             //
    //------------------------------------------------------------------------//
public:
    // Setter.
    inline void TimeScale(float timeScale = 1.0f) { m_timeScale = timeScale; }
    // Getter.
    inline float TimeScale() const { return m_timeScale; }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Uint64 m_startTime;
    Uint64 m_frequency;

    float m_deltaTime;
    float m_totalTime;
    float m_timeScale;

    bool m_initialized;

}; // class Timer
}  // namespace Cooper