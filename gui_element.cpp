#include "gui_element.hpp"
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

using namespace pfui;

bool Rect::contains(glm::vec2 point) const
{
  const glm::vec2 endPos = this->position + this->size;
  return point.x > this->position.x && point.y > this->position.y && point.x < endPos.x && point.y < endPos.y;
}

// The color used for 
Color GUIElement::defaultBackgroundColor = Color(0.6f, 0.2f, 0.0f, 1.0f);
Color GUIElement::defaultObjectColor = Color(0.4f, 0.2f, 0.0f, 1.0f);
Color GUIElement::defaultBorderColor = Color(0.6f, 0.6f, 0.4f, 1.0f);
Color GUIElement::defaultInteractableColor = Color(0.4f, 0.4f, 0.4f, 1.0f);

void (*GUIElement::drawRect)(Rect rect, Color color) = nullptr;
void (*GUIElement::drawLine)(glm::vec2 position1, glm::vec2 position2, Color color) = nullptr;
void (*GUIElement::drawText)(FontID font, std::string text, glm::vec2 pos, float height, Color color) = nullptr;
Rect (*GUIElement::getTextBounds)(FontID font, std::string text, glm::vec2 pos, float height) = nullptr;

// must be called each time the mouse moves in order for gui elements to be interactable
void GUIElement::updateCursor(glm::vec2 pos)
{
  //if (held != nullptr && sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SCREEN->getSize())).contains(pos))
  if (held != nullptr && Rect{glm::vec2(-1.0f), glm::vec2(2.0f)}.contains(pos))
  {
    //glm::vec2 delta = (pos - glm::vec2(mPos)) / glm::vec2(SCREEN->getSize().x*0.5f, SCREEN->getSize().y*0.5f);
    glm::vec2 delta = pos - mPos;
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
  mPos = pos;
}

// must be called each time a mouse button is pressed or released in order for gui elements to be interactable
void GUIElement::updateMouseButtons(MouseButtons buttonStates)
{
  mPressed.states = buttonStates;
}

// must be called each time the mouse scroll wheel moves in order for scrolling to work properly
void GUIElement::updateScrollWheel(float offset)
{
  scrollValue += offset;
}

glm::mat3 GUIElement::normalizationTransform(glm::vec2 viewportSize)
{
  /*return glm::mat3(
    glm::vec3(viewportSize.x*0.5f,                0.0f, 0.0f),
    glm::vec3(               0.0f, viewportSize.y*0.5f, 0.0f),
    glm::vec3(viewportSize.x*0.5f, viewportSize.y*0.5f, 1.0f));*/

  return glm::mat3(
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f));
}

std::shared_ptr<GUIElement> GUIElement::held = nullptr;
GUIElement::ResizeDirs GUIElement::resizeDirs;

GUIElement::MouseButtonField GUIElement::mPressed = {0};
glm::vec2 GUIElement::mPos(0.0f);
float  GUIElement::scrollValue = 0.0f;
