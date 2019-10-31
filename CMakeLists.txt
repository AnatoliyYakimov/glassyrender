cmake_minimum_required(VERSION 3.15)

project(GlassyRender)

set(CMAKE_CXX_STANDARD 17)

add_executable(GlassyRender main.cpp Constants.h include/scene/viewport.h sources/scene/model.cpp include/scene/model.h include/scene/scene3d.h include/entities/point.h include/entities/sphere.h include/entities/vec.h include/entities/i_light_source.h include/entities/objects.h include/entities/matrix.h include/entities/affine_transform.h include/entities/vector_utils.h sources/scene/scene3d.cpp sources/scene/viewport.cpp sources/entities/affine_transform.cpp include/algorithms/kernel.cpp include/algorithms/kernel.h)

