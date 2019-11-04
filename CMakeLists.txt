cmake_minimum_required(VERSION 3.15)

project(GlassyRender)

set(CMAKE_CXX_STANDARD 17)

add_executable(GlassyRender main.cpp Constants.h include/scene/viewport.h sources/scene/model.cpp include/scene/model.h include/scene/scene3d.h include/entities/algebra/point.h include/entities/model_objects/sphere.h include/entities/algebra/vec.h include/entities/model_objects/i_light_source.h include/entities/model_objects/objects.h include/entities/algebra/matrix.h include/entities/algebra/affine_transform.h include/entities/algebra/vector_utils.h sources/scene/scene3d.cpp sources/scene/viewport.cpp sources/entities/algebra/affine_transform.cpp sources/algorithms/kernel.cpp include/algorithms/kernel.h sources/algorithms/brdf.cpp include/algorithms/brdf.h include/entities/model_objects/material.h sources/color/rgb.cpp include/entities/color/rgb.h include/algorithms/cook_torrance.h)

