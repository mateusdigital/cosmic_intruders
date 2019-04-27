//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Typewritter.cpp                                               //
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
#include "Game/include/Helpers/Typewritter.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Typewritter::Typewritter(
    const std::string &contents,
    const std::string &fontPath,
    int                fontSize) :
    // Base.
    Cooper::TextEntity(fontPath, fontSize, contents),
    // Members.
    m_currentIndex(0),
    m_totalTime   (0),
    m_currTime    (0),
    m_updateTime  (0),
    m_started     (false),
    m_finished    (false),
    m_charsCount  (contents.size()),
    m_onFinish    (nullptr)
{
    CalculateRenderRect();
}


//----------------------------------------------------------------------------//
// Action Functions                                                           //
//----------------------------------------------------------------------------//
void Typewritter::Start()
{
    m_currentIndex = 0;
    m_currTime     = m_updateTime;
    m_started      = true;
    m_finished     = false;

    RenderRect(Cooper::Math::RectZero);
}

void Typewritter::Configure(float totalTime, const OnFinishCallback &callback)
{
    m_totalTime  = totalTime;
    m_updateTime = m_totalTime / m_charsCount;
    m_onFinish   = callback;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void Typewritter::Update()
{
    //--------------------------------------------------------------------------
    // We're done here.
    if(!m_started || m_finished)
        return;

    //--------------------------------------------------------------------------
    // Check if enough time has been passed.
    m_currTime -= m_pGameRef->GetTimer()->DeltaTime();
    if(m_currTime < 0)
    {
        //----------------------------------------------------------------------
        // Check if we're already displayed all chars.
        if(m_currentIndex > m_charsCount)
        {
            m_finished = true;

            if(m_onFinish)
                m_onFinish();
        }
        else
        {
            CalculateRenderRect();
            ++m_currentIndex;
            m_currTime = m_updateTime;
        }
    }
}


//----------------------------------------------------------------------------//
// Render Rect Helpers                                                        //
//----------------------------------------------------------------------------//
void Typewritter::CalculateRenderRect()
{
    const auto& size        = Size();
    auto        char_width  = (size.x / m_charsCount);

    auto rect = Cooper::Math::MakeRect(
        0.0f,
        0.0f,
        char_width * m_currentIndex,
        size.y
    );

    RenderRect(rect);
}
