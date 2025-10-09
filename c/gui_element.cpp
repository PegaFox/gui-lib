#include "gui_element.h"

#include "../gui_element.hpp"

using namespace pfui;

extern "C"
{
  PFUI_Color* PFUI_defaultColorPtr(PFUI_ColorType type)
  {
    switch (type)
    {
      case PFUI_BackgroundColor:
        return (PFUI_Color*)&GUIElement::defaultBackgroundColor;
      case PFUI_ObjectColor:
        return (PFUI_Color*)&GUIElement::defaultObjectColor;
      case PFUI_BorderColor:
        return (PFUI_Color*)&GUIElement::defaultBorderColor;
      case PFUI_InteractableColor:
        return (PFUI_Color*)&GUIElement::defaultInteractableColor;
    }

    return nullptr;
  }

  PFUI_drawRect* PFUI_drawRectPtr()
  {
    return (PFUI_drawRect*)&GUIElement::drawRect;
  }
  PFUI_drawLine* PFUI_drawLinePtr()
  {
    return (PFUI_drawLine*)&GUIElement::drawLine;
  }
  PFUI_drawText* PFUI_drawTextPtr()
  {
    return (PFUI_drawText*)&GUIElement::drawText;
  }
  PFUI_getTextBounds* PFUI_getTextBoundsPtr()
  {
    return (PFUI_getTextBounds*)&GUIElement::getTextBounds;
  }

  PFUI_Mat3* PFUI_ElementTransformPtr(void* self)
  {
    return (PFUI_Mat3*)&((GUIElement*)self)->transform;
  }

  // normalized, -1.0 to 1.0 range coordinate
  PFUI_Vec2* PFUI_ElementPosPtr(void* self)
  {
    return (PFUI_Vec2*)&((GUIElement*)self)->pos;
  }

  // 0.0 to 2.0 coordinate representing size relative to render space
  PFUI_Vec2* PFUI_ElementSizePtr(void* self)
  {
    return (PFUI_Vec2*)&((GUIElement*)self)->size;
  }

  // must be called each time the mouse moves in order for gui elements to be interactable
  void PFUI_UpdateCursor(PFUI_Vec2 pos)
  {
    GUIElement::updateCursor(*(glm::vec2*)&pos);
  }

  // must be called each time a mouse button is pressed or released in order for gui elements to be interactable
  void PFUI_UpdateMouseButtons(PFUI_MouseButtons buttonStates)
  {
    GUIElement::updateMouseButtons(*(MouseButtons*)&buttonStates);
  }

  // must be called each time the mouse scroll wheel moves in order for scrolling to work properly
  void PFUI_UpdateScrollWheel(float offset)
  {
    GUIElement::updateScrollWheel(offset);
  }

  PFUI_Rect PFUI_ElementGetGlobalBounds(void* self)
  {
    Rect bounds = ((GUIElement*)self)->getGlobalBounds();

    return *(PFUI_Rect*)&bounds;
  }

  PFUI_ElementType PFUI_ElementGetType(void* self)
  {
    return (PFUI_ElementType)((GUIElement*)self)->getType();
  }

  void PFUI_ElementDraw(void* self)
  {
    ((GUIElement*)self)->draw();
  }
}
