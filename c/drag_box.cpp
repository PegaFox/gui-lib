#include "drag_box.h"

#include "../drag_box.hpp"

using namespace pfui;

extern "C"
{
  PFUI_DragBox* PFUI_DragBoxInit(void** children, size_t childCount)
  {
    return (PFUI_DragBox*)new DragBox((GUIElement* const *)children, (GUIElement* const *)children + childCount);
  }

  void PFUI_DragBoxDeinit(PFUI_DragBox* self)
  {
    delete (DragBox*)self;
  }

  void* PFUI_DragBoxAddChild(PFUI_DragBox* self, void* child, uint8_t index)
  {
    return ((DragBox*)self)->addChild((GUIElement*)child, index);
  }

  // removes and frees the child's memory
  bool PFUI_DragBoxRemoveChild(PFUI_DragBox* self, uint8_t index)
  {
    return ((DragBox*)self)->removeChild(index);
  }

  void* PFUI_DragBoxGetChild(PFUI_DragBox* self, uint8_t index)
  {
    return (*(DragBox*)self)[index];
  }

  uint8_t PFUI_DragBoxChildCount(PFUI_DragBox* self)
  {
    return ((DragBox*)self)->childCount();
  }
}
