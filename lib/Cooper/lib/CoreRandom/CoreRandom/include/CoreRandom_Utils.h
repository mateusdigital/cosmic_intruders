//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : CoreRandom_Utils.h                                            //
//  Project   : CoreRandom                                                    //
//  Date      : Apr 06, 2016                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2016 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

//----------------------------------------------------------------------------//
// Namespaces                                                                 //
//----------------------------------------------------------------------------//
// All classes of this core is placed inside this namespace.
// We use MACROS so is easier to change if needed.
// Is (in our opinion) more explicit.
// And finally the editors will not reformat the code.
#define NS_CORERANDOM_BEGIN namespace CoreRandom {
#define NS_CORERANDOM_END   }
#define USING_NS_CORERANDOM using namespace CoreRandom

//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//
// The core version number.
#define COW_CORERANDOM_VERSION_MAJOR    "0"
#define COW_CORERANDOM_VERSION_MINOR    "5"
#define COW_CORERANDOM_VERSION_REVISION "0"

#define COW_CORERANDOM_VERSION       \
    COW_CORERANDOM_VERSION_MAJOR "." \
    COW_CORERANDOM_VERSION_MINOR "." \
    COW_CORERANDOM_VERSION_REVISION
