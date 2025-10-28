#include "c/drag_field.h"

#include "drag_field.hpp"

using namespace pfui;

extern "C"
{
  uint8_t* PFUI_DragFieldDrawStartPtr(PFUI_DragField* self)
  {
    return &((DragField*)self)->drawStart;
  }

  PFUI_DragField* PFUI_DragFieldInit(PFUI_DragBox* const * children, uint8_t childCount)
  {
    return (PFUI_DragField*)new DragField((DragBox* const *)children, (DragBox* const *)children + childCount);
  }

  void PFUI_DragFieldDeinit(PFUI_DragField* self)
  {
    delete (DragField*)self;
  }

  PFUI_DragBox* PFUI_DragFieldAddChild(PFUI_DragField* self, PFUI_DragBox* child, uint8_t index)
  {
    return (PFUI_DragBox*)((DragField*)self)->addChild((DragBox*)child, index);
  }

  // removes and frees the child's memory
  bool PFUI_DragFieldRemoveChild(PFUI_DragField* self, uint8_t index)
  {
    return ((DragField*)self)->removeChild(index);
  }

  PFUI_DragBox* PFUI_DragFieldGetChild(PFUI_DragField* self, uint8_t index)
  {
    return (PFUI_DragBox*)(*(DragField*)self)[index];
  }

  uint8_t PFUI_DragFieldChildCount(PFUI_DragField* self)
  {
    return ((DragField*)self)->childCount();
  }
}
