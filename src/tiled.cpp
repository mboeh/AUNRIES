#include "tiled.hpp"

TiledSet& TiledLoader::loadTileset(std::string name) {
    if (tilesets.find(name) != tilesets.end()) {
        return tilesets.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    tilesets.try_emplace(name, t);

    return tilesets.at(name);
}

TiledMap& TiledLoader::loadTilemap(std::string name) {
    if (tilemaps.find(name) != tilemaps.end()) {
        return tilemaps.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    tilemaps.try_emplace(name, t);

    return tilemaps.at(name);
}