cmake_minimum_required(VERSION 3.13)
project(AUNRIES)
set(CMAKE_CXX_STANDARD 20)
include_directories(./src)
include_directories(./vendor)
include_directories(/usr/local/include/lua)
link_directories(/usr/local/lib)
add_executable(game src/game.cpp src/main.cpp src/asset_loader.cpp src/roster.cpp src/tiled.cpp src/tiled.hpp src/map_scene.cpp src/map_scene.hpp src/scenario.cpp src/scenario.hpp src/encounter.cpp src/encounter.hpp)
target_link_libraries(game PRIVATE lua)
find_package(ImGui-SFML REQUIRED)
target_link_libraries(game PRIVATE ImGui-SFML::ImGui-SFML)

add_custom_target(buildMaps DEPENDS maps/basic_map.lua maps/colors.lua maps/oryx_fan.lua maps/oryx_fan_creatures.lua)
add_custom_command(
        OUTPUT maps/basic_map.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-map lua ${CMAKE_CURRENT_SOURCE_DIR}/maps/basic_map.tmx ${CMAKE_CURRENT_SOURCE_DIR}/maps/basic_map.lua
        DEPENDS maps/basic_map.tmx
        VERBATIM
)
add_custom_command(
        OUTPUT maps/colors.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua ${CMAKE_CURRENT_SOURCE_DIR}/maps/colors.tsx ${CMAKE_CURRENT_SOURCE_DIR}/maps/colors.lua
        DEPENDS maps/colors.tsx
        VERBATIM
)
add_custom_command(
        OUTPUT maps/oryx_fan.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua ${CMAKE_CURRENT_SOURCE_DIR}/maps/oryx_fan.tsx ${CMAKE_CURRENT_SOURCE_DIR}/maps/oryx_fan.lua
        DEPENDS maps/oryx_fan.tsx
        VERBATIM
)
add_custom_command(
        OUTPUT maps/oryx_fan_creatures.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua ${CMAKE_CURRENT_SOURCE_DIR}/maps/oryx_fan_creatures.tsx ${CMAKE_CURRENT_SOURCE_DIR}/maps/oryx_fan_creatures.lua
        DEPENDS maps/oryx_fan_creatures.tsx
        VERBATIM
)
add_dependencies(game buildMaps)