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
    body.shape[0].color = defaultInteractableColor * sf::Color(255 * 1.5f, 255 * 1.5f, 255 * 1.5f);
    body.shape[1].color = defaultInteractableColor * sf::Color(255 * 1.5f, 255 * 1.5f, 255 * 1.5f);
    body.shape[2].color = defaultInteractableColor * sf::Color(255 * 1.5f, 255 * 1.5f, 255 * 1.5f);
    body.shape[3].color = defaultInteractableColor * sf::Color(255 * 1.5f, 255 * 1.5f, 255 * 1.5f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      body.shape[0].color = defaultInteractableColor * sf::Color(255 * 0.8f, 255 * 0.8f, 255 * 0.8f);
      body.shape[1].color = defaultInteractableColor * sf::Color(255 * 0.8f, 255 * 0.8f, 255 * 0.8f);
      body.shape[2].color = defaultInteractableColor * sf::Color(255 * 0.8f, 255 * 0.8f, 255 * 0.8f);
      body.shape[3].color = defaultInteractableColor * sf::Color(255 * 0.8f, 255 * 0.8f, 255 * 0.8f);

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
