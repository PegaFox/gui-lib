#ifndef PEGAFOX_GUI_LIB_PARAGRAPH_HPP
#define PEGAFOX_GUI_LIB_PARAGRAPH_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "gui_element.hpp"

namespace pfui
{
  class Paragraph : public GUIElement
  {
    public:
      static sf::Font font;
      sf::Text text = sf::Text(font);

      bool scrollable = false;
      uint32_t drawStart = 0;

      enum class WrapMode: uint8_t
      {
        None,
        LetterWrap,
        WordWrap
      } wrapMode = WrapMode::WordWrap;
  
      Paragraph();
  
      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f));
    private:
  };
}

#endif
