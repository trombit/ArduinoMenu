/* -*- C++ -*- */
#pragma once
////////////////////////////////////////////////////
// Rui Azevedo - Apr2019
// neu-rah (ruihfazevedo@gmail.com)
// use arduino standard LCD library as menu output

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <streamFlow.h>
#include "../out.h"
#include "../nav.h"
#include "../panels.h"
#include "../fmt/textCursor.h"
#include "../fmt/cursorPos.h"
#include "../fmt/titleWrap.h"
#include "../printers.h"
#include "../fmt/debug.h"

namespace Menu {

  template<typename P,typename Dev,Dev& dev, typename O=Void>
  struct LCDOutDef:public O {
    using RAW_DEVICE = LCDOutDef<P,Dev,dev,O>;
    using Parts=P;
    using O::O;
    // static inline void endl() {O::useY();}//the viewport will catch it
    template<typename T>
    inline void raw(T i) {
      if (!O::operator bool()) return;
      dev.setCursor(O::posX(),O::posY());
      // Serial<<"lcd.setCursor("<<posX()<<","<<posY()<<") "<<i<<endl;
      O::useX(dev.print(i));
    }
  };

  using LCDParts=DeviceParts<
    ItemPrinter,//emit format messages for accel, cursor amd item
    TitlePrinter//emit format messages for titles (fmtTitle)
  >;

  // template<typename O>
  // using TitleWrap=TitleWrapFmt<O>;

  // template<typename O>
  // using SingleLineMenu=SingleLineScrollCtrl<O,1>;

  template<template<typename> class N=NavNode>
  using LCDFmt = Menu::Chain<//wrap inner types
    DebugFmt,//add debug info when enabled
    // TextCursorFmt,//signal selected option on text mode
    CursorPosFmt,//cursor control, change line at item end
    TitleWrap,//wrap title in []
    TitlePrinter,
    SelItemPrinter,
    // FullPrinter,//print inner then options
    // SingleLineMenu,//scroll on every move (text lines)
    N//flat navigation control (no sub menus)
  >;

};//Menu

template<LiquidCrystal& lcd,typename Panel=Menu::StaticPanel<16,2>,typename Parts=Menu::LCDParts>
using LCDOutDev=Menu::LCDOutDef<
  Parts,
  LiquidCrystal,
  lcd,
  Menu::Viewport<Panel>
>;