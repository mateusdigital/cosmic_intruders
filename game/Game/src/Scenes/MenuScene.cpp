//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : MenuScene.cpp                                                 //
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
#include "Game/include/Scenes/MenuScene.h"
// CosmicIntruders
#include "Game/include/Helpers/GameUtils.h"
#include "Game/include/Helpers/SceneHelper.h"
#include "Game/include/Helpers/Storage.h"

// Usings
using namespace CosmicIntruders;


//----------------------------------------------------------------------------//
// MACROS                                                                     //
//----------------------------------------------------------------------------//
#define SECONDS_IN_MS(_value_) int((_value_) * 1000)

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Positions.
constexpr auto kPlay_RelativePosition     = Cooper::Vec2(0.5f, 0.25f);
constexpr auto kMessage_RelativePosition  = Cooper::Vec2(0.5f, 0.90f);
constexpr auto kGameMode_RelativePosition = Cooper::Vec2(0.5f, 0.74f);
//------------------------------------------------------------------------------
// Gaps.
constexpr auto kGap_LogoText            = Cooper::Vec2(0,  50);
constexpr auto kGap_ScoreChartTitleText = Cooper::Vec2(0,  70);

constexpr auto kGap_MisteryItemText = Cooper::Vec2(30, 50);
constexpr auto kGap_MisteryItemIcon = Cooper::Vec2(-5,  0);

constexpr auto kGap_ScoreItemsText = Cooper::Vec2(  0, 40);
constexpr auto kGap_ScoreItemsIcon = Cooper::Vec2(-15,  0);
//------------------------------------------------------------------------------
// Paddings.
constexpr auto kPadding_ScoreIcon = Cooper::Vec2(0, -2);
//------------------------------------------------------------------------------
// Durations.
constexpr auto kDuration_PlayAndLogo   = 0.5f;
constexpr auto kDuration_ScoreItems    = 0.5f;
constexpr auto kDelay_TitleToLogo      = 0.3f;
constexpr auto kDelay_LogoToScoreChart = 0.5f;
//------------------------------------------------------------------------------
// Text Content Values.
constexpr auto kString_Play            = "P L A Y";
constexpr auto kString_Logo            = "C O S M I C   I N T R U D E R S";
constexpr auto kString_ScoreChartTitle = "* S C O R E   A D V A N C E  T A B L E *";
constexpr auto kString_Mistery         = "=  ? ?   P O I N T S";
constexpr auto kString_Mage            = "=  3 0   P O I N T S";
constexpr auto kString_Shooter         = "=  2 0   P O I N T S";
constexpr auto kString_Blocker         = "=  1 0   P O I N T S";
constexpr auto kString_Message         = "C R E A T E D   W I T H  <3  F O R  M I N I C L I P !";
constexpr auto kString_GameMode        = "G A M E  M O D E";
constexpr auto kString_GameMode1       = "1  -  P L A Y E R";
constexpr auto kString_GameMode2       = "2  -  P L A Y E R S";
//------------------------------------------------------------------------------
// Atlas Frame names.
constexpr auto kAtlasName_Mistery = "UFO_Alive";
constexpr auto kAtlasName_Mage    = "AlienMage_Frame1";
constexpr auto kAtlasName_Shooter = "AlienShooter_Frame1";
constexpr auto kAtlasName_Blocker = "AlienBlocker_Frame1";
//------------------------------------------------------------------------------
// Buttons.
constexpr auto kButtonsCount         = 2;
constexpr auto kButton_SelectedColor = Cooper::Math::MakeColor(244, 34, 43);
constexpr auto kButton_NormalColor   = Cooper::Math::ColorWhite;

