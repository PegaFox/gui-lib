#include "c/slider.h"

#include "slider.hpp"

using namespace pfui;

extern "C"
{
  float* PFUI_SliderValuePtr(PFUI_Slider* self)
  {
    return &((Slider*)self)->value;
  }

  float* PFUI_SliderMinPtr(PFUI_Slider* self)
  {
    return &((Slider*)self)->min;
  }

  float* PFUI_SliderMaxPtr(PFUI_Slider* self)
  {
    return &((Slider*)self)->max;
  }

  float* PFUI_SliderStepSizePtr(PFUI_Slider* self)
  {
    return &((Slider*)self)->stepSize;
  }

  PFUI_SliderOnChange* PFUI_SliderOnChangePtr(PFUI_Slider* self)
  {
    return &((Slider*)self)->onChange;
  }

  PFUI_Slider* PFUI_SliderInit()
  {
    return (PFUI_Slider*)new Slider;
  }

  void PFUI_SliderDeinit(PFUI_Slider* self)
  {
    delete (Slider*)self;
  }
}
