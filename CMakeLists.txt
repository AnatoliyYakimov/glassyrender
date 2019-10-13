# cmake_minimum_required(VERSION <specify CMake version here>)
project(GlassyRender)

set(CMAKE_CXX_STANDARD 17)

add_executable(GlassyRender main.cpp Constants.h Scene3D/viewport.h Scene3D/Model.cpp Scene3D/Model.h Scene3D/Scene3D.h Entities/point.h Entities/sphere.h Entities/vec.h)