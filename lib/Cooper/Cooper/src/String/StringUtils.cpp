//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : StringUtils.cpp                                               //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : stdmatt <stdmatt@pixelwizards.io>                             //
//  Copyright : stdmatt - 2017 - 2019                                         //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/String/StringUtils.h"
// Cooper
#include "include/Macros/private/MacrosHelpers.h"

// Usings
using namespace Cooper;


//----------------------------------------------------------------------------//
// Format Functions                                                           //
//----------------------------------------------------------------------------//
std::string StringUtils::Format(const char *pFormat, ...)
{
    va_list args;
    va_start(args, pFormat);

    //Forward the '...' to vFormat.
    auto ret = StringUtils::vFormat(pFormat, args);

    va_end(args);

    return ret;
}

std::string StringUtils::vFormat(const char *pFormat, std::va_list list)
{
    return Private::vformat(pFormat, list);
}
