cmake_minimum_required (VERSION 3.8)

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

add_executable (HelloOpenGL main.cpp "D:/dev/lib/glad.c")

target_include_directories(HelloOpenGL PRIVATE "D:/dev/lib")
target_link_libraries(HelloOpenGL PRIVATE SFML::Graphics)
target_compile_features(HelloOpenGL PRIVATE cxx_std_17)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HelloOpenGL PROPERTY CXX_STANDARD 20)
endif()
