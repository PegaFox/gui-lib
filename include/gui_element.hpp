#ifndef PEGAFOX_GUI_LIB_GUI_ELEMENT_HPP
#define PEGAFOX_GUI_LIB_GUI_ELEMENT_HPP

#include <memory>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

namespace pfui
{
  typedef glm::vec4 Color;

  typedef uint16_t FontID;

  struct Rect
  {
    glm::vec2 position;
    glm::vec2 size;

    bool contains(glm::vec2 point) const;
  };

  struct MouseButtons
  {
    bool left: 1;
    bool middle: 1;
    bool right: 1;
    bool extra1: 1;
    bool extra2: 1;
  };

  class GUIElement
  {
    public:
      static Color defaultBackgroundColor;
      static Color defaultObjectColor;
      static Color defaultBorderColor;
      static Color defaultInteractableColor;

      static void (*drawRect)(Rect rect, Color color);
      static void (*drawLine)(glm::vec2 position1, glm::vec2 position2, Color color);
      static void (*drawText)(FontID font, const char* text, glm::vec2 pos, float height, Color color);
      static Rect (*getTextBounds)(FontID font, const char* text, glm::vec2 pos, float height);

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

      glm::mat3 transform = glm::mat3(1.0f);

      // normalized, -1.0 to 1.0 range coordinate
      glm::vec2 pos = glm::vec2(0.0f);

      // 0.0 to 2.0 coordinate representing size relative to render space
      glm::vec2 size = glm::vec2(2.0f);

      // must be called each time the mouse moves in order for gui elements to be interactable
      static void updateCursor(glm::vec2 pos);

      // must be called each time a mouse button is pressed or released in order for gui elements to be interactable
      static void updateMouseButtons(MouseButtons buttonStates);

      // must be called each time the mouse scroll wheel moves in order for scrolling to work properly
      static void updateScrollWheel(float offset);

      virtual Rect getGlobalBounds() const = 0;

      virtual ElementType getType() const = 0;

      virtual void draw() = 0;
    protected:
      struct HeldDeleter
      {
        void operator()(GUIElement* ptr)
        {
          return;
        }
      };

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

      static union MouseButtonField {MouseButtons states; uint8_t value;} mPressed;
      static glm::vec2 mPos;
      static float scrollValue;

      static glm::mat3 normalizationTransform(glm::vec2 viewportSize);
  };
}

#endif
