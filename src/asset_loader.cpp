#include "asset_loader.hpp"

void AssetLoader::preload() {
    for (const TilesetDef &def : game->tilesets.entries) {
        loadTileset(def);
    }
}

void AssetLoader::loadTileset(const TilesetDef &def) {
    if (tilesets.find(def.name) != tilesets.end()) {
        return;
    }
    tilesets[def.name] = LoadImage(def.path.c_str());
}

void AssetLoader::loadTileset(const string& tileset) {
    const TilesetDef &ts = game->tilesets.find(tileset);
    loadTileset(ts);
}

Image &AssetLoader::loadTile(const string& tileset, const string& name) {
    const TilesetDef &tsd = game->tilesets.find(tileset);
    loadTileset(tsd);
    auto &ts = tiles[tileset];
    auto i = ts.find(name);
    if (i != ts.end()) {
        return get<1>(*i);
    }
    ts[name] = ImageFromImage(tilesets[tileset], tsd.tileRect(name));
    return ts[name];
}
