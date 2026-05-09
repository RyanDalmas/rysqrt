#ifndef RYSQRT
#define RYSQRT
/**
 * RySQRT:
 * A simple inline .h file written
 * for Dr. Patrick Miller's CS142 Algorithms course at UCR
 * 
 * The goal of this project is to beat 'System Sqrt',
 * otherwise known as the sqrt() function in the cmath library,
 * And to compete in a friendly class-wide optimization competition.
 * 
 * The following compiler options can be included,
 * however they produce varying results
 */
#include <stdint.h>

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC push_options
#pragma GCC optimize("Ofast")
#endif

namespace RySQRT {
    inline
    __attribute__((always_inline, const, hot, optimize("Ofast")))
    float
    newtons_method(float guess, float number) {
        return (guess + number/guess)*0.5f;
    }

    inline
    __attribute__((always_inline, const, hot, optimize("Ofast")))
    float
    fast_sqrt
    (float number) {
        union {
            float number;
            uint32_t bits;
        } estimate = { number };

        estimate.bits = 0x1FBB4F3C + (estimate.bits >> 1);
        return estimate.number;
    }

    inline
    __attribute__((always_inline, const, hot, optimize("Ofast")))
    double
    fast_sqrt
    (double number) {
        union {
            double number;
            uint64_t bits;
        } estimate = { number };

        estimate.bits = 0x1FF769E780000000ULL + (estimate.bits >> 1);
        return estimate.number;
    }

    inline
    __attribute__((always_inline, const, hot, optimize("Ofast")))
    float
    acc_sqrt
    (float number) {
        /**
         * I use my fast_sqrt function and I perform
         * two additional iterations for higher accuracy
         */
        float r = fast_sqrt(number);
        r = newtons_method(r, number);
        r = newtons_method(r, number);
        return r;
    }
}

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC pop_options
#endif

#endif
