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

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      VertexArray body = VertexArray(VertexArray::Type::AABB);

      void init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd);
  };
}

#endif
