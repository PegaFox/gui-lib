#ifndef PEGAFOX_GUI_LIB_C_BUTTON_H
#define PEGAFOX_GUI_LIB_C_BUTTON_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_Button PFUI_Button;

typedef void (*PFUI_ButtonOnChange)(bool pressed);

PFUI_ButtonOnChange* PFUI_ButtonOnChangePtr(PFUI_Button* self);

PFUI_Button* PFUI_ButtonInit();

void PFUI_ButtonDeinit(PFUI_Button* self);

bool PFUI_ButtonIsPressed(PFUI_Button* self);

#ifdef __cplusplus
}
#endif

#endif
