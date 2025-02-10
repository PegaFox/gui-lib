#include "gui_element.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

using namespace pfui;

// must be called for all events in order for gui elements to be interactable
void GUIElement::getEvent(sf::Event& event)
{
  switch (event.type)
  {
    case sf::Event::MouseMoved:
      if (held != nullptr && sf::IntRect(0, 0, SCREEN->getSize().x, SCREEN->getSize().y).contains(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)))
      {
        glm::vec2 delta = (glm::vec2(event.mouseMove.x, event.mouseMove.y) - glm::vec2(mPos)) / glm::vec2(SCREEN->getSize().x*0.5f, SCREEN->getSize().y*0.5f);
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
      mPos = glm::ivec2(event.mouseMove.x, event.mouseMove.y);
      break;
    case sf::Event::MouseWheelScrolled:
      scrollValue += event.mouseWheelScroll.delta;
      break;
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
