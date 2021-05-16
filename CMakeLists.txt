cmake_minimum_required(VERSION 3.13)
project(AUNRIES)
set(CMAKE_CXX_STANDARD 20)
include_directories(./src)
include_directories(./vendor)
include_directories(/usr/local/Cellar/raylib/3.0.0/include)
include_directories(/usr/local/include/lua)
link_directories(/usr/local/lib)
link_directories(/usr/local/Cellar/raylib/3.0.0/lib)
add_executable(game src/game.cpp src/main.cpp src/asset_loader.cpp src/roster.cpp src/map_loader.cpp src/map_loader.hpp)
target_link_libraries(game raylib)
target_link_libraries(game lua)

add_custom_target(buildMaps DEPENDS maps/basic_map.lua maps/colors.lua maps/oryx_fan.lua)
add_custom_command(
        OUTPUT maps/basic_map.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-map lua maps/basic_map.tmx ${CMAKE_CURRENT_SOURCE_DIR}/maps/basic_map.lua
        DEPENDS maps/basic_map.tmx
        VERBATIM
)
add_custom_command(
        OUTPUT maps/colors.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua maps/colors.tsx ${CMAKE_CURRENT_SOURCE_DIR}/maps/colors.lua
        DEPENDS maps/colors.tsx
        VERBATIM
)
add_custom_command(
        OUTPUT maps/oryx_fan.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua maps/oryx_fan.tsx ${CMAKE_CURRENT_SOURCE_DIR}/maps/oryx_fan.lua
        DEPENDS maps/oryx_fan.tsx
        VERBATIM
)
add_dependencies(game buildMaps)