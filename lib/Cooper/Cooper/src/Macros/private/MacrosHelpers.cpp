//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : MacrosHelpers.cpp (Private)                                   //
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
#include "include/Macros/private/MacrosHelpers.h"
// std
#include <cstdio>
#include <cstdlib>

//COWTODO(n2omatt): The assert and verify functions are almost equal.
//  Refactor them soon as possible to make use a general function.

//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
std::string Cooper::Private::vformat(const char *fmt, std::va_list list)
{
    constexpr int kBufferSize = 1024;
    char buffer[kBufferSize]  = {'\0'};

    // Build the buffer with the variadic args list.
    vsnprintf(buffer, kBufferSize, fmt, list);

    return std::string(buffer);
}

//----------------------------------------------------------------------------//
// Assert                                                                     //
//----------------------------------------------------------------------------//
void Cooper::Private::_cooper_assert_print_args(
    const    char *expr,
    const    char *file,
    unsigned int   line,
    const    char *func,
    const    char *msg,
    ...)
{
    va_list args;
    va_start(args, msg);

    // Forward the '...' to vformat
    auto buffer = vformat(msg, args);

    va_end(args);

    // Print the message and abort.
    fprintf(stderr,
            "Cooper Assert: assertion failed on: \n \
  file       : %s \n \
  line       : %d \n \
  function   : %s \n \
  expression : %s \n \
  message    : %s \n",
            file, line, func, expr, buffer.c_str());

    abort();
}


//----------------------------------------------------------------------------//
// Verify                                                                     //
//----------------------------------------------------------------------------//
void Cooper::Private::_cooper_verify_print_args(
    const    char *expr,
    const    char *file,
    unsigned int   line,
    const    char *func,
    const    char *msg,
    ...)
{
    va_list args;
    va_start(args, msg);

    // Forward the '...' to vformat
    auto buffer = vformat(msg, args);

    va_end(args);

    // Print the message and abort.
    fprintf(stderr,
            "Cooper Verify: assertion failed on: \n \
  file       : %s \n \
  line       : %d \n \
  function   : %s \n \
  expression : %s \n \
  message    : %s \n",
            file, line, func, expr, buffer.c_str());

    abort();
}
