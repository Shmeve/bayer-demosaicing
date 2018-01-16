cmake_minimum_required(VERSION 3.9)
project(comp498_a1_demosaicing)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES src/main.cpp)
add_executable(comp498_a1_demosaicing ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(comp498_a1_demosaicing ${OpenCV_LIBS})