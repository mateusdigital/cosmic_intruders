//~---------------------------------------------------------------------------//
//                        _      _                 _   _                      //
//                    ___| |_ __| |_ __ ___   __ _| |_| |_                    //
//                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   //
//                   \__ \ || (_| | | | | | | (_| | |_| |_                    //
//                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   //
//                                                                            //
//  File      : Random.h                                                      //
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

//std
#include <random>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>
#include <stdexcept>
//CoreRandom
#include "CoreRandom_Utils.h"



NS_CORERANDOM_BEGIN

class Random
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Typedef to reduce verbosity.
    typedef std::mt19937 NumberGeneratorType;

    ///-------------------------------------------------------------------------
    /// @brief Typedef to reduce verbosity.
    typedef std::uniform_int_distribution<int> IntegerDistributionType;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Constructs a Random object with the target seed.
    /// @param seed
    ///   The seed that the random number generator will
    ///   be initialized. If seed is kRandomSeed it will be
    ///   selected from the system std::time(nullptr).
    /// @see kRandomSeed, reseed(), getSeed(), isUsingRandomSeed().
    Random(int seed = -1)
        : m_randomDist(0, 1)
    {
        reseed(seed);
    }



    //------------------------------------------------------------------------//
    // Generation Methods                                                     //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [0, std::numeric_limits<int>::max()].
    /// @returns
    ///   An integer in [0, std::numeric_limits<int>::max()] range.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(int max), next(int min, int max);
    int next() {
        resetRange(0, std::numeric_limits<int>::max());
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [0, max].
    /// @param max
    ///   The upperbound of the range.
    /// @warning
    ///   max must be >= 0.
    /// @returns
    ///   An integer in [0, max] range.
    /// @throws
    ///   std::invalid_argument if max < 0.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(), next(int min, int max);
    int next(int max) {
        resetRange(0, max);
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [min, max].
    /// @param min
    ///   The lowerbound of the range.
    /// @param max
    ///   The upperbound of the range.
    /// @warning
    ///   max >= min.
    /// @returns
    ///   An integer in [min, max] range.
    /// @throws
    ///   std::invalid_argument if max < min.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(), next(int max);
    int next(int min, int max) {
        resetRange(min, max);
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random bool value.
    /// @returns
    ///   A bool value.
    /// @see next(), next(int max), next(int min, int max);
    bool nextBool() {
        return static_cast<bool>(m_randomDist(m_rnd));
    }


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the reference for the internal number generator.
    /// @returns
    ///   A reference for the internal number generator.
    /// @see NumberGeneratorType.
    NumberGeneratorType& getNumberGenerator() { return m_rnd; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the constant reference for the internal number generator.
    /// @returns
    ///   A constant reference for the internal number generator.
    /// @see NumberGeneratorType.
    const NumberGeneratorType& getNumberGenerator() const { return m_rnd; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the reference for the internal integer distribution.
    /// @returns
    ///   A reference for the internal integer distribution.
    /// @see IntegerDistributionType.
    IntegerDistributionType& getIntDistribution() { return m_dist; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the constant reference for the internal integer distribution.
    /// @returns
    ///   A constant reference for the internal integer distribution.
    /// @see IntegerDistributionType.
    const IntegerDistributionType& getIntDistribution() const { return m_dist; }


    ///-------------------------------------------------------------------------
    /// @brief
    ///   Reseed object with the target seed.
    /// @param seed
    ///   The seed that the random number generator will
    ///   be initialized. If seed is kRandomSeed it will be
    ///   selected from the system std::time(nullptr).
    /// @see getSeed(), isUsingRandomSeed().
    void reseed(int seed = -1) {
        m_seed = (seed == -1)
            ? std::time(nullptr)
            : seed;

        m_isUsingRandomSeed = (seed == -1);
        m_rnd.seed(m_seed);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the actual seed used.
    /// @returns
    ///   The actual seed used in this object - If Random was created
    ///   using kRandomSeed it will the chosen seed, otherwise will
    ///   return the argument used in the CTOR.
    int getSeed() const { return m_seed; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Checks if CTOR was initialized with kRandomSeed.
    /// @returns
    ///   True if kRandomSeed was used, False otherwise.
    bool isUsingRandomSeed() const {
        return m_isUsingRandomSeed;
    }


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    void resetRange(int min, int max) {
        if(max > min) {
            const auto temp = min;
            max = min;
            min = temp;
        }

        if(m_dist.min() != min || m_dist.max() != max)
            m_dist.param(std::uniform_int_distribution<int>::param_type(min, max));
    }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Housekeeping.
    int  m_seed;
    bool m_isUsingRandomSeed;

    // Random.
    NumberGeneratorType     m_rnd;
    IntegerDistributionType m_dist;
    IntegerDistributionType m_randomDist;
};

NS_CORERANDOM_END
