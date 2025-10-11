#ifndef PEGAFOX_GUI_LIB_C_VERTEX_ARRAY_H
#define PEGAFOX_GUI_LIB_C_VERTEX_ARRAY_H

#include <stddef.h>

#include "gui_element.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_VertexArray PFUI_VertexArray;

typedef enum
{
  PFUI_AABB,
  PFUI_Line,
  PFUI_LineStrip,
} PFUI_VertexArrayType;

PFUI_VertexArrayType* PFUI_VertexArrayRenderTypePtr(PFUI_VertexArray* self);

PFUI_Color* PFUI_VertexArrayColorPtr(PFUI_VertexArray* self);

PFUI_Vec2* PFUI_VertexArrayGetVertices(PFUI_VertexArray* self, size_t* vertexCount);
PFUI_Vec2* PFUI_VertexArraySetVertices(PFUI_VertexArray* self, PFUI_Vec2* vertices, size_t vertexCount);

PFUI_VertexArray* PFUI_VertexArrayInit();

void PFUI_VertexArrayDeinit(PFUI_VertexArray* self);

#ifdef __cplusplus
}
#endif

#endif
