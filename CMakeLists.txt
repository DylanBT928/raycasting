cmake_minimum_required(VERSION 3.29)
project(raycasting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(SOURCE_FILES src/main.cpp
        src/raycasting.cpp
        src/raycasting.h
        src/draw.cpp
        src/draw.h
)
add_executable(raycasting ${SOURCE_FILES})

target_link_libraries(raycasting glfw3)
