//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Graphics.h                                                    //
//  Project   : Cooper                                                        //
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
#include <memory> //shared_ptr
#include <string>
// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// Cooper
#include "include/Macros/Macros.h"
#include "include/Math/Math.h"

namespace Cooper {

class Graphics
{
    //------------------------------------------------------------------------//
    // Singleton                                                              //
    //------------------------------------------------------------------------//
public:
    COOPER_SINGLETON_OF(Graphics);


    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                    //
    //------------------------------------------------------------------------//
public:
    static void Init(
        int windowWidth,
        int windowHeight,
        int contentWidth,
        int contentHeight,
        const std::string &caption
    );
    static void Shutdown();

    static bool Initialized();


    //------------------------------------------------------------------------//
    // Screen Functions                                                       //
    //------------------------------------------------------------------------//
public:
    inline Vec2 GetScreenSize  () const { return Vec2(m_width, m_height); }
    inline int  GetScreenWidth () const { return m_width;  }
    inline int  GetScreenHeight() const { return m_height; }

    inline const std::string& GetScreenCaption() const { return m_caption; }
    void SetScreenCaption(const std::string &caption);


    //------------------------------------------------------------------------//
    // Texture Creation Functions                                             //
    //------------------------------------------------------------------------//
public:
    SDL_Texture* LoadTexture(const std::string &path);

    SDL_Texture* CreateTexture(
        int    width,
        int    height,
        Uint32 format = SDL_PIXELFORMAT_ARGB8888,
        int    access = SDL_TEXTUREACCESS_STATIC)
    {
        COOPER_ASSERT(m_initialized, "Graphics isn't initialized.");

        auto p_texture = SDL_CreateTexture(
            m_pRenderer,
            format,
            access,
            width,
            height
        );

        COOPER_VERIFY(
            p_texture, //Texture must be not null...
            "Failed to create texture!\nSDL_Error: %s",
            SDL_GetError()
        );

        return p_texture;
    }


    //--------------------------------------------------------------------------
    // NOT MANAGED!
    //   Users must call SDL_DestroyTexture() themselves or
    //   a memory leak will occur.
    SDL_Texture* CreateFontTexture(
        TTF_Font          *pFont,
        const std::string &contents,
        SDL_Color          color);

    //--------------------------------------------------------------------------
    // MANAGED!
    //   The destruction of this texture is handled by the std::shared_ptr
    //   itself, so users don't need to worry about memory leaks.
    std::shared_ptr<SDL_Texture> CreateFontTextureManaged(
        TTF_Font          *pFont,
        const std::string &contents,
        SDL_Color          color);


    //------------------------------------------------------------------------//
    // Rendering Functions                                                    //
    //------------------------------------------------------------------------//
public:
    inline void SetClearColor(const SDL_Color &c)
    {
        COOPER_ASSERT(m_initialized, "Graphics isn't initialized.");

        m_clearColor = c;
        SDL_SetRenderDrawColor(m_pRenderer, c.r, c.g, c.b, 0xFF);
    }

    inline void Clear()
    {
        COOPER_ASSERT(m_initialized, "Graphics isn't initialized.");
        SDL_RenderClear(m_pRenderer);
    }

    inline void Present()
    {
        COOPER_ASSERT(m_initialized, "Graphics isn't initialized.");
        SDL_RenderPresent(m_pRenderer);
    }

    void Begin() {
        SDL_SetRenderTarget(m_pRenderer, m_pRenderTexture);
    }

    void End() {
        SDL_SetRenderTarget(m_pRenderer, nullptr);
        SDL_RenderCopy(m_pRenderer, m_pRenderTexture, nullptr, nullptr);
        Present();
    }

    //--------------------------------------------------------------------------
    // Texture.
    void RenderTexture(
        SDL_Texture      *pTexture,
        const SDL_Rect   &srcRrect,
        const SDL_Rect   &dstRrect,
        float            angleDegrees,
        const SDL_Point  &origin,
        SDL_RendererFlip flip    = SDL_FLIP_NONE,
        float            opacity = 1.0f);


    //--------------------------------------------------------------------------
    // Rectangle.
    void RenderRect(const SDL_Rect &rect, const SDL_Color &c = Math::ColorWhite);

    //--------------------------------------------------------------------------
    // Circle.
    void RenderCircle(
        const Vec2      &center,
        float            radius,
        const SDL_Color &color = Math::ColorWhite,
        int              sides = -1);

    //--------------------------------------------------------------------------
    // Line.
    void RenderLine(const Vec2 &start, const Vec2 &end, const SDL_Color& c);


    //------------------------------------------------------------------------//
    // iVars.                                                                 //
    //------------------------------------------------------------------------//
public:
    // Control.
    bool      m_initialized;
    SDL_Color m_clearColor;

    // Window.
    int         m_width;
    int         m_height;
    std::string m_caption;

    // SDL.
    SDL_Window   *m_pWindow;
    SDL_Renderer *m_pRenderer;

    SDL_Texture *m_pRenderTexture;
}; //class Graphics
} //namespace Cooper
