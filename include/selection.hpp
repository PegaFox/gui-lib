#ifndef PEGAFOX_GUI_LIB_SELECTION_HPP
#define PEGAFOX_GUI_LIB_SELECTION_HPP

#include "gui_element.hpp"
#include "vertex_array.hpp"

namespace pfui
{
  class Selection: public GUIElement
  {
    public:
      glm::u16vec2 optionDimensions = glm::u16vec2(2, 1);

      uint16_t* selectedIndex = &defaultSelected;

      void (*onChange)(uint16_t index) = nullptr;

      Selection();

      Rect getSelectedBounds() const;

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      uint16_t defaultSelected = 0;

      VertexArray body = VertexArray(VertexArray::Type::AABB);
      VertexArray selected = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
