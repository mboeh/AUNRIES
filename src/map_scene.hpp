#pragma once

#include "asset_loader.hpp"
#include "tiled.hpp"
#include <SFML/Graphics.hpp>

class MapScene {
    std::shared_ptr<Game> game;
    std::shared_ptr<AssetLoader> assets;
    std::shared_ptr<TiledLoader> tiled;
    std::optional<string> loadedMap;
    sf::RenderTexture screen;
    bool needsDraw;

public:
    MapScene(std::shared_ptr<Game> game, std::shared_ptr<AssetLoader> assets, std::shared_ptr<TiledLoader> tiled): game{std::move(game)}, assets{std::move(assets)}, tiled{std::move(tiled)}{}

    void loadMap(std::string name);
    bool draw();
    bool draw(sf::RenderTexture& img);
    void drawLayer(sf::RenderTexture& img, TiledMap& map, TiledMap::Layer& l);
    void makeImage(int width, int height);

    const sf::RenderTexture& getScreen() const {
        return screen;
    }

    void onKeyPress(int code);
};