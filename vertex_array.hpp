#ifndef PEGAFOX_GUI_LIB_TRIANGLE_FAN_HPP
#define PEGAFOX_GUI_LIB_TRIANGLE_FAN_HPP

#include "gui_element.hpp"

#include <glm/vec4.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace pfui
{
  class VertexArray: public GUIElement
  {
    public:
      sf::RenderStates shapeRenderStates = sf::RenderStates::Default;
      sf::VertexArray shape;

      VertexArray(sf::PrimitiveType type = sf::PrimitiveType::Points);

      // this is for getting the transformed shape; for local bounds, use this->shape.getBounds()
      sf::FloatRect getGlobalBounds();

      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f));
    private:
      sf::FloatRect globalBounds;
  };
}

#endif
