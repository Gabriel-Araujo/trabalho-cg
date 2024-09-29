cmake_minimum_required(VERSION 3.22)

project(trabalho-cg)

set(CMAKE_CXX_STANDARD 20)
# Adicione a GLM
find_package(glm REQUIRED)

add_executable(trabalho-cg main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ./artifacts/ ./utils/)

target_link_libraries(trabalho-cg ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glm::glm)