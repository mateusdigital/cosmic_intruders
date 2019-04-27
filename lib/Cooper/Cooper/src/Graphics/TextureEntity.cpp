//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : TextureEntity.cpp                                             //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#include "include/Graphics/TextureEntity.h"
// Cooper
#include "include/Game/RES.h"
#include "include/Graphics/Graphics.h"

// Usings
using namespace Cooper;


//------------------------------------------------------------------------//
// CTOR / DTOR                                                            //
//------------------------------------------------------------------------//
TextureEntity::TextureEntity(
    const std::string &path,
    const Vec2        &pos,  /* = Vec2::Zero()      */
    const SDL_Rect    &rect  /* = SDL_Rect{0,0,0,0} */) :
    // Base.
    Entity   (pos),
    // Members.
    m_pTexture  (       nullptr),
    m_renderRect(Math::RectZero),
    m_flip      ( SDL_FLIP_NONE),
    m_opacity   (          1.0f)
{
    // Get the texture.
    m_pTexture = RES::GetTexture(path);

    // The function will calculate the actual rectangle.
    RenderRect(rect);
}

TextureEntity::~TextureEntity()
{
    m_pTexture = nullptr;
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void TextureEntity::Render()
{
    //--------------------------------------------------------------------------
    // We're fully transparent - So don't need spend cycles drawing it.
    if(m_opacity <= 0.0f || !Visible())
        return;

    //--------------------------------------------------------------------------
    // RenderTexture.
    m_pGraphicsRef->RenderTexture(
        m_pTexture,
        m_renderRect,
        BoundingRect(),
        0,
        SDL_Point{},
        SDL_RendererFlip(m_flip),
        m_opacity

    );
}
