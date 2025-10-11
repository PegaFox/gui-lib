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

GUIElement* DragBox::addChild(GUIElement* child, uint8_t index)
{
  if (index == uint8_t(-1))
  {
    index = children.second;
  }

  if (children.second == 32 || index > children.second)
  {
    return nullptr;
  }

  std::move_backward(&children.first[index], &children.first[children.second++], &children.first[index+1]);
  children.first[index].reset(child);
  return children.first[index].get();
}

bool DragBox::removeChild(uint8_t index)
{
  if (index == uint8_t(-1))
  {
    index = children.second-1;
  }

  if (index >= children.second)
  {
    return false;
  }

  children.first[index].reset();
  std::move(&children.first[index+1], &children.first[children.second--], &children.first[index]);
  return true;
}

GUIElement* DragBox::operator[](uint8_t index)
{
  if (index < children.second)
  {
    return children.first[index].get();
  }
  return nullptr;
}

uint8_t DragBox::childCount() const
{
  return children.second;
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
  glm::mat3 fieldTransform = transform * glm::mat3(glm::vec3(size.x*0.5f, 0, 0), glm::vec3(0, size.y*0.5f, 0), glm::vec3(pos.x, pos.y, 1));
  glm::mat3 childTransform = glm::inverse(normalizationTransform(glm::vec2(2.0f))) * fieldTransform;

  body.transform = fieldTransform;
  body.draw();

  for (uint8_t c = 0; c < children.second; c++)
  {
    //children.first[c]->transform = childTransform;
    children.first[c]->transform = fieldTransform;

    children.first[c]->draw();
  }
}

void DragBox::init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd)
{
  body.color = defaultBackgroundColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);

  for (GUIElement* const * child = childrenBegin; child != childrenEnd; child++)
  {
    this->children.first[this->children.second++].reset(*child);
  }
}
