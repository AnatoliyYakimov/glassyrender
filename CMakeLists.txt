cmake_minimum_required(VERSION 3.15)

project(GlassyRender)

set(CMAKE_CXX_STANDARD 17)

add_executable(GlassyRender main.cpp Constants.h Scene3D/viewport.h Scene3D/model.cpp Scene3D/model.h Scene3D/scene3d.h Entities/point.h Entities/sphere.h Entities/vec.h Entities/i_light_source.h algorithms/render.h Entities/objects.h Entities/matrix.h)

