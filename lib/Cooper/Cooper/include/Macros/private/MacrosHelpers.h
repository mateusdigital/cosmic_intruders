//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : MacrosHelpers.h (Private)                                     //
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
#include <cstdarg>
#include <string>

namespace Cooper { namespace Private {

//----------------------------------------------------------------------------//
// Var args                                                                   //
//----------------------------------------------------------------------------//
std::string vformat(const char *fmt, std::va_list list);


//----------------------------------------------------------------------------//
// Assert                                                                     //
//----------------------------------------------------------------------------//
void _cooper_assert_print_args(
    const    char   *expr,
    const    char   *file,
    unsigned int     line,
    const    char   *func,
    const    char   *msg,
    ...);


//----------------------------------------------------------------------------//
// Verify                                                                     //
//----------------------------------------------------------------------------//
void _cooper_verify_print_args(
    const    char   *expr,
    const    char   *file,
    unsigned int     line,
    const    char   *func,
    const    char   *msg,
    ...);

} // namespace Private
} // namespace Cooper
