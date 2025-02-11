#ifndef PEGAFOX_GUI_LIB_GUI_ELEMENT_HPP
#define PEGAFOX_GUI_LIB_GUI_ELEMENT_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <memory>

namespace pfui
{
  class GUIElement
  {
    public:
      enum class ElementType
      {
        None,// this is for invalid states and should not be used regularly in-game
        Window,
        Paragraph,
        Button,
        VertexArray,
        DragField,
        DragBox
      };

      // normalized, -1.0 to 1.0 range coordinate
      glm::vec2 pos = glm::vec2(0.0f);

      // 0.0 to 2.0 coordinate representing size relative to render space
      glm::vec2 size = glm::vec2(2.0f);

      // must be called for all events in order for gui elements to be interactable
      static void getEvent(sf::Event& event);

      ElementType getType();

      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f)) = 0;
    protected:
      struct HeldDeleter
      {
        void operator()(GUIElement* ptr)
        {
          return;
        }
      };

      ElementType type;

      union ResizeDirs {
        struct Flags {
          bool top: 1;
          bool bottom: 1;
          bool left: 1;
          bool right: 1;
        } flags;
        uint8_t value;
      };

      static std::shared_ptr<GUIElement> held;
      static ResizeDirs resizeDirs;
      static sf::RenderTarget* SCREEN;

      static glm::ivec2 mPos;
      static float scrollValue;

      static glm::mat3 normalizationTransform(sf::RenderTarget& SCREEN);
  };
}

#endif