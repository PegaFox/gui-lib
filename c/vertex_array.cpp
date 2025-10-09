#include "vertex_array.h"

#include "../vertex_array.hpp"

using namespace pfui;

extern "C"
{
  PFUI_VertexArrayType* PFUI_VertexArrayRenderTypePtr(PFUI_VertexArray* self)
  {
    return (PFUI_VertexArrayType*)&((VertexArray*)self)->renderType;
  }

  PFUI_Color* PFUI_VertexArrayColorPtr(PFUI_VertexArray* self)
  {
    return (PFUI_Color*)&((VertexArray*)self)->color;
  }

  PFUI_Vec2* PFUI_VertexArrayGetVertices(PFUI_VertexArray* self, size_t* vertexCount)
  {
    if (vertexCount)
    {
      *vertexCount = ((VertexArray*)self)->vertices.size();
    }

    return (PFUI_Vec2*)((VertexArray*)self)->vertices.data();
  }

  PFUI_Vec2* PFUI_VertexArraySetVertices(PFUI_VertexArray* self, PFUI_Vec2* vertices, size_t vertexCount)
  {
    ((VertexArray*)self)->vertices.assign((glm::vec2*)vertices, (glm::vec2*)vertices + vertexCount);

    return (PFUI_Vec2*)((VertexArray*)self)->vertices.data();
  }

  PFUI_VertexArray* PFUI_VertexArrayInit(PFUI_VertexArrayType renderType, PFUI_Color color, PFUI_Vec2* vertices, size_t vertexCount)
  {
    PFUI_VertexArray* vertexArray = (PFUI_VertexArray*)new VertexArray;

    *PFUI_VertexArrayRenderTypePtr(vertexArray) = renderType;
    *PFUI_VertexArrayColorPtr(vertexArray) = color;
    PFUI_VertexArraySetVertices(vertexArray, vertices, vertexCount);

    return vertexArray;
  }

  void PFUI_VertexArrayDeinit(PFUI_VertexArray* self)
  {
    delete (VertexArray*)self;
  }
}
