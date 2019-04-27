//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Log.h                                                         //
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

namespace Cooper {

//class-like namespace
namespace Log {

    //------------------------------------------------------------------------//
    // Enum / Constants / Typedefs                                            //
    //------------------------------------------------------------------------//
    enum {
        LOG_LEVEL_NONE    = 0,
        LOG_LEVEL_DEBUG   = 1 << 0,
        LOG_LEVEL_INFO    = 1 << 1,
        LOG_LEVEL_WARN    = 1 << 2,
        LOG_LEVEL_ERROR   = 1 << 3,
        LOG_LEVEL_VERBOSE = LOG_LEVEL_DEBUG |
                            LOG_LEVEL_INFO  |
                            LOG_LEVEL_WARN  |
                            LOG_LEVEL_ERROR
    };

    typedef unsigned int LogLevel;


    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                    //
    //------------------------------------------------------------------------//
    void Init    ();
    void Shutdown();

    bool Initialized();


    //------------------------------------------------------------------------//
    // Set / Get the Current LogLevel                                         //
    //------------------------------------------------------------------------//
    void     SetLogLevel(LogLevel level = LOG_LEVEL_VERBOSE);
    LogLevel GetLogLevel();


    //------------------------------------------------------------------------//
    // Log Functions                                                          //
    //------------------------------------------------------------------------//
    void D(std::string msg, ...);
    void I(std::string msg, ...);
    void W(std::string msg, ...);
    void E(std::string msg, ...);

} // namespace Log
} // namespace Cooper
