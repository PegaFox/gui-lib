#include "selection.hpp"

using namespace pfui;

Selection::Selection()
{
  body.color = defaultInteractableColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);

  selected.color = defaultInteractableColor * 1.5f;
  selected.vertices.emplace_back(-0.5f, -0.5f);
  selected.vertices.emplace_back(0.5f, 0.5f);
}

Rect Selection::getGlobalBounds() const
{
  return body.getGlobalBounds();
}

GUIElement::ElementType Selection::getType() const
{
  return ElementType::Slider;
}

void Selection::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  body.pos = pos;
  body.size = size;
  body.transform = transform;
  body.draw();

  selected.size = size / glm::vec2(this->optionDimensions);
  selected.pos = glm::vec2(pos.x-size.x*0.5f + selected.size.x*(0.5f+*this->selectedIndex%this->optionDimensions.x), pos.y-size.y*0.5f + selected.size.y*(0.5f+*this->selectedIndex/this->optionDimensions.x));
  selected.transform = transform;
  selected.draw();

  if (getGlobalBounds().contains(mPos) && this->mPressed.states.left)
  {
    glm::vec2 localMPos = glm::inverse(transform * viewportTransform(this->pos, this->size)) * glm::vec3(this->mPos, 1);

    glm::i16vec2 selectedPosition = (glm::clamp(localMPos, -1.0f, 1.0f) + 1.0f) * glm::vec2(this->optionDimensions)*0.5f;

    *this->selectedIndex = selectedPosition.y*this->optionDimensions.x + selectedPosition.x;
    //*this->selectedIndex = (glm::clamp(localMPos.y, this->pos.y - this->size.y*0.5f, this->pos.y + this->size.y*0.5f) + this->size.y*0.5f) * this->optionCount*0.5f;
    //this->held.reset(this, HeldDeleter());
  }

  /*if (pressed == false && currentlyPressed == true && onPress != nullptr)
  {
    onPress();
  }

  pressed = currentlyPressed;*/
}

