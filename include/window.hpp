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

      Window(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd);

      void setOpen(bool open);

      bool isOpen();

      void setMaximize(bool maximize);

      bool isMaximized();

      void setMinimize(bool minimize);

      bool isMinimized();

      GUIElement* addChild(GUIElement* child, uint8_t index = -1, bool heapAllocated = true);

      bool removeChild(uint8_t index = -1);

      GUIElement* operator[](uint8_t index);

      uint8_t childCount();

      Rect getGlobalBounds() const override;

      ElementType getType() const override;

      void draw() override;
    private:
      std::pair<std::array<std::shared_ptr<GUIElement>, 32>, uint8_t> children;
      VertexArray body = VertexArray(VertexArray::Type::AABB);
      VertexArray titlebar = VertexArray(VertexArray::Type::AABB);
      VertexArray closeSpr = VertexArray(VertexArray::Type::Line);
      VertexArray maximizeSpr = VertexArray(VertexArray::Type::LineStrip);
      VertexArray minimizeSpr = VertexArray(VertexArray::Type::Line);

      float close = 1.0f;
      float maximize = 0.0f;
      float minimize = 1.0f;

      void init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd);
  };
}

#endif
