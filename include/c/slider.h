#ifndef PEGAFOX_GUI_LIB_C_SLIDER_H
#define PEGAFOX_GUI_LIB_C_SLIDER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PFUI_Slider PFUI_Slider;

typedef void (*PFUI_SliderOnChange)(float currentValue);

float** PFUI_SliderValuePtr(PFUI_Slider* self);

float* PFUI_SliderMinPtr(PFUI_Slider* self);

float* PFUI_SliderMaxPtr(PFUI_Slider* self);

float* PFUI_SliderStepSizePtr(PFUI_Slider* self);

PFUI_SliderOnChange* PFUI_SliderOnChangePtr(PFUI_Slider* self);

PFUI_Slider* PFUI_SliderInit();

void PFUI_SliderDeinit(PFUI_Slider* self);

#ifdef __cplusplus
}
#endif

#endif
