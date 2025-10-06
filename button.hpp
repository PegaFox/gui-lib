#ifndef PEGAFOX_GUI_LIB_BUTTON_HPP
#define PEGAFOX_GUI_LIB_BUTTON_HPP

#include "gui_element.hpp"
#include "vertex_array.hpp"

namespace pfui
{
  class Button: public GUIElement
  {
    public:
      void (*onPress)() = nullptr;

      Button();

      bool isPressed();

      Rect getGlobalBounds();

      ElementType getType() override;

      void draw() override;
    private:
      bool pressed = false;

      VertexArray body = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
