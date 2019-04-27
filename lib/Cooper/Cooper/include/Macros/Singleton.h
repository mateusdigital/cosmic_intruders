//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Singleton.h                                                   //
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

//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Makes the type a Singleton. So instead of type all of the code bellow for
// each type that we want to make a singleton we can just type, lets say:
//   COOPER_SINGLETON_OF(Enemy);
// Please notice that it expects that the user is reasonable with the type
// passed in, it only work for the classes that you own.
//
// Reference:
//   https://en.wikipedia.org/wiki/Singleton_pattern
#define COOPER_SINGLETON_OF(_type_)                   \
    static _type_* Instance() {                       \
        static _type_ s_instance;                     \
        return &s_instance;                           \
    };                                                \
                                                      \
    /* CTOR / DTOR */                                 \
    private:                                          \
         _type_();                                    \
        ~_type_();                                    \
                                                      \
    public:                                           \
        /* Copy CTOR / Copy Assign */                 \
        _type_(const _type_&) = delete;               \
        _type_& operator=(const _type_&) = delete;    \
                                                      \
        /* Move CTOR / Move Assign */                 \
        _type_(_type_&&) = delete;                    \
        _type_& operator=(_type_&&) = delete;         \
                                                      \
    /* Let everything bellow be private by default */ \
    private:
