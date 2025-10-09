#ifndef PEGAFOX_GUI_LIB_C_DRAG_BOX_H
#define PEGAFOX_GUI_LIB_C_DRAG_BOX_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_DragBox PFUI_DragBox;

PFUI_DragBox* PFUI_DragBoxInit(void** children = NULL, size_t childCount = 0);

void PFUI_DragBoxDeinit(PFUI_DragBox* self);

void* PFUI_DragBoxAddChild(PFUI_DragBox* self, void* child, uint8_t index = -1);

// removes and frees the child's memory
bool PFUI_DragBoxRemoveChild(PFUI_DragBox* self, uint8_t index = -1);

void* PFUI_DragBoxGetChild(PFUI_DragBox* self, uint8_t index);

uint8_t PFUI_DragBoxChildCount(PFUI_DragBox* self);

#ifdef __cplusplus
}
#endif

#endif
