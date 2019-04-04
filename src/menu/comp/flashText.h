/* -*- C++ -*- */
#pragma once

#include <Arduino.h>
#include "../items.h"

namespace Menu {
  template<typename O=Empty>
  class FlashTextDef:public O {
  protected:
  public:
    const __FlashStringHelper * text;
    // using O::O;
    inline FlashTextDef(PGM_P t):text(reinterpret_cast<const __FlashStringHelper *>(t)) {}
    inline FlashTextDef(FlashTextDef<O>& o):text(o.text) {}
    inline void out(MenuOut &o) const {o<<text;}
  };
};