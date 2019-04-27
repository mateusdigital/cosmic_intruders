//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Sound.h                                                       //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// std
#include <string>
#include <vector>

namespace Cooper {
// Forward declarations.

// "class-like" namespace.
namespace Sound {

    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                    //
    //------------------------------------------------------------------------//
    void Init();
    void Shutdown();

    bool Initialized();


    //------------------------------------------------------------------------//
    // Sound Functions                                                        //
    //------------------------------------------------------------------------//
    void PreloadSound(const std::vector<std::string> &path);
    void FreeSound   (const std::string &path);

    bool IsLoaded(const std::string &path);

    void PlaySound(const std::string &path);


} // namespace Sound
} // namespace Cooper
