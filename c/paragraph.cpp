#include "paragraph.h"

#include "../paragraph.hpp"

using namespace pfui;

extern "C"
{
  PFUI_FontID* PFUI_ParagraphFontPtr(PFUI_Paragraph* self)
  {
    return (PFUI_FontID*)&((Paragraph*)self)->font;
  }

  const char* PFUI_ParagraphGetText(PFUI_Paragraph* self, size_t* textLength)
  {
    if (textLength)
    {
      *textLength = ((Paragraph*)self)->text.length();
    }

    return ((Paragraph*)self)->text.c_str();
  }

  const char* PFUI_ParagraphSetText(PFUI_Paragraph* self, const char* text, size_t textLength)
  {
    ((Paragraph*)self)->text.assign(text, text + textLength);

    return ((Paragraph*)self)->text.c_str();
  }

  float* PFUI_ParagraphTextHeightPtr(PFUI_Paragraph* self)
  {
    return &((Paragraph*)self)->textHeight;
  }

  PFUI_Color* PFUI_ParagraphColorPtr(PFUI_Paragraph* self)
  {
    return (PFUI_Color*)&((Paragraph*)self)->color;
  }

  bool* PFUI_ParagraphScrollablePtr(PFUI_Paragraph* self)
  {
    return &((Paragraph*)self)->scrollable;
  }

  uint32_t* PFUI_ParagraphDrawStartPtr(PFUI_Paragraph* self)
  {
    return &((Paragraph*)self)->drawStart;
  }

  PFUI_ParagraphWrapMode* PFUI_ParagraphWrapModePtr(PFUI_Paragraph* self)
  {
    return (PFUI_ParagraphWrapMode*)&((Paragraph*)self)->wrapMode;
  }

  PFUI_Paragraph* PFUI_ParagraphInit(
    PFUI_FontID font,
    PFUI_Color color,
    const char* text,
    size_t textLength,
    float textHeight,
    bool scrollable,
    uint32_t drawStart)
  {
    PFUI_Paragraph* paragraph = (PFUI_Paragraph*)new Paragraph;

    *PFUI_ParagraphFontPtr(paragraph) = font;
    *PFUI_ParagraphColorPtr(paragraph) = color;
    PFUI_ParagraphSetText(paragraph, text, textLength);
    *PFUI_ParagraphTextHeightPtr(paragraph) = textHeight;
    *PFUI_ParagraphScrollablePtr(paragraph) = scrollable;
    *PFUI_ParagraphDrawStartPtr(paragraph) = drawStart;

    return paragraph;
  }

  void PFUI_ParagraphDeinit(PFUI_Paragraph* self)
  {
    delete (Paragraph*)self;
  }
}
