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

      DragBox(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd);

      GUIElement* addChild(GUIElement* child, uint8_t index = -1, bool heapAllocated = true);

      bool removeChild(uint8_t index = -1);

      GUIElement* operator[](uint8_t index);

      uint8_t childCount() const;

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      std::pair<std::array<std::shared_ptr<GUIElement>, 32>, uint8_t> children;
      VertexArray body = VertexArray(VertexArray::Type::AABB);

      void init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd);
  };
}

#endif
