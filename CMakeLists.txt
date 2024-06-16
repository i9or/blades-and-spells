cmake_minimum_required(VERSION 3.28)
project(blades_and_spells LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
endif ()

set(PROJECT_OUTPUT_BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_BIN_DIR}")

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories({GLUT_INCLUDE_DIR} {OPENGL_INCLUDE_DIR})

add_subdirectory(shared)
add_subdirectory(game)
add_subdirectory(editor)
