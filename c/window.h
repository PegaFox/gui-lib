#ifndef PEGAFOX_GUI_LIB_C_WINDOW_H
#define PEGAFOX_GUI_LIB_C_WINDOW_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_Window PFUI_Window;

const char* PFUI_WindowGetTitle(PFUI_Window* self, size_t* textLength);
const char* PFUI_WindowSetTitle(PFUI_Window* self, const char* text, size_t textLength);

bool* PFUI_WindowDraggablePtr(PFUI_Window* self);

bool* PFUI_WindowTitlebarPtr(PFUI_Window* self);

bool* PFUI_WindowResizeablePtr(PFUI_Window* self);

bool* PFUI_WindowCloseButtonPtr(PFUI_Window* self);

bool* PFUI_WindowMaximizeButtonPtr(PFUI_Window* self);

bool* PFUI_WindowMinimizeButtonPtr(PFUI_Window* self);

PFUI_Window* PFUI_WindowInit(void** children, uint8_t childCount);

void PFUI_WindowDeinit(PFUI_Window* self);

void PFUI_WindowSetOpen(PFUI_Window* self, bool open);

bool PFUI_WindowIsOpen(PFUI_Window* self);

void PFUI_WindowSetMaximize(PFUI_Window* self, bool maximize);

bool PFUI_WindowIsMaximized(PFUI_Window* self);

void PFUI_WindowSetMinimize(PFUI_Window* self, bool minimize);

bool PFUI_WindowIsMinimized(PFUI_Window* self);

void* PFUI_WindowAddChild(PFUI_Window* self, void* child, uint8_t index);

// removes and frees the child's memory
bool PFUI_WindowRemoveChild(PFUI_Window* self, uint8_t index);

void* PFUI_WindowGetChild(PFUI_Window* self, uint8_t index);

uint8_t PFUI_WindowChildCount(PFUI_Window* self);

#ifdef __cplusplus
}
#endif

#endif
