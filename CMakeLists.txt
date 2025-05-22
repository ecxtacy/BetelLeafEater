cmake_minimum_required(VERSION 3.10)

project(BetelLeafEater)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED SDL2_image)


set(SOURCES 
src/main.cpp
src/game/game.cpp
src/game/display.cpp
src/game/map.cpp
src/game/texture_manager.cpp
src/game/game_object.cpp
src/entities/lassi.cpp
src/entities/watermelon.cpp
src/entities/tile.cpp
src/game/tile_keeper.cpp
src/components/collision.cpp
src/components/physics.cpp
src/components/vector2D.cpp
)


link_directories(
  ${SDL2_LIBRARY_DIRS}
  ${SDL2_IMAGE_LIBRARY_DIRS}
  )

add_executable(BetelLeafEater ${SOURCES})

target_include_directories(BetelLeafEater PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(BetelLeafEater PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(BetelLeafEater PRIVATE SDL2 SDL2_image)
