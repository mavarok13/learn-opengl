cmake_minimum_required(VERSION 3.22)

project("Textures" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include (FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(hello_texture    main.cpp
                                D:/dev/lib/glad.c
                                stb_image.cpp)

target_link_libraries(hello_texture PRIVATE SFML::Graphics)
target_include_directories(hello_texture PRIVATE D:/dev/lib)