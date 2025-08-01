﻿cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HelloOpenGL")

# Install SFML lib
include (FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable (UniformTest main.cpp "D:/dev/lib/glad.c" "src/shader_loader.hpp")

target_include_directories(UniformTest PRIVATE "D:/dev/lib")
target_link_libraries(UniformTest PRIVATE SFML::Graphics)
target_compile_features(UniformTest PRIVATE cxx_std_17)

add_executable (ColorfulShape colorfulshape.cpp "D:/dev/lib/glad.c" "src/shader_loader.hpp")

target_include_directories(ColorfulShape PRIVATE "D:/dev/lib")
target_link_libraries(ColorfulShape PRIVATE SFML::Graphics)
target_compile_features(ColorfulShape PRIVATE cxx_std_17)

# * Exercise 1
add_executable (Exercise1 exercise1.cpp "D:/dev/lib/glad.c" "src/shader_loader.hpp")

target_include_directories(Exercise1 PRIVATE "D:/dev/lib")
target_link_libraries(Exercise1 PRIVATE SFML::Graphics)
target_compile_features(Exercise1 PRIVATE cxx_std_17)

# * Exercise 2
add_executable (Exercise2 exercise2.cpp "D:/dev/lib/glad.c" "src/shader_loader.hpp")

target_include_directories(Exercise2 PRIVATE "D:/dev/lib")
target_link_libraries(Exercise2 PRIVATE SFML::Graphics)
target_compile_features(Exercise2 PRIVATE cxx_std_17)

# * Exercise 3
add_executable (Exercise3 exercise3.cpp "D:/dev/lib/glad.c" "src/shader_loader.hpp")

target_include_directories(Exercise3 PRIVATE "D:/dev/lib")
target_link_libraries(Exercise3 PRIVATE SFML::Graphics)
target_compile_features(Exercise3 PRIVATE cxx_std_17)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UniformTest PROPERTY CXX_STANDARD 20)
  set_property(TARGET ColorfulShape PROPERTY CXX_STANDARD 20)
  set_property(TARGET Exercise1 PROPERTY CXX_STANDARD 20)
  set_property(TARGET Exercise2 PROPERTY CXX_STANDARD 20)
  set_property(TARGET Exercise3 PROPERTY CXX_STANDARD 20)
endif()
