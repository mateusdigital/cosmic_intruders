//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Typewritter.h                                                 //
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
#include <functional> //std::function
#include <string>
// Cooper
#include "Cooper/Cooper.h"

namespace CosmicIntruders {

class Typewritter
    : public Cooper::TextEntity
{
    //----------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                               //
    //----------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(Typewritter);

    typedef std::function<void ()> OnFinishCallback;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Typewritter(
        const std::string &contents,
        const std::string &fontPath,
        int                fontSize);


    //------------------------------------------------------------------------//
    // Action Functions                                                       //
    //------------------------------------------------------------------------//
public:
    void Start();

    void Configure(float totalTime, const OnFinishCallback &callback);


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;


    //------------------------------------------------------------------------//
    // Render Rect Helpers                                                    //
    //------------------------------------------------------------------------//
private:
    void CalculateRenderRect();



    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    int m_currentIndex;

    float m_totalTime;
    float m_currTime;
    float m_updateTime;

    bool m_started;
    bool m_finished;

    int m_charsCount;

    OnFinishCallback m_onFinish;

}; // class Typewritter
}  // namespace CosmicIntruders
