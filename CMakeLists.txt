CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

PROJECT(GlassyRender)
SET(CMAKE_CXX_STANDARD 17)

set(Boost_COMPILER       "-mgw10")
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.62.0 COMPONENTS filesystem)
find_package(OpenGL)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    ADD_EXECUTABLE(GlassyRender main.cpp Constants.h include/scene/viewport.h sources/scene/model.cpp include/scene/model.h
                   include/scene/scene3d.h include/entities/model_objects/sphere.h
                   include/entities/algebra/vec.h include/entities/model_objects/i_light_source.h
                   include/entities/model_objects/i_object.h include/entities/algebra/matrix.h
                   include/entities/algebra/affine_transform.h include/entities/algebra/vector_utils.h
                   sources/scene/scene3d.cpp sources/scene/viewport.cpp sources/entities/algebra/affine_transform.cpp
                   sources/algorithms/kernel.cpp include/algorithms/kernel.h sources/algorithms/brdf.cpp
                   include/algorithms/brdf.h
                   include/algorithms/cook_torrance.h
                   include/utils/obj_file_handler.cpp include/utils/obj_file_handler.h include/entities/model_objects/polygonal_object.h
                   include/entities/textures/i_rgb_texture.h
                   lib/tga/tga.hpp include/entities/color/color_utils.h include/entities/textures/texture_map_loader.cpp include/entities/textures/texture_map_loader.h include/enviroment/enviroment.h include/entities/textures/i_monochrome_texture.cpp include/entities/textures/i_monochrome_texture.h)

    target_link_libraries(GlassyRender ${Boost_LIBRARIES})
endif()
