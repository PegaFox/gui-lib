#include "button.hpp"

using namespace pfui;

Button::Button()
{
  body.color = defaultInteractableColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);
}

bool Button::isPressed() const
{
  return pressed;
}

Rect Button::getGlobalBounds() const
{
  return body.getGlobalBounds();
}

GUIElement::ElementType Button::getType() const
{
  return ElementType::Button;
}

void Button::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  body.pos = pos;
  body.size = size;
  body.transform = transform;
  body.draw();

  body.color = defaultInteractableColor;

  bool currentlyPressed = false;
  if (getGlobalBounds().contains(mPos))
  {
    body.color = defaultInteractableColor * 1.5f;

    if (this->mPressed.states.left)
    {
      body.color = defaultInteractableColor * 0.8f;

      currentlyPressed = true;
    }
  }

  if (pressed == false && currentlyPressed == true && onPress != nullptr)
  {
    onPress();
  }

  pressed = currentlyPressed;
}
