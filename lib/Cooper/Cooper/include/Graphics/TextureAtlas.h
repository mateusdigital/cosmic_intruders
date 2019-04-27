//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : TextureAtlas.h                                                //
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

// std
#include <map>
#include <string>
// Cooper
#include "include/Graphics/TextureEntity.h"
#include "include/Macros/Macros.h"


namespace Cooper {

class TextureAtlas
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    COOPER_SMART_PTRS_OF(TextureAtlas);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     explicit TextureAtlas(const std::string &path);

    ~TextureAtlas() = default;


    //------------------------------------------------------------------------//
    //  Getters                                                               //
    //------------------------------------------------------------------------//
public:
    //--------------------------------------------------------------------------
    // This will return a brand new TextureEntity with the Render Rectangle
    // set and the Position to (0,0).
    //
    // If we want just to get the Render Rectangles to make an animation
    // of the texture we can call the Rectangle() function instead.
    TextureEntity::UPtr Texture(const std::string &key);


    //--------------------------------------------------------------------------
    // Gets the rectangle described by the key.
    // This is useful to make an texture animation.
    const SDL_Rect& Rectangle(const std::string &key);


    //------------------------------------------------------------------------//
    // Loading Functions                                                      //
    //------------------------------------------------------------------------//
private:
    void LoadFromFile();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    std::string                     m_atlasPath;
    std::string                     m_texturesPath;
    std::map<std::string, SDL_Rect> m_rectsMap;

}; // class TextureAtlas
}  // namespace Cooper
