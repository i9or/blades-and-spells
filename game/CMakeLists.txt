add_executable(game
        main.c
        grid.c
        keyboard.c
        triangle.c
        camera.c)

target_include_directories(game PRIVATE include)
target_compile_features(game PRIVATE c_std_99)

target_link_libraries(game PRIVATE shared_library GLUT::GLUT OpenGL::GL)