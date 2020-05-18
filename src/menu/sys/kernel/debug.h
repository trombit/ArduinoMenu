/* -*- C++ -*- */
#pragma once
/**
* @file debug.h
* @author Rui Azevedo
* @brief debug macros and utilities
*/

#include "api.h"

#ifdef MENU_DEBUG
  #define dbg_constexpr
  #ifdef ARDUINO
    // #pragma message "COMPILE FOR ARDUINO FRAMEWORK!"
    #include <streamFlow.h>
    // #include <Streaming.h>
    #ifndef MDO
      #define MDO Serial
      using mdo_t=decltype(MDO);
    #endif
  #else
    #include <iostream>
    // using namespace std;
    // #define endl "\r\n"
    #ifndef MDO
      #define MDO std::cout
    #endif
    using mdo_t=decltype(MDO)&;
  #endif
#else
  #define dbg_constexpr constexpr
#endif

// struct _MDO:mdo_t {};
// _MDO _mdo;

#include <assert.h>
#ifdef ARDUINO
  //from: https://gist.github.com/jlesech/3089916
  #if !defined(__AVR_ATtiny13__) && !defined(ARDUINO_attiny)
    #define __ASSERT_USE_STDERR

    // handle diagnostic informations given by assertion and abort program execution:
    void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
        // transmit diagnostic informations through serial link.
        Serial.println(__func);
        Serial.println(__file);
        Serial.println(__lineno, DEC);
        Serial.println(__sexp);
        Serial.flush();
        // abort program execution.
        abort();
    }
  #endif
#endif

namespace Menu {
  #if defined(MENU_DEBUG) && defined(TRACE)
    #define trace(x) x
  #else
    #define trace(x)
  #endif
  #ifdef MENU_DEBUG
    #define _trace(x) x
  #else
    #define _trace(x)
  #endif
  #ifndef MENU_RELEASE
    #define __trace(x) x
  #else
    #define __trace(x)
  #endif
};