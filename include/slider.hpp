#ifndef PEGAFOX_GUI_LIB_SLIDER_HPP
#define PEGAFOX_GUI_LIB_SLIDER_HPP

#include "gui_element.hpp"
#include "vertex_array.hpp"

namespace pfui
{
  class Slider: public GUIElement
  {
    public:
      float value = 0.0f;
      float min = 0.0f;
      float max = 1.0f;

      // Zero for no step size restriction
      float stepSize = 0.0f;

      void (*onChange)(float currentValue) = nullptr;

      Slider();

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      bool handleHeld = false;

      VertexArray body = VertexArray(VertexArray::Type::AABB);
      VertexArray handle = VertexArray(VertexArray::Type::AABB);
  };
}

#endif
