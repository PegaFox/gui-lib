#ifndef PEGAFOX_GUI_LIB_C_DRAG_BOX_H
#define PEGAFOX_GUI_LIB_C_DRAG_BOX_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_DragBox PFUI_DragBox;

PFUI_DragBox* PFUI_DragBoxInit(void* const * children, size_t childCount);

void PFUI_DragBoxDeinit(PFUI_DragBox* self);

void* PFUI_DragBoxAddChild(PFUI_DragBox* self, void* child, uint8_t index);

// removes and frees the child's memory
bool PFUI_DragBoxRemoveChild(PFUI_DragBox* self, uint8_t index);

void* PFUI_DragBoxGetChild(PFUI_DragBox* self, uint8_t index);

uint8_t PFUI_DragBoxChildCount(PFUI_DragBox* self);

#ifdef __cplusplus
}
#endif

#endif
