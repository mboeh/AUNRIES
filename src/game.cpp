#include "game.hpp"

void Game::load_tilesets(sol::table &tbl) {
    tbl.for_each([&](const sol::object &key, const sol::object &value) {
        sol::table attrs = value.as<sol::table>();
        tilesets.add(TilesetDef(attrs));
    });
}
