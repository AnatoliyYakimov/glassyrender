CMAKE_MINIMUM_REQUIRED(VERSION 3.15.3)


PROJECT(FILESYSTEM VERSION 1.0 LANGUAGES CXX)

SET(PNG_SHARED OFF)
SET(PNG_TESTS OFF)
SET(PNG_HARDWARE_OPTIMIZATIONS OFF)
SET(ld-version-script OFF)

SET(YAML_CPP_BUILD_CONTRIB OFF)
SET(YAML_CPP_INSTALL OFF)

ADD_SUBDIRECTORY(ext/yaml-cpp)
ADD_SUBDIRECTORY(ext/lpng1637)
ADD_SUBDIRECTORY(ext/png++-0.2.9)

TARGET_INCLUDE_DIRECTORIES(png_static PUBLIC ext/lpng1637)



ADD_LIBRARY(FILESYSTEM INTERFACE)

FILE(GLOB FILESYSTEM_SOURCES src/**.cpp)
TARGET_SOURCES(FILESYSTEM INTERFACE ${FILESYSTEM_SOURCES})

TARGET_INCLUDE_DIRECTORIES(FILESYSTEM INTERFACE include)
TARGET_INCLUDE_DIRECTORIES(FILESYSTEM INTERFACE ext/yaml-cpp/include)

TARGET_COMPILE_FEATURES(FILESYSTEM INTERFACE cxx_std_17)

TARGET_LINK_LIBRARIES(FILESYSTEM INTERFACE PNG++ png_static)
TARGET_LINK_LIBRARIES(FILESYSTEM INTERFACE COMMON_LIB RENDER yaml-cpp::yaml-cpp)
