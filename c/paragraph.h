#ifndef PEGAFOX_GUI_LIB_C_PARAGRAPH_H
#define PEGAFOX_GUI_LIB_C_PARAGRAPH_H

#include <stddef.h>

#include "gui_element.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_Paragraph PFUI_Paragraph;

typedef enum
{
  PFUI_None,
  PFUI_LetterWrap,
  PFUI_WordWrap,
} PFUI_ParagraphWrapMode;

PFUI_FontID* PFUI_ParagraphFontPtr(PFUI_Paragraph* self);

const char* PFUI_ParagraphGetText(PFUI_Paragraph* self, size_t* textLength = NULL);
const char* PFUI_ParagraphSetText(PFUI_Paragraph* self, const char* text, size_t textLength);

float* PFUI_ParagraphTextHeightPtr(PFUI_Paragraph* self);

PFUI_Color* PFUI_ParagraphColorPtr(PFUI_Paragraph* self);

bool* PFUI_ParagraphScrollablePtr(PFUI_Paragraph* self);

uint32_t* PFUI_ParagraphDrawStartPtr(PFUI_Paragraph* self);

PFUI_ParagraphWrapMode* PFUI_ParagraphWrapModePtr(PFUI_Paragraph* self);

PFUI_Paragraph* PFUI_ParagraphInit(
  PFUI_FontID font,
  PFUI_Color color,
  const char* text = NULL,
  size_t textLength = 0,
  float textHeight = 2.0f,
  bool scrollable = false,
  uint32_t drawStart = 0);

void PFUI_ParagraphDeinit(PFUI_Paragraph* self);

#ifdef __cplusplus
}
#endif

#endif
