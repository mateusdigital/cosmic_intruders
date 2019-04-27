//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : SplashScreen.cpp                                              //
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
#include <Game/include/Helpers/SceneHelper.h>
#include "Game/include/Scenes/SplashScene.h"
#include "Game/include/Helpers/GameUtils.h"

// Usings
using namespace CosmicIntruders;

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kAtlasName_Cow = "AmazingCow_Logo";
constexpr auto kAtlasName_N2O = "N2OMatt_Logo";

constexpr auto kSoundName_Intro = "Intro.wav";


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
SplashScene::SplashScene() :
     // Members.
    m_pTexture(nullptr),
    m_isFinalTween(false)
{
    //--------------------------------------------------------------------------
    // Set the background.
    Cooper::Graphics::Instance()->SetClearColor(Cooper::Math::ColorWhite);

    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::SplashAtlasPath());

    //--------------------------------------------------------------------------
    // Setup the texture and render rects.
    m_pTexture = p_atlas->Texture  (kAtlasName_Cow);
    m_n2oRect  = p_atlas->Rectangle(kAtlasName_N2O);

    m_pTexture->Position(
        m_pGraphicsRef->GetScreenSize() * 0.5f
    );

    //--------------------------------------------------------------------------
    // Load the sounds
    auto sound_name = GameUtils::GetSoundsPath(kSoundName_Intro);
    Cooper::Sound::PreloadSound({sound_name});

    //--------------------------------------------------------------------------
    // Setup the tween.
    m_animTweenUp
        .From(0).To(1).In(1.0f)
        .OnChange([this](float v){
            m_pTexture->Opacity(v);
        })
        .OnFinish([this](){
            m_animTweenDown.Start();
        })
        .OnStart([this, sound_name]() {
            if(!m_isFinalTween)
                Cooper::Sound::PlaySound(sound_name);
        })
        .Start();

    m_animTweenDown
        .From(0).To(1).In(1.0f)
        .OnChange([this](float v){ m_pTexture->Opacity(1.0f -v); })
        .OnFinish([this](){
            // Ended the Splash Scene animation.
            if(m_isFinalTween)
            {
                SceneHelper::GoToMenuScene();
                return;
            }

            m_pTexture->RenderRect(m_n2oRect);
            m_isFinalTween = true;
            m_animTweenUp.Start();
        });
}



//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void SplashScene::Update()
{
    auto dt = m_pGameRef->GetTimer()->DeltaTime();

    m_animTweenUp  .Update(dt);
    m_animTweenDown.Update(dt);
}

void SplashScene::Render()
{
    m_pTexture->Render();
}
