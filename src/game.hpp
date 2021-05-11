#pragma once

#include "codex.hpp"
#include "map.hpp"
#include "tileset.hpp"
#include "roster.hpp"

class Game {
public:
    Codex<Terrain> terrain;
    Codex<TilesetDef> tilesets;
    Roster roster;

    void load_tilesets(sol::table &tbl);
};