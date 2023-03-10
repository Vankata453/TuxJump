cmake_minimum_required(VERSION 3.7)

project(TuxJump)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PhysFS REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PHYSFS_INCLUDE_DIR})
include_directories(src)

file(GLOB SRCFILES src/*.cpp src/collision/*.cpp src/control/*.cpp src/game/*.cpp src/gui/*.cpp src/gui/menu/*.cpp src/level/*.cpp src/util/*.cpp src/video/*.cpp)
file(COPY data/ DESTINATION data)
add_executable(TuxJump ${SRCFILES})

target_link_libraries(TuxJump ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)
target_link_libraries(TuxJump ${PHYSFS_LIBRARY})
