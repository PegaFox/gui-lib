#include "c/selection.h"

#include "selection.hpp"

using namespace pfui;

extern "C"
{
  PFUI_SelectionVec2* PFUI_SelectionOptionDimensionsPtr(PFUI_Selection* self)
  {
    return (PFUI_SelectionVec2*)&((Selection*)self)->optionDimensions;
  }

  uint16_t** PFUI_SelectionSelectedIndexPtr(PFUI_Selection* self)
  {
    return &((Selection*)self)->selectedIndex;
  }

  PFUI_SelectionOnChange* PFUI_SelectionOnChangePtr(PFUI_Selection* self)
  {
    return &((Selection*)self)->onChange;
  }

  PFUI_Selection* PFUI_SelectionInit()
  {
    return (PFUI_Selection*)new Selection;
  }

  void PFUI_SelectionDeinit(PFUI_Selection* self)
  {
    delete (Selection*)self;
  }

  PFUI_Rect PFUI_SelectionGetSelectedBounds(PFUI_Selection* self)
  {
    Rect bounds = ((Selection*)self)->getSelectedBounds();

    return *(PFUI_Rect*)&bounds;
  }
}
