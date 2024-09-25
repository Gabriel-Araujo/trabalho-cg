cmake_minimum_required(VERSION 3.22)

project(trabalhocg)

set(CMAKE_CXX_STANDARD 20)

add_executable(trabalhocg main.cpp
        utils/gridplane.h
        utils/constants.h
        utils/keyboard.h
        utils/camera.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(trabalhocg ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )