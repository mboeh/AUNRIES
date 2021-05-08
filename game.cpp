#include <raylib.h>
#include "roster.hpp"
#include "sol/sol.hpp"

int main()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string);
  lua.script_file("init.lua");
  sol::table config = lua["CONFIG"];

  InitWindow(300, 300, config.get<string>("title").c_str());

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
