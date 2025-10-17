#include "drag_field.hpp"
#include <algorithm>
#include <fstream>

using namespace pfui;

DragField::DragField(const std::initializer_list<DragBox*>& children)
{
  init(children.begin(), children.end());
}

DragField::DragField(DragBox* const * childrenBegin, DragBox* const * childrenEnd)
{
  init(childrenBegin, childrenEnd);
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

uint8_t DragField::childCount() const
{
  return children.second;
}

Rect DragField::getGlobalBounds() const
{
  return body.getGlobalBounds();
}

GUIElement::ElementType DragField::getType() const
{
  return ElementType::DragField;
}

void DragField::draw()
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

  if (held != nullptr && held->getType() == ElementType::DragBox)
  {
    if (body.getGlobalBounds().contains(mPos))
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

      if (index == (uint8_t)-1 || position != &children.first[index])
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

    if (held == nullptr && this->mPressed.states.left && children.first[c]->getGlobalBounds().contains(mPos))
    {
      held = children.first[c];
      resizeDirs.value = 0;
    }

    if (held == nullptr && children.first[c].use_count() > 1 && !body.getGlobalBounds().contains(mPos))
    {
      removeChild(c);
    } else
    {
      children.first[c]->draw();
    }
  }

  // this goes after the draw step in case of a drag box containing a drag field
  if (body.getGlobalBounds().contains(mPos))
  {
    drawStart = glm::clamp((float)drawStart-scrollValue, 0.0f, (float)children.second-1);
    scrollValue = 0.0f;
  }

  if (!this->mPressed.states.left)
  {
    held = nullptr;
  }
}

void DragField::init(DragBox* const * childrenBegin, DragBox* const * childrenEnd)
{
  body.color = defaultObjectColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);

  for (DragBox* const * child = childrenBegin; child != childrenEnd; child++)
  {
    this->children.first[this->children.second++].reset(*child);
  }
}
