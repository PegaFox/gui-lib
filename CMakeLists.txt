cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

project(gui-lib)

add_library(gui-lib STATIC
  # main lib
  src/gui_element.cpp
  src/window.cpp
  src/vertex_array.cpp
  src/paragraph.cpp
  src/button.cpp
  src/selection.cpp
  src/slider.cpp
  src/drag_field.cpp
  src/drag_box.cpp

  # C declarations
  src/c/gui_element.cpp
  src/c/window.cpp
  src/c/vertex_array.cpp
  src/c/paragraph.cpp
  src/c/button.cpp
  src/c/slider.cpp
  src/c/drag_field.cpp
  src/c/drag_box.cpp
)

target_include_directories(gui-lib PRIVATE include)
