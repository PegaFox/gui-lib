#include "c/button.h"

#include "button.hpp"

using namespace pfui;

extern "C"
{
  PFUI_ButtonOnChange* PFUI_ButtonOnChangePtr(PFUI_Button* self)
  {
    return &((Button*)self)->onChange;
  }

  PFUI_Button* PFUI_ButtonInit()
  {
    return (PFUI_Button*)new Button;
  }

  void PFUI_ButtonDeinit(PFUI_Button* self)
  {
    delete (Button*)self;
  }

  bool PFUI_ButtonIsPressed(PFUI_Button* self)
  {
    return ((Button*)self)->isPressed();
  }
}
