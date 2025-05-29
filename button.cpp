#include "button.hpp"

using namespace pfui;

Button::Button()
{
  type = ElementType::Button;

  body.shape.setPrimitiveType(sf::PrimitiveType::TriangleFan);
  body.shape.append(sf::Vertex{sf::Vector2f(-0.5f, -0.5f), defaultInteractableColor});
  body.shape.append(sf::Vertex{sf::Vector2f(-0.5f, 0.5f), defaultInteractableColor});
  body.shape.append(sf::Vertex{sf::Vector2f(0.5f, 0.5f), defaultInteractableColor});
  body.shape.append(sf::Vertex{sf::Vector2f(0.5f, -0.5f), defaultInteractableColor});
}

bool Button::isPressed()
{
  return pressed;
}

sf::FloatRect Button::getGlobalBounds()
{
  return body.getGlobalBounds();
}

void Button::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
  }

  body.pos = pos;
  body.size = size;
  body.draw(SCREEN, transform);

  bool currentlyPressed = false;
  if (getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
  {
    sf::Color newColor(defaultInteractableColor.r * 1.5f, defaultInteractableColor.g * 1.5f, defaultBackgroundColor.b * 1.5f);

    body.shape[0].color = newColor;
    body.shape[1].color = newColor;
    body.shape[2].color = newColor;
    body.shape[3].color = newColor;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      newColor = sf::Color(defaultInteractableColor.r * 0.8f, defaultInteractableColor.g * 0.8f, defaultBackgroundColor.b * 0.8f);

      body.shape[0].color = newColor;
      body.shape[1].color = newColor;
      body.shape[2].color = newColor;
      body.shape[3].color = newColor;

      currentlyPressed = true;
    }
  } else
  {
    body.shape[0].color = defaultInteractableColor;
    body.shape[1].color = defaultInteractableColor;
    body.shape[2].color = defaultInteractableColor;
    body.shape[3].color = defaultInteractableColor;
  }

  if (pressed == false && currentlyPressed == true && onPress != nullptr)
  {
    onPress();
  }

  pressed = currentlyPressed;
}
