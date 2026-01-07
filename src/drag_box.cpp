#include "drag_box.hpp"

using namespace pfui;

DragBox::DragBox(const std::initializer_list<GUIElement*>& children)
{
  init(children.begin(), children.end());
}

DragBox::DragBox(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd)
{
  init(childrenBegin, childrenEnd);
}

Rect DragBox::getGlobalBounds() const
{
  return body.getGlobalBounds();
}

GUIElement::ElementType DragBox::getType() const
{
  return ElementType::DragBox;
}

void DragBox::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  glm::mat3 invTransform = glm::inverse(transform);
  glm::mat3 fieldTransform = transform * viewportTransform(pos, size);
  glm::mat3 childTransform = glm::inverse(normalizationTransform(glm::vec2(2.0f))) * fieldTransform;

  body.transform = fieldTransform;
  body.draw();

  for (uint8_t c = 0; c < this->childrenCount; c++)
  {
    //children.first[c]->transform = childTransform;
    (*this)[c]->transform = fieldTransform;

    (*this)[c]->draw();
  }
}

void DragBox::init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd)
{
  body.color = defaultBackgroundColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);

  
  for (GUIElement* const* child = childrenBegin; child != childrenEnd; child++)
  {
    this->addChild(*child);
  }
}
