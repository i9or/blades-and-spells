file(GLOB HEADER_LIST CONFIGURE_DEPENDS "include/*.h")

add_library(shared_library STATIC
        dynamic_array.c
        face.c
        load_obj.c
        logger.c
        mesh.c
        tex2.c
        vec3.c
        ${HEADER_LIST})

target_include_directories(shared_library PUBLIC ./include)
target_compile_features(shared_library PUBLIC c_std_99)