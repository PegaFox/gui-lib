#include "window.h"

#include "../window.hpp"

using namespace pfui;

extern "C"
{
  const char* PFUI_WindowGetTitle(PFUI_Window* self, size_t* textLength)
  {
    if (textLength)
    {
      *textLength = ((Window*)self)->title.length();
    }

    return ((Window*)self)->title.c_str();
  }

  const char* PFUI_WindowSetTitle(PFUI_Window* self, const char* text, size_t textLength)
  {
    ((Window*)self)->title.assign(text, text + textLength);

    return ((Window*)self)->title.c_str();
  }

  bool* PFUI_WindowDraggablePtr(PFUI_Window* self)
  {
    return &((Window*)self)->isDraggable;
  }

  bool* PFUI_WindowTitlebarPtr(PFUI_Window* self)
  {
    return &((Window*)self)->hasTitlebar;
  }

  bool* PFUI_WindowResizeablePtr(PFUI_Window* self)
  {
    return &((Window*)self)->resizeable;
  }

  bool* PFUI_WindowCloseButtonPtr(PFUI_Window* self)
  {
    return &((Window*)self)->closeButton;
  }

  bool* PFUI_WindowMaximizeButtonPtr(PFUI_Window* self)
  {
    return &((Window*)self)->maximizeButton;
  }

  bool* PFUI_WindowMinimizeButtonPtr(PFUI_Window* self)
  {
    return &((Window*)self)->minimizeButton;
  }

  PFUI_Window* PFUI_WindowInit(void** children, uint8_t childCount)
  {
    return (PFUI_Window*)new Window((GUIElement* const *)children, (GUIElement* const *)children + childCount);
  }

  void PFUI_WindowDeinit(PFUI_Window* self)
  {
    delete (Window*)self;
  }

  void PFUI_WindowSetOpen(PFUI_Window* self, bool open)
  {
    ((Window*)self)->setOpen(open);
  }

  bool PFUI_WindowIsOpen(PFUI_Window* self)
  {
    return ((Window*)self)->isOpen();
  }

  void PFUI_WindowSetMaximize(PFUI_Window* self, bool maximize)
  {
    ((Window*)self)->setMaximize(maximize);
  }

  bool PFUI_WindowIsMaximized(PFUI_Window* self)
  {
    return ((Window*)self)->isMaximized();
  }

  void PFUI_WindowSetMinimize(PFUI_Window* self, bool minimize)
  {
    ((Window*)self)->setMinimize(minimize);
  }

  bool PFUI_WindowIsMinimized(PFUI_Window* self)
  {
    return ((Window*)self)->isMinimized();
  }

  void* PFUI_WindowAddChild(PFUI_Window* self, void* child, uint8_t index)
  {
    return ((Window*)self)->addChild((GUIElement*)child, index);
  }

  // removes and frees the child's memory
  bool PFUI_WindowRemoveChild(PFUI_Window* self, uint8_t index)
  {
    return ((Window*)self)->removeChild(index);
  }

  void* PFUI_WindowGetChild(PFUI_Window* self, uint8_t index)
  {
    return (*(Window*)self)[index];
  }

  uint8_t PFUI_WindowChildCount(PFUI_Window* self)
  {
    return ((Window*)self)->childCount();
  }
}
