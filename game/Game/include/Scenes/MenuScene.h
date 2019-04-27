//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : MenuScene.h                                                   //
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
#include <array>
// Cooper
#include "Cooper/Cooper.h"
// CosmicIntruders
#include "Game/include/GamePlay/Hud/ScoreHUD.h"
#include "Game/include/Helpers/Typewritter.h"


namespace CosmicIntruders {

class MenuScene
    : public Cooper::Entity
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     MenuScene();


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() override;
    void Render() override;


    //------------------------------------------------------------------------//
    // Helper Functions                                                       //
    //------------------------------------------------------------------------//
private:
    //--------------------------------------------------------------------------
    // Object groups.
    void CreateScoreHUD  ();
    void CreateTitle     ();
    void CreateScoreChart();
    void CreateButtons   ();
    void CreateMessage   ();

    //--------------------------------------------------------------------------
    // Objects.
    Typewritter::UPtr CreateTypewriter(
        Typewritter                         *pParent,
        const std::string                   &text,
        const Cooper::Vec2                  &position,
        float                               time,
        const Typewritter::OnFinishCallback &callback);

    Cooper::TextureEntity::UPtr CreateIcon(
        Typewritter        *pParent,
        const std::string  &name,
        const Cooper::Vec2 &position);

    //--------------------------------------------------------------------------
    // Button selection.
    void UpdateButtonSelection();

    //--------------------------------------------------------------------------
    // Scene Selection.
    void GoToSelectedScene();

    //------------------------------------------------------------------------//
    // Input Functions                                                        //
    //------------------------------------------------------------------------//
private:
    void HandleInput();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Score HUD.
    ScoreHUD::UPtr m_pScoreHUD;

    // Play / Logo.
    Typewritter::UPtr m_pPlay;
    Typewritter::UPtr m_pLogo;

    // Score Chart.
    Typewritter::UPtr m_pScoreChartTitle;

    // Mistery.
    Cooper::TextureEntity::UPtr m_pMisteryIcon;
    Typewritter::UPtr           m_pMisteryText;

    // Mage.
    Cooper::TextureEntity::UPtr m_pMageIcon;
    Typewritter::UPtr           m_pMageText;

    // Shooter.
    Cooper::TextureEntity::UPtr m_pShooterIcon;
    Typewritter::UPtr           m_pShooterText;

    // Blocker.
    Cooper::TextureEntity::UPtr m_pBlockerIcon;
    Typewritter::UPtr           m_pBlockerText;

    // Buttons.
    Cooper::TextEntity::UPtr                m_pGameModeText;
    std::array<Cooper::TextEntity::UPtr, 2> m_buttonsTexts;
    int                                     m_selectedButtonIndex;

    // Message.
    Cooper::TextureEntity::UPtr m_pMessageIcon;
    Cooper::TextEntity::UPtr    m_pMessageText;
    Cooper::Tween<float>        m_messageTween;
};

} //namespace CosmicIntruders
