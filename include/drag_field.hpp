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

      DragField(DragBox* const * childrenBegin, DragBox* const * childrenEnd);

      DragBox* addChild(DragBox* child, uint8_t index = -1, bool heapAllocated = true);

      DragBox* addChild(std::shared_ptr<DragBox> child, uint8_t index = -1);

      bool removeChild(uint8_t index = -1);

      DragBox* operator[](uint8_t index);

      uint8_t childCount() const;

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      std::pair<std::array<std::shared_ptr<DragBox>, 32>, uint8_t> children;
      VertexArray body = VertexArray(VertexArray::Type::AABB);

      void init(DragBox* const * childrenBegin, DragBox* const * childrenEnd);
  };
}

#endif
