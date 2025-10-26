#ifndef PEGAFOX_GUI_LIB_C_SELECTION_H
#define PEGAFOX_GUI_LIB_C_SELECTION_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_Selection PFUI_Selection;

typedef struct
{
  uint16_t width;
  uint16_t height;
} PFUI_SelectionVec2;

typedef void (*PFUI_SelectionOnChange)(uint16_t index);

PFUI_SelectionVec2* PFUI_SelectionOptionDimensionsPtr(PFUI_Selection* self);

uint16_t** PFUI_SelectionSelectedIndexPtr(PFUI_Selection* self);

PFUI_SelectionOnChange* PFUI_SelectionOnChangePtr(PFUI_Selection* self);

PFUI_Selection* PFUI_SelectionInit();

void PFUI_SelectionDeinit(PFUI_Selection* self);

#ifdef __cplusplus
}
#endif

#endif
