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

  PFUI_VertexArray* PFUI_VertexArrayInit()
  {
    return (PFUI_VertexArray*)new VertexArray;
  }

  void PFUI_VertexArrayDeinit(PFUI_VertexArray* self)
  {
    delete (VertexArray*)self;
  }
}
