#include "codex.hpp"
#include "map.hpp"
#include "tileset.hpp"
#include "roster.hpp"

class Game
{
public:
  Codex<Terrain> terrain;
  Codex<TilesetDef> tilesets;
  Roster roster;

  void load_tilesets(sol::table &tbl)
  {
    tbl.for_each([&](sol::object key, sol::object value) {
      sol::table attrs = value.as<sol::table>();
      tilesets.add(TilesetDef(attrs));
    });
  }
};