cmake_minimum_required(VERSION 3.22)

project(trabalho-cg)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

# Obtendo tiny_obj_loader
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG        release
)
FetchContent_MakeAvailable(tinyobjloader)

# Obtendo stb_image
FetchContent_Declare(
    stb_image
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb_image)

# Adicione a GLM
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(trabalho-cg main.cpp)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ./artifacts/
    ./utils/
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${tinyobjloader_SOURCE_DIR}/include  # Incluir o diretório de cabeçalhos do tinyobjloader
    ${stb_image_SOURCE_DIR}                # Incluir o diretório de cabeçalhos do stb_image
    .
)

target_link_libraries(trabalho-cg
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    glm::glm
    ${GLEW_LIBRARIES}
    tinyobjloader
)
