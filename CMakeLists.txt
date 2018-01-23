cmake_minimum_required(VERSION 3.5)
project(comp498_a1_demosaicing)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES src/main.cpp src/Demosaic.cpp src/Demosaic.h)
add_executable(comp498_a1_demosaicing ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(comp498_a1_demosaicing ${OpenCV_LIBS})
add_custom_command(TARGET comp498_a1_demosaicing PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:comp498_a1_demosaicing>/images)