#ifndef PEGAFOX_GUI_LIB_TRIANGLE_FAN_HPP
#define PEGAFOX_GUI_LIB_TRIANGLE_FAN_HPP

#include <vector>

#include "gui_element.hpp"

namespace pfui
{
  class VertexArray: public GUIElement
  {
    public:
      enum class Type
      {
        AABB,
        Line,
        LineStrip,
      } renderType;

      //sf::RenderStates shapeRenderStates = sf::RenderStates::Default; // TODO: Replace with texture struct
      Color color;
      std::vector<glm::vec2> vertices;

      VertexArray(Type renderType = Type::AABB);

      Rect getGlobalBounds();

      ElementType getType() override;

      void draw() override;
    private:
      Rect globalBounds;
  };
}

#endif
