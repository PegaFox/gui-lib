#include "gui_element.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

using namespace pfui;

// The color used for 
sf::Color GUIElement::defaultBackgroundColor = sf::Color(150, 50, 0);
sf::Color GUIElement::defaultObjectColor = sf::Color(100, 50, 0);
sf::Color GUIElement::defaultBorderColor = sf::Color(150, 150, 100);
sf::Color GUIElement::defaultInteractableColor = sf::Color(100, 100, 100);

// must be called for all events in order for gui elements to be interactable
void GUIElement::getEvent(const std::optional<sf::Event>& event)
{
  if (event)
  {
    if (const sf::Event::MouseMoved* move = event->getIf<sf::Event::MouseMoved>())
    {
      if (held != nullptr && sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SCREEN->getSize())).contains(move->position))
      {
        glm::vec2 delta = (glm::vec2(move->position.x, move->position.y) - glm::vec2(mPos)) / glm::vec2(SCREEN->getSize().x*0.5f, SCREEN->getSize().y*0.5f);
        if (resizeDirs.value == 0)
        {
          held->pos += delta;
        } else
        {
          if (resizeDirs.flags.left)
          {
            held->pos.x += delta.x/2.0f;
            held->size.x -= delta.x;
          }
          if (resizeDirs.flags.right)
          {
            held->pos.x += delta.x/2.0f;
            held->size.x += delta.x;
          }
          if (resizeDirs.flags.top)
          {
            held->pos.y += delta.y/2.0f;
            held->size.y -= delta.y;
          }
          if (resizeDirs.flags.bottom)
          {
            held->pos.y += delta.y/2.0f;
            held->size.y += delta.y;
          }
        }
      }
      mPos = glm::ivec2(move->position.x, move->position.y);
    } else if (const sf::Event::MouseWheelScrolled* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
    {
      scrollValue += scroll->delta;
    }
  }
}

GUIElement::ElementType GUIElement::getType()
{
  return type;
}

glm::mat3 GUIElement::normalizationTransform(sf::RenderTarget& SCREEN)
{
  return glm::mat3(glm::vec3(SCREEN.getSize().x*0.5f, 0, 0), glm::vec3(0, SCREEN.getSize().y*0.5f, 0), glm::vec3(SCREEN.getSize().x*0.5f, SCREEN.getSize().y*0.5f, 1.0f));
}

std::shared_ptr<GUIElement> GUIElement::held = nullptr;
GUIElement::ResizeDirs GUIElement::resizeDirs;
sf::RenderTarget* GUIElement::SCREEN = nullptr;

glm::ivec2 GUIElement::mPos(0);
float  GUIElement::scrollValue = 0.0f;
