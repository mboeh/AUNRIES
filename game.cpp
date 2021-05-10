#include <raylib.h>
#include <iostream>
#include <fstream>
#include "roster.hpp"
#include "map.hpp"
#define SOL_ALL_SAFETIES_ON
#include "sol/sol.hpp"

template <typename T>
T fennel_eval(sol::state &lua, string filename)
{
  sol::table fnl = lua["fennel"];
  sol::function fnl_eval = fnl["eval"];
  ifstream f("config.fnl");
  stringstream buf;
  buf << f.rdbuf();
  T result = fnl_eval(buf.str());

  return result;
}

void fennel_load(sol::state &lua, string filename)
{
  fennel_eval<sol::object>(lua, filename);
}

int main()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::package, sol::lib::table, sol::lib::math);

  cerr << "loading fennel" << endl;
  lua.require_file("fennel", "fennel.lua");
  cerr << "loading lume" << endl;
  lua.require_file("lume", "lume.lua");
  cout << "loading init.lua" << endl;
  lua.safe_script_file("init.lua");

  sol::table config = fennel_eval<sol::table>(lua, "config.fnl");

  auto roster = new Roster();
  auto terrains = new Codex<Terrain>();

  sol::usertype<Roster> roster_type = lua.new_usertype<Roster>("Roster");
  roster_type["add"] = &Roster::add;
  roster_type["get"] = &Roster::get;
  lua["roster"] = roster;

  sol::usertype<Fighter> fighter_type = lua.new_usertype<Fighter>("Fighter");
  fighter_type["name"] = &Fighter::name;

  sol::usertype<Terrain> terrain_type = lua.new_usertype<Terrain>("Terrain", sol::constructors<Terrain(string, bool)>());
  terrain_type["name"] = &Terrain::name;
  terrain_type["passable"] = &Terrain::passable;

  sol::usertype<Codex<Terrain>> terrain_codex_type = lua.new_usertype<Codex<Terrain>>("TerrainCodex");
  terrain_codex_type["add"] = &Codex<Terrain>::add;
  lua["terrains"] = terrains;

  fennel_load(lua, "roster.fnl");
  fennel_load(lua, "maps.fnl");

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
