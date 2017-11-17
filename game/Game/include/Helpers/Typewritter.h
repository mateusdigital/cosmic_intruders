//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Typewritter.h                                                 //
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
