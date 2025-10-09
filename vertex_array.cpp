#include "vertex_array.hpp"

using namespace pfui;

VertexArray::VertexArray(Type renderType)
{
  this->renderType = renderType;
}

Rect VertexArray::getGlobalBounds() const 
{
  return this->globalBounds;
}

GUIElement::ElementType VertexArray::getType() const
{
  return ElementType::VertexArray;
}

void VertexArray::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f, 2.0f));
  }

  glm::vec2 projectedPos(transform * glm::vec3(pos, 1.0f));
  glm::vec2 projectedSize(transform * glm::vec3(size, 0.0f));

  if (this->vertices.size() >= 2)
  {
    if (this->renderType == Type::AABB && this->drawRect != nullptr)
    {
      this->globalBounds = Rect{
        this->vertices[0]*projectedSize + projectedPos,
        (this->vertices[1]-this->vertices[0])*projectedSize,
      };

      this->drawRect(this->globalBounds, this->color);
    } else if (this->drawLine != nullptr)
    {
      if (this->renderType == Type::Line)
      {
        this->globalBounds = Rect{glm::vec2(INFINITY), glm::vec2(0.0f)};

        glm::vec2 maxCorner(-INFINITY);

        for (std::size_t v = 0; v < (this->vertices.size() >> 1) << 1; v += 2)
        {
          glm::vec2 pos1 = this->vertices[v]*projectedSize + projectedPos;
          glm::vec2 pos2 = this->vertices[v+1]*projectedSize + projectedPos;

          this->globalBounds.position.x = glm::min(glm::min(pos1.x, pos2.x), this->globalBounds.position.x);
          this->globalBounds.position.y = glm::min(glm::min(pos1.y, pos2.y), this->globalBounds.position.y);
          maxCorner.x = glm::max(glm::max(pos1.x, pos2.x), maxCorner.x);
          maxCorner.y = glm::max(glm::max(pos1.y, pos2.y), maxCorner.y);
          //this->globalBounds.size.x = glm::max(glm::abs(pos1.x - this->globalBounds.position.x), this->globalBounds.size.x);
          //this->globalBounds.size.y = glm::max(glm::abs(pos1.y - this->globalBounds.position.y), this->globalBounds.size.y);

          this->drawLine(pos1, pos2, this->color);
        }

        this->globalBounds.size = maxCorner - this->globalBounds.position;
      } else if (this->renderType == Type::LineStrip)
      {
        this->globalBounds = Rect{this->vertices[0]*projectedSize + projectedPos, glm::vec2(0.0f)};

        glm::vec2 maxCorner(this->vertices[0]*projectedSize + projectedPos);

        for (std::size_t v = 1; v < this->vertices.size(); v++)
        {
          glm::vec2 pos1 = this->vertices[v-1]*projectedSize + projectedPos;
          glm::vec2 pos2 = this->vertices[v]*projectedSize + projectedPos;

          this->globalBounds.position.x = glm::min(pos2.x, this->globalBounds.position.x);
          this->globalBounds.position.y = glm::min(pos2.y, this->globalBounds.position.y);
          maxCorner.x = glm::max(pos2.x, maxCorner.x);
          maxCorner.y = glm::max(pos2.y, maxCorner.y);
          //this->globalBounds.size.x = glm::max(glm::abs(pos1.x - this->globalBounds.position.x), this->globalBounds.size.x);
          //this->globalBounds.size.y = glm::max(glm::abs(pos1.y - this->globalBounds.position.y), this->globalBounds.size.y);

          this->drawLine(pos1, pos2, this->color);
        }

        this->globalBounds.size = maxCorner - this->globalBounds.position;
      }
    }
  }
}
