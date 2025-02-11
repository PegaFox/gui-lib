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

      sf::FloatRect getGlobalBounds();

      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f));
    private:
      bool pressed = false;

      VertexArray body;
  };
}

#endif