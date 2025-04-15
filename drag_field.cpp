#include "drag_field.hpp"
#include <algorithm>
#include <fstream>

using namespace pfui;

DragField::DragField(const std::initializer_list<DragBox*>& children)
{
  type = ElementType::DragField;

  body.shape.setPrimitiveType(sf::PrimitiveType::TriangleFan);
  body.shape.append(sf::Vertex{sf::Vector2f(-0.5f, -0.5f), sf::Color(100, 50, 0)});
  body.shape.append(sf::Vertex{sf::Vector2f(-0.5f, 0.5f), sf::Color(100, 50, 0)});
  body.shape.append(sf::Vertex{sf::Vector2f(0.5f, 0.5f), sf::Color(100, 50, 0)});
  body.shape.append(sf::Vertex{sf::Vector2f(0.5f, -0.5f), sf::Color(100, 50, 0)});

  for (DragBox* child: children)
  {
    this->children.first[this->children.second++].reset(child);
  }
}

DragBox* DragField::addChild(DragBox* child, uint8_t index)
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

DragBox* DragField::addChild(std::shared_ptr<DragBox> child, uint8_t index)
{
  if (index == uint8_t(-1))
  {
    index = children.second;
  }

  if (children.second == 32 || index > children.second)
  {
    return nullptr;
  }

  std::move_backward(&children.first[index], &children.first[children.second], &children.first[children.second+1]);
  children.second++;
  children.first[index] = child;
  return children.first[index].get();
}

bool DragField::removeChild(uint8_t index)
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

DragBox* DragField::operator[](uint8_t index)
{
  if (index < children.second)
  {
    return children.first[index].get();
  }
  return nullptr;
}

uint8_t DragField::childNum()
{
  return children.second;
}

void DragField::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
  }

  glm::mat3 invTransform = glm::inverse(transform);
  glm::mat3 fieldTransform = transform * glm::mat3(glm::vec3(size.x*0.5f, 0, 0), glm::vec3(0, size.y*0.5f, 0), glm::vec3(pos.x, pos.y, 1));
  glm::mat3 childTransform = glm::inverse(normalizationTransform(SCREEN)) * fieldTransform;

  body.draw(SCREEN, fieldTransform);

  if (held != nullptr && held->getType() == ElementType::DragBox)
  {
    if (body.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      uint8_t index = -1;
      float yPos = body.getGlobalBounds().position.y;
      for (uint8_t c = drawStart; c < children.second; c++)
      {
        float itemHeight = children.first[c]->getGlobalBounds().size.y;

        if (mPos.y >= yPos && mPos.y < yPos + itemHeight)
        {
          index = c;
        } else if (children.first[c].get() == held.get())
        {
          removeChild(c);
          c--;
        }

        yPos += itemHeight;
      }

      std::shared_ptr<DragBox>* position = std::find(&children.first[0], &children.first[children.second], held);

      if (position != &children.first[index])
      {
        addChild(dynamic_pointer_cast<DragBox>(held), index);
      }
    }
  }
  
  float drawHeight = 0.0f;
  for (uint8_t c = drawStart; c < children.second; c++)
  {
    if (held.get() != children.first[c].get())
    {
      float ratio = children.first[c]->size.x / children.first[c]->size.y;
      children.first[c]->size.x = (childTransform * glm::vec3(2.0f, 2.0f, 0.0f)).x;
      children.first[c]->size.y = children.first[c]->size.x / ratio;

      drawHeight += children.first[c]->size.y*0.5f;
      children.first[c]->pos.x = (childTransform * glm::vec3(/*pos.x*/0.0f, 0.0f, 1.0f)).x;
      children.first[c]->pos.y = (childTransform * glm::vec3(0.0f, pos.y-1.0f, 1.0f)).y + drawHeight;
      drawHeight += children.first[c]->size.y*0.5f;
    } else
    {
      drawHeight += children.first[c]->size.y;
    }

    if ((c == drawStart ? body.getGlobalBounds().position.y + children.first[c]->getGlobalBounds().size.y : children.first[c-1]->getGlobalBounds().position.y + children.first[c-1]->getGlobalBounds().size.y + children.first[c]->getGlobalBounds().size.y) > body.getGlobalBounds().position.y + body.getGlobalBounds().size.y)
    {
      break;
    }

    if (held == nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && children.first[c]->getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      held = children.first[c];
      resizeDirs.value = 0;
    }

    if (held == nullptr && children.first[c].use_count() > 1 && !body.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      removeChild(c);
    } else
    {
      children.first[c]->draw(SCREEN);
    }
  }

  // this goes after the draw step in case of a drag box containing a drag field
  if (body.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
  {
    drawStart = glm::clamp((float)drawStart-scrollValue, 0.0f, (float)children.second-1);
    scrollValue = 0.0f;
  }

  if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
  {
    held = nullptr;
  }
}
