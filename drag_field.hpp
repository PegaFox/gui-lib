#ifndef PEGAFOX_GUI_LIB_DRAG_FIELD_HPP
#define PEGAFOX_GUI_LIB_DRAG_FIELD_HPP

#include <array>
#include <memory>
#include <cstdint>
#include "gui_element.hpp"
#include "drag_box.hpp"

namespace pfui
{
  class DragField: public GUIElement
  {
    public:
      // starting item index, used for scrolling
      uint8_t drawStart = 0;

      DragField(const std::initializer_list<DragBox*>& children = {});

      DragBox* addChild(DragBox* child, uint8_t index = -1);

      DragBox* addChild(std::shared_ptr<DragBox> child, uint8_t index = -1);

      bool removeChild(uint8_t index = -1);

      DragBox* operator[](uint8_t index);

      uint8_t childNum();

      virtual void draw(glm::mat3 transform = glm::mat3(0.0f));
    private:
      std::pair<std::array<std::shared_ptr<DragBox>, 32>, uint8_t> children;
      VertexArray body = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
