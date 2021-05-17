#pragma once

#include <raylib.h>
#include "asset_loader.hpp"
#include "tiled.hpp"

class MapScene {
    std::shared_ptr<Game> game;
    std::shared_ptr<AssetLoader> assets;
    std::shared_ptr<TiledLoader> tiled;
    std::optional<string> loadedMap;
    std::optional<Image> screen;
    bool needsDraw;

public:
    MapScene(std::shared_ptr<Game> game, std::shared_ptr<AssetLoader> assets, std::shared_ptr<TiledLoader> tiled): game{std::move(game)}, assets{std::move(assets)}, tiled{std::move(tiled)}{}

    void loadMap(std::string name);
    bool draw();
    bool draw(Image& img);
    void drawLayer(Image& img, TiledMap& map, TiledMap::Layer& l);
    void makeImage(int width, int height);

    std::optional<Image> getScreen() const {
        return screen;
    }

    void onKeyPress(int code);
};