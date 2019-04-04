/* -*- C++ -*- */
#pragma once

namespace Menu {

  template<typename O>
  struct FullPrinter:public O {
    // using This=FullPrinter<O>;
    using O::O;
    using RAW_DEVICE=typename O::RAW_DEVICE;//must have a raw device!
    template<typename P>
    using titleFmt=typename RAW_DEVICE::Parts::template titleFmt<P>;
    template<typename P>
    using itemFmt=typename RAW_DEVICE::Parts::template itemFmt<P>;
    template<typename P>
    void printMenuRaw(PrintHead<P> p,const Item& o) {
      // MENU_DEBUG_OUT<<"FullPrinter::printMenuRaw"<<endl;
      p.printer.fmtMenu(p,true);
      reinterpret_cast<titleFmt<O>*>(this)->printMenuRaw(p,o);
      // MenuOutCap<titleFmt<O>>(p.menuOut).printMenuRaw(p,o);;
      O::printMenuRaw(p,o);
      for(size_t n=0;n<o.size();n++) {
        reinterpret_cast<itemFmt<O>*>(this)->printMenuRaw(PrintHead<P>{p.menuOut,p.printer,n},o[n]);
      }
      p.printer.fmtMenu(p,false);
    }
  };

  template<typename O>
  struct TextCursorPrinter:public O {
    using O::O;
    using RAW_DEVICE=typename O::RAW_DEVICE;//must have a raw device!
    template<typename P>
    void printMenuRaw(PrintHead<P> p,const Item& o) {
      // MENU_DEBUG_OUT<<"TextCursorPrinter::printMenuRaw"<<endl;
      // if (p.menuOut.selected(p))
      p.printer.fmtCursor(p,true);
      // o.out(p.printer);
      O::printMenuRaw(p,o);
      if (selected(p)) p.printer.fmtCursor(p,false);
    }
  };

  template<typename O>
  struct TitlePrinter:public O {
    using O::O;
    using RAW_DEVICE=typename O::RAW_DEVICE;//must have a raw device!
    template<typename P>
    void printMenuRaw(PrintHead<P> p,const Item& o) {
      // MENU_DEBUG_OUT<<"TitlePrinter::printMenuRaw"<<endl;
      #if (MENU_INJECT_PARTS==true)
        //guess i wont need this
        PrinterPart pp;
        o.out(*reinterpret_cast<MenuOutCap<TitlePrinter<O>>*>(this),pp);
      #else
        o.out(p.menuOut);
      #endif
      O::printMenuRaw(p,o);
    }
  };

  template<typename O>
  struct ItemPrinter:public O {
    using O::O;
    using RAW_DEVICE=typename O::RAW_DEVICE;//must have a raw device!
    template<typename P>
    void printMenuRaw(PrintHead<P> p,const Item& o) {
      o.out(p.menuOut);
      O::printMenuRaw(p,o);
    }
  };

  //collection of printer parts to customize part printing
  template<
    template<typename> class i=ID,
    template<typename> class t=ID,
    template<typename> class m=ID,
    template<typename> class p=ID,
    typename O=Void
  > struct DeviceParts:public O {
    using O::O;
    template<typename T> using itemFmt=i<T>;
    template<typename T> using titleFmt=t<T>;
    template<typename T> using menuFmt=m<T>;
    template<typename T> using panelFmt=p<T>;
  };

};//Menu namespace