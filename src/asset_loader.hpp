#pragma once

#include <map>
#include <utility>
#include "tileset.hpp"
#include "game.hpp"

class AssetLoader {
    std::shared_ptr<Game> game;
    std::map<string, Image> tilesets;
    std::map<string, std::map<string, Image>> tiles;

public:
    explicit AssetLoader(std::shared_ptr<Game> game) : game{std::move(game)} {}

    void preload();

    void loadTileset(const TilesetDef &def);

    void loadTileset(const string& tileset);

    Image &loadTile(const string& tileset, const string& name);
};