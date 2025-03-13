cmake_minimum_required(VERSION 3.29)
project(raycasting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8  # You can specify the version you want here
)
FetchContent_MakeAvailable(glfw)

include_directories(${glfw_SOURCE_DIR}/include)
link_directories(${glfw_BINARY_DIR}/src)

set(SOURCE_FILES src/main.cpp
        src/raycasting.cpp
        src/raycasting.h
        src/draw.cpp
        src/draw.h
)
add_executable(raycasting ${SOURCE_FILES})

target_link_libraries(raycasting glfw)
