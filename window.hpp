#ifndef PEGAFOX_GUI_LIB_WINDOW_HPP
#define PEGAFOX_GUI_LIB_WINDOW_HPP

#include <cstdint>
#include <array>
#include <memory>
#include <string>
#include "vertex_array.hpp"

namespace pfui
{
  class Window: public GUIElement
  {
    public:
      std::string title;

      // windowBind forces the window to remain on screen
      //bool windowBind = true;

      bool isDraggable = true;
      bool hasTitlebar = true;
      bool resizeable = true;

      bool closeButton = true;
      bool maximizeButton = true;
      bool minimizeButton = true;

      Window(const std::initializer_list<GUIElement*>& children = {});

      void setOpen(bool open);

      bool isOpen();

      void setMaximize(bool maximize);

      bool isMaximized();

      void setMinimize(bool minimize);

      bool isMinimized();

      GUIElement* addChild(GUIElement* child);

      bool removeChild();

      GUIElement* operator[](uint8_t index);

      uint8_t childNum();

      sf::FloatRect getGlobalBounds();

      virtual void draw(sf::RenderTarget& SCREEN, glm::mat3 transform = glm::mat3(0.0f));
    private:
      std::pair<std::array<std::unique_ptr<GUIElement>, 32>, uint8_t> children;
      VertexArray body;
      VertexArray titlebar;
      VertexArray closeSpr;
      VertexArray maximizeSpr;
      VertexArray minimizeSpr;

      float close = 1.0f;
      float maximize = 0.0f;
      float minimize = 1.0f;
  };
}

#endif
