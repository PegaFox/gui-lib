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

      virtual void draw(glm::mat3 transform = glm::mat3(0.0f));
    private:
      bool pressed = false;

      VertexArray body = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
