CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

PROJECT(GlassyRender)
SET(CMAKE_CXX_STANDARD 17)
FIND_PACKAGE(Boost)
FIND_PACKAGE(OPENGL REQUIRED COMPONENTs OPENGL)

SET(NANOGUI_BUILD_EXAMPLE OFF)
SET(NANOGUI_BUILD_PYTHON OFF)
SET(NANOGUI_BUILD_SHARED OFF)
SET(NANOGUI_USE_GLAD ON)
SET(NANOGUI_ADDITIONAL_FLAGS "-Wno-cast-function-type -Wno-misleading-indentation -Wno-unused-function -Wno-unknown-pragmas -Wno-implicit-fallthrough")
SET(GCC_ADDITIONAL_FLAGS "-static ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NANOGUI_ADDITIONAL_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ${GCC_ADDITIONAL_FLAGS} -mstackrealign")
ADD_SUBDIRECTORY(lib/nanogui)

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
IF (${CMAKE_BUILD_TYPE} STREQUAL Release)
    TARGET_COMPILE_OPTIONS(GlassyRender PRIVATE -Ofast)
ENDIF ()



TARGET_LINK_LIBRARIES(GlassyRender nanogui)
TARGET_INCLUDE_DIRECTORIES(GlassyRender PRIVATE ${NANOGUI_EXTRA_INCS})
TARGET_INCLUDE_DIRECTORIES(GlassyRender PRIVATE lib/nanogui/include)
TARGET_INCLUDE_DIRECTORIES(GlassyRender PRIVATE ${Boost_INCLUDE_DIRS})

