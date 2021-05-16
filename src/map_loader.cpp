#include "map_loader.hpp"

TiledSet& MapLoader::loadTileset(std::string name) {
    if (loadedTilesets.find(name) != loadedTilesets.end()) {
        return loadedTilesets.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    loadedTilesets.try_emplace(name,t);

    return loadedTilesets.at(name);
}

TiledMap& MapLoader::loadTilemap(std::string name) {
    if (loadedTilemaps.find(name) != loadedTilemaps.end()) {
        return loadedTilemaps.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    loadedTilemaps.try_emplace(name,t);

    return loadedTilemaps.at(name);
}