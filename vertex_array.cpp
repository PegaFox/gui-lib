#include "vertex_array.hpp"

using namespace pfui;

VertexArray::VertexArray(sf::PrimitiveType primitiveType)
{
  type = ElementType::VertexArray;
  shape.setPrimitiveType(primitiveType);
}

sf::FloatRect VertexArray::getGlobalBounds()
{
  return globalBounds;
}

void VertexArray::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
  }

  glm::vec2 projectedPos(transform * glm::vec3(pos, 1.0f));
  glm::vec2 projectedSize(transform * glm::vec3(size, 0.0f));

  sf::VertexArray draw = shape;
  for (std::size_t v = 0; v < draw.getVertexCount(); v++)
  {
    glm::vec2 newPos = glm::vec2(draw[v].position.x, draw[v].position.y) * projectedSize + projectedPos;
    draw[v].position = sf::Vector2f(newPos.x, newPos.y);
  }

  globalBounds = draw.getBounds();
  SCREEN.draw(draw);
}