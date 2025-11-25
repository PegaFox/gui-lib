#ifndef PEGAFOX_GUI_LIB_BUTTON_HPP
#define PEGAFOX_GUI_LIB_BUTTON_HPP

#include "gui_element.hpp"
#include "vertex_array.hpp"

namespace pfui
{
  class Button: public GUIElement
  {
    public:
      void (*onChange)(bool pressed) = nullptr;

      Button();

      bool isPressed() const;

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      bool pressed = false;

      VertexArray body = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