constexpr auto kButton_IndexSingle   = 0;
constexpr auto kButton_IndexMulti    = 1;
constexpr auto kButton_IndexCredits  = 2;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
MenuScene::MenuScene()
{
    //--------------------------------------------------------------------------
    // Set the background.
    m_pGraphicsRef->SetClearColor(Cooper::Math::ColorBlack);

    //--------------------------------------------------------------------------
    // Create the Menu Objects.
    CreateScoreHUD  ();
    CreateTitle     ();
    CreateScoreChart();
    CreateButtons   ();
    CreateMessage   ();

    //--------------------------------------------------------------------------
    // Setup the button logic.
    m_selectedButtonIndex = 0;
    UpdateButtonSelection();
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void MenuScene::Update()
{
    //--------------------------------------------------------------------------
    // Play / Logo
    m_pPlay->Update();
    m_pLogo->Update();

    //--------------------------------------------------------------------------
    // Score chart.
    m_pScoreChartTitle->Update();

    m_pMisteryText->Update();
    m_pMageText   ->Update();
    m_pShooterText->Update();
    m_pBlockerText->Update();

    //--------------------------------------------------------------------------
    // Message.
    m_messageTween.Update(m_pGameRef->GetTimer()->DeltaTime());

    //--------------------------------------------------------------------------
    // Input.
    HandleInput();
}

void MenuScene::Render()
{
    //--------------------------------------------------------------------------
    // ScoreHUD
    m_pScoreHUD->Render();

    //--------------------------------------------------------------------------
    // Play / Logo
    m_pPlay->Render();
    m_pLogo->Render();

    //--------------------------------------------------------------------------
    // Score chart.
    m_pScoreChartTitle->Render();

    m_pMisteryText->Render();
    m_pMisteryIcon->Render();

    m_pMageText->Render();
    m_pMageIcon->Render();

    m_pShooterText->Render();
    m_pShooterIcon->Render();

    m_pBlockerText->Render();
    m_pBlockerIcon->Render();

    //--------------------------------------------------------------------------
    // Buttons.
    m_pGameModeText->Render();
    for(int i = 0; i < kButtonsCount; ++i)
        m_buttonsTexts[i]->Render();

    //--------------------------------------------------------------------------
    // Message.
    m_pMessageText->Render();
    m_pMessageIcon->Render();
}


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Object Groups.
void MenuScene::CreateScoreHUD()
{
    m_pScoreHUD = Cooper::make_unique<ScoreHUD>(0,0);
}

void MenuScene::CreateTitle()
{
    //--------------------------------------------------------------------------
    // Just to reduce verbosity and cache.
    auto screen_size = m_pGraphicsRef->GetScreenSize();

    //--------------------------------------------------------------------------
    //  Play
    m_pPlay = CreateTypewriter(
        nullptr,
        kString_Play,
        screen_size * kPlay_RelativePosition,
        kDuration_PlayAndLogo,
        [this](){ m_pLogo->Start(); }
    );
    m_pPlay->Start();

    //--------------------------------------------------------------------------
    //  Logo
    m_pLogo = CreateTypewriter(
        m_pPlay.get(),
        kString_Logo,
        kGap_LogoText,
        kDuration_PlayAndLogo,
        [this]() {
            SDL_Delay(SECONDS_IN_MS(kDelay_TitleToLogo));
            m_pScoreChartTitle->Start();
        }
    );
}

void MenuScene::CreateScoreChart()
{
    //--------------------------------------------------------------------------
    //  Score Chart
    m_pScoreChartTitle = CreateTypewriter(
        m_pLogo.get(),
        kString_ScoreChartTitle,
        kGap_ScoreChartTitleText,
        0.0f, // Instant.
        [this]() {
            SDL_Delay(SECONDS_IN_MS(kDelay_LogoToScoreChart));
            m_pMisteryIcon->Visible(true);
            m_pMisteryText->Start();
        }
    );

    //--------------------------------------------------------------------------
    //  Mystery Score
    m_pMisteryText = CreateTypewriter(
        m_pScoreChartTitle.get(),
        kString_Mistery,
        kGap_MisteryItemText,
        kDuration_ScoreItems,
        [this]() {
            m_pMageIcon->Visible(true);
            m_pMageText->Start();
        }
    );
    m_pMisteryIcon = CreateIcon(
        m_pMisteryText.get(),
        kAtlasName_Mistery,
        kGap_MisteryItemIcon
    );

    //--------------------------------------------------------------------------
    //  Mage Score
    m_pMageText = CreateTypewriter(
        m_pMisteryText.get(),
        kString_Mage,
        kGap_ScoreItemsText,
        kDuration_ScoreItems,
        [this]() {
            m_pShooterIcon->Visible(true);
            m_pShooterText->Start();
        }
    );
    m_pMageIcon = CreateIcon(
        m_pMageText.get(),
        kAtlasName_Mage,
        kGap_ScoreItemsIcon
    );

    //--------------------------------------------------------------------------
    //  Shooter Score
    m_pShooterText = CreateTypewriter(
        m_pMageText.get(),
        kString_Shooter,
        kGap_ScoreItemsText,
        kDuration_ScoreItems,
        [this]() {
            m_pBlockerIcon->Visible(true);
            m_pBlockerText->Start();
        }
    );
    m_pShooterIcon = CreateIcon(
        m_pShooterText.get(),
        kAtlasName_Shooter,
        kGap_ScoreItemsIcon
    );

    //--------------------------------------------------------------------------
    //  Blocker Score
    m_pBlockerText = CreateTypewriter(
        m_pShooterText.get(),
        kString_Blocker,
        kGap_ScoreItemsText,
        kDuration_ScoreItems,
        [this]() {
            m_messageTween.Start();
        }
    );
    m_pBlockerIcon = CreateIcon(
        m_pBlockerText.get(),
        kAtlasName_Blocker,
        kGap_ScoreItemsIcon
    );
}

void MenuScene::CreateButtons()
{
    //--------------------------------------------------------------------------
    // Just to reduce verbosity and cache.
    using namespace Cooper;

    const auto &path        = GameUtils::GameFontPath();
    const auto  size        = GameUtils::GameFontSize() - 2;
    const auto &color       = Math::ColorWhite;
    const auto &screen_size = m_pGraphicsRef->GetScreenSize();

    //--------------------------------------------------------------------------
    // Create the Game Mode.
    m_pGameModeText = make_unique<TextEntity>(path, size, kString_GameMode, color);
    m_pGameModeText->Position(screen_size * kGameMode_RelativePosition);

    //--------------------------------------------------------------------------
    // Create the Buttons.
    m_buttonsTexts[0] = make_unique<TextEntity>(path, size, kString_GameMode1, color);
    m_buttonsTexts[1] = make_unique<TextEntity>(path, size, kString_GameMode2, color);

    //--------------------------------------------------------------------------
    // Set their positions.
    for(int i = 0; i < kButtonsCount; ++i)
    {
        //----------------------------------------------------------------------
        // Set their gaps - This is a little "hacky".
        // We want make them a little bit more spaced from each other
        // so we're adding some gaps here.
        m_buttonsTexts[i]->Position(
            screen_size * Cooper::Vec2(0.33f * (i+1), 0.8f)
        );
    }
}

void MenuScene::CreateMessage()
{
    //--------------------------------------------------------------------------
    // Just to reduce verbosity and cache.
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    const auto &screen_size = m_pGraphicsRef->GetScreenSize();
    const auto  path        = GameUtils::GameFontPath();
    const auto &size        = GameUtils::GameFontSize();

    //--------------------------------------------------------------------------
    // Message Text.
    m_pMessageText = Cooper::make_unique<Cooper::TextEntity>(
        path,
        size,
        kString_Message,
        Cooper::Math::ColorWhite
    );

    m_pMessageText->Position(screen_size * kMessage_RelativePosition);
    m_pMessageText->RenderRect(
        Cooper::Math::MakeRect(0.0, 0.0, 0.0, m_pMessageText->Size().y)
    );

    //--------------------------------------------------------------------------
    // Message Icon.
    m_pMessageIcon = p_atlas->Texture(kAtlasName_Mistery);
    m_pMessageIcon->Origin  (0.0f, 0.5f);
    m_pMessageIcon->Position(
        -m_pMessageIcon->Size    ().x,
         m_pMessageText->Position().y
    );

    //--------------------------------------------------------------------------
    // Message Tween.
    m_messageTween
        .From(m_pMessageIcon->Position().x)
        .To  (screen_size.x + m_pMessageIcon->Size().x)
        .In  (5.0f)
        .OnChange([this](float v){
            m_pMessageIcon->Position(v, m_pMessageText->Position().y);

            //------------------------------------------------------------------
            // Calculate the Message properties.
            auto message_size = m_pMessageText->Size();
            auto message_left = m_pMessageText->Position().x - message_size.x * 0.5f;

            //------------------------------------------------------------------
            // Already shown the whole message.
            if(v > message_left + message_size.x)
                return;

            //------------------------------------------------------------------
            // Make the message appears.
            m_pMessageText->RenderRect(
                Cooper::Math::MakeRect(
                    0.0,
                    0.0,
                    v - message_left,
                    message_size.y
                )
            );
        });
}

//------------------------------------------------------------------------------
// Objects.
Typewritter::UPtr MenuScene::CreateTypewriter(
    Typewritter                         *pParent,
    const std::string                   &text,
    const Cooper::Vec2                  &position,
    float                               time,
    const Typewritter::OnFinishCallback &callback)
{
    //--------------------------------------------------------------------------
    // Create Typewriter.
    auto p_obj = Cooper::make_unique<Typewritter>(
        text,
        GameUtils::GameFontPath(),
        GameUtils::GameFontSize()
    );

    //--------------------------------------------------------------------------
    // Set properties.
    p_obj->Parent  (pParent);
    p_obj->Position(position);
    p_obj->Color   (Cooper::Math::ColorWhite);

    //--------------------------------------------------------------------------
    // Configure.
    p_obj->Configure(time, callback);

    return p_obj;
}

Cooper::TextureEntity::UPtr MenuScene::CreateIcon(
    Typewritter        *pParent,
    const std::string  &name,
    const Cooper::Vec2 &position)
{
    auto p_atlas = Cooper::RES::GetAtlas(GameUtils::GameAtlasPath());

    //--------------------------------------------------------------------------
    // Calculate Half of parent width.
    // We do this because we want that the icon be placed at the left
    // of the Score Text.
    auto parent_hwidth = (pParent->Size() * Cooper::Vec2(0.5f, 0.0f));

    //--------------------------------------------------------------------------
    // Create Icon
    auto p_icon = p_atlas->Texture(name);

    //--------------------------------------------------------------------------
    // Set Properties.
    p_icon->Parent  (pParent);
    p_icon->Origin  (1.0f, 0.5f);
    p_icon->Visible (false);
    p_icon->Position(
        position + kPadding_ScoreIcon - parent_hwidth
    );

    return p_icon;
}


//------------------------------------------------------------------------------
// Button selection.
void MenuScene::UpdateButtonSelection()
{
    for(int i = 0; i < kButtonsCount; ++i)
    {
        m_buttonsTexts[i]->Color(
            (i == m_selectedButtonIndex)
                ? kButton_SelectedColor
                : kButton_NormalColor
        );
    }
}


//--------------------------------------------------------------------------
// Scene Selection.
void MenuScene::GoToSelectedScene()
{
    if(m_selectedButtonIndex == kButton_IndexSingle)
        SceneHelper::GoToGameScene(false);

    else if(m_selectedButtonIndex == kButton_IndexMulti)
        SceneHelper::GoToGameScene(true);

}

//----------------------------------------------------------------------------//
// Input Functions                                                            //
//----------------------------------------------------------------------------//
void MenuScene::HandleInput()
{
    //--------------------------------------------------------------------------
    // Keyboard Input
    if(Cooper::Input::HasKeyboardInput())
    {
        auto delta = 0;

        if(Cooper::Input::KeyPress(SDL_SCANCODE_LEFT))
            delta = -1;
        if(Cooper::Input::KeyPress(SDL_SCANCODE_RIGHT))
            delta = +1;

        // Makes the selection wraps.
        if(delta != 0)
        {
            m_selectedButtonIndex = (m_selectedButtonIndex + delta) % kButtonsCount;
            if(m_selectedButtonIndex < 0)
                m_selectedButtonIndex = kButtonsCount-1;

            UpdateButtonSelection();
        }

        if(Cooper::Input::KeyPress(SDL_SCANCODE_SPACE ) ||
           Cooper::Input::KeyPress(SDL_SCANCODE_RETURN))
        {
            GoToSelectedScene();
            return;
        }
    }
    //--------------------------------------------------------------------------
    // Mouse Input
    else if(Cooper::Input::HasMouseInput())
    {
        //--------------------------------------------------------------------------
        // Button selection
        auto point        = Cooper::Math::MakePoint(Cooper::Input::MousePosition());
        auto left_pressed = Cooper::Input::MouseButtonPress(0);

        for(int i = 0; i < kButtonsCount; ++i)
        {
            auto rect  = m_buttonsTexts[i]->BoundingRect();
            if(!SDL_PointInRect(&point, &rect))
                continue;

            m_selectedButtonIndex = i;
            UpdateButtonSelection();

            if(left_pressed)
            {
                GoToSelectedScene();
                return;
            }
        }
    }
}
