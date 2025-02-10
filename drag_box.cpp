#include "drag_box.hpp"

using namespace pfui;

DragBox::DragBox(const std::initializer_list<GUIElement*>& children)
{
  type = ElementType::DragBox;

  body.shape.setPrimitiveType(sf::TriangleFan);
  body.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(0.5f, -0.5f), sf::Color(150, 50, 0)));

  for (GUIElement* child: children)
  {
    this->children.first[this->children.second++].reset(child);
  }
}

GUIElement* DragBox::addChild(GUIElement* child, uint8_t index)
{
  if (children.second == 32)
  {
    return nullptr;
  }

  children.first[children.second++].reset(child);
  return children.first[children.second-1].get();
}

bool DragBox::removeChild(uint8_t index)
{
  if (children.second == 0)
  {
    return false;
  }

  children.first[--children.second].reset();
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

uint8_t DragBox::childNum()
{
  return children.second;
}

sf::FloatRect DragBox::getGlobalBounds()
{
  return body.getGlobalBounds();
}

void DragBox::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
  }

  glm::mat3 invTransform = glm::inverse(transform);
  glm::mat3 fieldTransform = transform * glm::mat3(glm::vec3(size.x*0.5f, 0, 0), glm::vec3(0, size.y*0.5f, 0), glm::vec3(pos.x, pos.y, 1));
  glm::mat3 childTransform = glm::inverse(normalizationTransform(SCREEN)) * fieldTransform;

  body.draw(SCREEN, fieldTransform);

  for (uint8_t c = 0; c < children.second; c++)
  {
    children.first[c]->draw(SCREEN, fieldTransform);
  }
}