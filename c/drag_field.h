#ifndef PEGAFOX_GUI_LIB_C_DRAG_FIELD_H
#define PEGAFOX_GUI_LIB_C_DRAG_FIELD_H

#include "drag_box.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_DragField PFUI_DragField;

uint8_t* PFUI_DragFieldDrawStartPtr(PFUI_DragField* self);

PFUI_DragField* PFUI_DragFieldInit(PFUI_DragBox** children = NULL, uint8_t childCount = 0, uint8_t drawStart = 0);

void PFUI_DragFieldDeinit(PFUI_DragField* self);

PFUI_DragBox* PFUI_DragFieldAddChild(PFUI_DragField* self, PFUI_DragBox* child, uint8_t index = -1);

// removes and frees the child's memory
bool PFUI_DragFieldRemoveChild(PFUI_DragField* self, uint8_t index = -1);

PFUI_DragBox* PFUI_DragFieldGetChild(PFUI_DragField* self, uint8_t index);

uint8_t PFUI_DragFieldChildCount(PFUI_DragField* self);

#ifdef __cplusplus
}
#endif

#endif
