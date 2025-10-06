#ifndef PEGAFOX_GUI_LIB_PARAGRAPH_HPP
#define PEGAFOX_GUI_LIB_PARAGRAPH_HPP

#include "gui_element.hpp"

namespace pfui
{
  class Paragraph: public GUIElement
  {
    public:
      FontID font;
      std::string text = "Hello, World!";
      float textHeight = 2.0f;
      Color color;

      bool scrollable = false;
      uint32_t drawStart = 0;

      enum class WrapMode: uint8_t
      {
        None,
        LetterWrap,
        WordWrap
      } wrapMode = WrapMode::WordWrap;

      ElementType getType() override;
  
      void draw() override;
    private:
  };
}

#endif
