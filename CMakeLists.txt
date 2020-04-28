cmake_minimum_required(VERSION 3.15)
project(MoviePlaiter)

set(CMAKE_CXX_STANDARD 11)

set(FLTK_SKIP_FLUID)
find_package(FLTK REQUIRED)

include_directories(Model)
include_directories(Utils)
include_directories(View)

add_executable(ConnectTheNumbers
        main.cpp View/PuzzleGrid.cpp View/PuzzleGrid.h)
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${FLTK_LIBRARIES})
TARGET_LINK_LIBRARIES(ConnectTheNumbers ${OPENGL_LIBRARIES})