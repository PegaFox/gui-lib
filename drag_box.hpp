#ifndef PEGAFOX_GUI_LIB_DRAG_BOX_HPP
#define PEGAFOX_GUI_LIB_DRAG_BOX_HPP

#include <array>
#include <memory>
#include <cstdint>
#include "gui_element.hpp"
#include "vertex_array.hpp"

namespace pfui
{
  class DragBox: public GUIElement
  {
    public:
      DragBox(const std::initializer_list<GUIElement*>& children = {});

      GUIElement* addChild(GUIElement* child, uint8_t index = -1);

      bool removeChild(uint8_t index = -1);

      GUIElement* operator[](uint8_t index);

      uint8_t childNum();

      sf::FloatRect getGlobalBounds();

      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f));
    private:
      std::pair<std::array<std::unique_ptr<GUIElement>, 32>, uint8_t> children;
      VertexArray body;
  };
}

#endif