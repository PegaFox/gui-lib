#ifndef PEGAFOX_GUI_LIB_C_GUI_ELEMENT_H
#define PEGAFOX_GUI_LIB_C_GUI_ELEMENT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  PFUI_TypeNone, // this is for invalid states and should not be used regularly
  PFUI_TypeWindow,
  PFUI_TypeParagraph,
  PFUI_TypeButton,
  PFUI_TypeVertexArray,
  PFUI_TypeDragField,
  PFUI_TypeDragBox,
} PFUI_ElementType;

typedef enum
{
  PFUI_BackgroundColor,
  PFUI_ObjectColor,
  PFUI_BorderColor,
  PFUI_InteractableColor,
} PFUI_ColorType;

typedef uint16_t PFUI_FontID;

typedef struct
{
  bool left: 1;
  bool middle: 1;
  bool right: 1;
  bool extra1: 1;
  bool extra2: 1;
} PFUI_MouseButtons;

typedef struct
{
  union
  {
    float x;
    float width;
  };

  union
  {
    float y;
    float height;
  };
} PFUI_Vec2;

typedef struct
{
  float x;
  float y;
  float z;
} PFUI_Mat3Col;

typedef struct
{
  float r;
  float g;
  float b;
  float a;
} PFUI_Color;

typedef struct
{
  PFUI_Mat3Col cols[3];
} PFUI_Mat3;

typedef struct
{
  PFUI_Vec2 position;
  PFUI_Vec2 size;
} PFUI_Rect;

typedef void (*PFUI_drawRect)(PFUI_Rect rect, PFUI_Color color);
typedef void (*PFUI_drawLine)(PFUI_Vec2 position1, PFUI_Vec2 position2, PFUI_Color color);
typedef void (*PFUI_drawText)(PFUI_FontID font, const char* text, PFUI_Vec2 pos, float height, PFUI_Color color);
typedef PFUI_Rect (*PFUI_getTextBounds)(PFUI_FontID font, const char* text, PFUI_Vec2 pos, float height);

// returns null if type is an invalid enum value
PFUI_Color* PFUI_defaultColorPtr(PFUI_ColorType type);

PFUI_drawRect* PFUI_drawRectPtr();
PFUI_drawLine* PFUI_drawLinePtr();
PFUI_drawText* PFUI_drawTextPtr();
PFUI_getTextBounds* PFUI_getTextBoundsPtr();

PFUI_Mat3* PFUI_ElementTransformPtr(void* self);

// normalized, -1.0 to 1.0 range coordinate
PFUI_Vec2* PFUI_ElementPosPtr(void* self);

// 0.0 to 2.0 coordinate representing size relative to render space
PFUI_Vec2* PFUI_ElementSizePtr(void* self);

// must be called each time the mouse moves in order for gui elements to be interactable
void PFUI_updateCursor(PFUI_Vec2 pos);

// must be called each time a mouse button is pressed or released in order for gui elements to be interactable
void PFUI_updateMouseButtons(PFUI_MouseButtons buttonStates);

// must be called each time the mouse scroll wheel moves in order for scrolling to work properly
void PFUI_updateScrollWheel(float offset);

PFUI_Rect PFUI_ElementGetGlobalBounds(void* self);

PFUI_ElementType PFUI_ElementGetType(void* self);

void PFUI_ElementDraw(void* self);

#ifdef __cplusplus
}
#endif

#endif
