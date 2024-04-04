add_executable(editor
        main.c)

target_include_directories(editor PRIVATE include)
target_compile_features(editor PRIVATE c_std_99)

target_link_libraries(editor PRIVATE shared_library GLUT::GLUT OpenGL::GL)