#include "button.h"

#include "../button.hpp"

using namespace pfui;

extern "C"
{
  PFUI_ButtonOnPress* PFUI_ButtonOnPressPtr(PFUI_Button* self)
  {
    return &((Button*)self)->onPress;
  }

  PFUI_Button* PFUI_ButtonInit(PFUI_ButtonOnPress onPress)
  {
    PFUI_Button* button = (PFUI_Button*)new Button;

    *PFUI_ButtonOnPressPtr(button) = onPress;

    return button;
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
