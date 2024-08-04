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

file(GLOB_RECURSE BNS_SOURCES CONFIGURE_DEPENDS src/*.c src/*.h)

set(BNS_GAME_SOURCES
  src/game.c
  src/camera.c
  src/camera.h
  src/grid.c
  src/grid.h
  src/keyboard.h
  src/keyboard.c
  src/triangle.c
  src/triangle.h
  src/data/dynamic_array.c
  src/data/dynamic_array.h
  src/data/face.c
  src/data/face.h
  src/data/image.c
  src/data/image.h
  src/data/material.c
  src/data/material.h
  src/data/mesh.c
  src/data/mesh.h
  src/data/tex2.c
  src/data/tex2.h
  src/data/vec3.c
  src/data/vec3.h
  src/loaders/load_mtl.c
  src/loaders/load_mtl.h
  src/loaders/load_obj.c
  src/loaders/load_obj.h
  src/loaders/load_tga.c
  src/loaders/load_tga.h
  src/utils/constants.h
  src/utils/logger.c
  src/utils/logger.h
  src/utils/utilities.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BNS_GAME_SOURCES})

add_executable(${PROJECT_NAME} ${BNS_GAME_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)
target_link_libraries(${PROJECT_NAME} GLUT::GLUT OpenGL::GL)

set(BNS_EDITOR_SOURCES
  src/editor.c
  src/utils/logger.c
  src/utils/logger.h
)

add_executable(editor ${BNS_EDITOR_SOURCES})
target_compile_features(editor PRIVATE c_std_99)
target_link_libraries(editor GLUT::GLUT OpenGL::GL)
