#include "slider.hpp"

using namespace pfui;

Slider::Slider()
{
  body.color = defaultObjectColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);

  handle.color = defaultInteractableColor;
  handle.vertices.emplace_back(-0.5f, -0.5f);
  handle.vertices.emplace_back(0.5f, 0.5f);
}

Rect Slider::getGlobalBounds() const
{
  return body.getGlobalBounds();
}

GUIElement::ElementType Slider::getType() const
{
  return ElementType::Slider;
}

void Slider::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  if (this->handleHeld)
  {
    float newValue = (glm::clamp((glm::inverse(handle.transform) * glm::vec3(this->mPos, 1)).x, -1.0f, 1.0f)+1.0f) * (max-min)*0.5f + min;

    if (this->stepSize != 0.0f)
    {
      newValue = glm::floor(newValue / this->stepSize) * this->stepSize;
    }

    if (newValue != this->value && this->onChange)
    {
      this->onChange(newValue);
    }

    this->value = newValue;

    if (!this->mPressed.states.left)
    {
      this->handleHeld = false;
    }
  } else if (getGlobalBounds().contains(mPos) && this->mPressed.states.left)
  {
    this->handleHeld = true;
    //this->held.reset(this, HeldDeleter());
  }

  body.pos = pos;
  body.size = size;
  body.transform = transform;
  body.draw();
  
  handle.pos.x = (this->value-min) / (max-min)*2.0f - 1.0f;
  handle.pos.y = 0.0f;
  //handle.size = glm::vec2(size.x*0.1f, size.y);
  handle.size = glm::vec2(0.1f, 2.0f);
  handle.transform = transform * viewportTransform(this->pos, this->size);
  handle.draw();

  /*if (pressed == false && currentlyPressed == true && onPress != nullptr)
  {
    onPress();
  }

  pressed = currentlyPressed;*/
}

