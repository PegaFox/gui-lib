#include "button.hpp"

using namespace pfui;

Button::Button()
{
  type = ElementType::Button;

  body.color = defaultInteractableColor;
  body.vertices.emplace_back(-0.5f, -0.5f);
  body.vertices.emplace_back(0.5f, 0.5f);
}

bool Button::isPressed()
{
  return pressed;
}

Rect Button::getGlobalBounds()
{
  return body.getGlobalBounds();
}

void Button::draw(glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  body.pos = pos;
  body.size = size;
  body.draw(transform);

  body.color = defaultInteractableColor;

  bool currentlyPressed = false;
  if (getGlobalBounds().contains(mPos))
  {
    body.color = defaultInteractableColor * 1.5f;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
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
