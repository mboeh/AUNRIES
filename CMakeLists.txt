cmake_minimum_required(VERSION 3.13)
project(AUNRIES)
set(CMAKE_CXX_STANDARD 20)
include_directories(./src)
include_directories(./vendor)
include_directories(/usr/local/Cellar/raylib/3.0.0/include)
include_directories(/usr/local/include/lua)
link_directories(/usr/local/lib)
link_directories(/usr/local/Cellar/raylib/3.0.0/lib)
add_executable(game src/game.cpp src/tileset.cpp src/main.cpp src/asset_loader.cpp src/roster.cpp)
target_link_libraries(game raylib)
target_link_libraries(game lua)

add_custom_target(buildMaps DEPENDS script/basic_map.lua assets/colors.lua assets/oryx_fan.lua)
add_custom_command(
        OUTPUT script/basic_map.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-map lua ${CMAKE_CURRENT_SOURCE_DIR}/basic_map.tmx ${CMAKE_CURRENT_SOURCE_DIR}/script/basic_map.lua
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/basic_map.tmx
        VERBATIM
)
add_custom_command(
        OUTPUT assets/colors.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua ${CMAKE_CURRENT_SOURCE_DIR}/colors.tsx ${CMAKE_CURRENT_SOURCE_DIR}/assets/colors.lua
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/colors.tsx
        VERBATIM
)
add_custom_command(
        OUTPUT assets/oryx_fan.lua
        COMMAND /Applications/Tiled.app/Contents/MacOS/Tiled --export-tileset lua ${CMAKE_CURRENT_SOURCE_DIR}/oryx_fan.tsx ${CMAKE_CURRENT_SOURCE_DIR}/assets/oryx_fan.lua
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/oryx_fan.tsx
        VERBATIM
)
add_dependencies(game buildMaps)