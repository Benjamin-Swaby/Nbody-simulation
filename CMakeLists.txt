include(CheckLanguage)
check_language(CUDA)

cmake_minimum_required(VERSION 3.10)

enable_language(CUDA)

project(Nbody
          VERSION 1.0
          LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(Nbody 
        src/main.cpp
        lib/body.cpp
        tests/tests.cpp
        kernel/launcher.cu
        lib/render.cpp
        )


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
target_link_libraries(Nbody  ${SDL2_LIBRARIES})




target_include_directories(Nbody
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
