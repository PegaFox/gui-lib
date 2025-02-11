cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

project(gui-lib)

add_library(gui-lib STATIC gui_element.cpp window.cpp vertex_array.cpp paragraph.cpp button.cpp drag_field.cpp drag_box.cpp)