#pragma once

#include "asset_loader.hpp"
#include "tiled.hpp"
#include "scenario.hpp"
#include "encounter.hpp"
#include <SFML/Graphics.hpp>

class MapScene {
    std::shared_ptr<Game> game;
    std::shared_ptr<AssetLoader> assets;
    std::shared_ptr<TiledLoader> tiled;
    std::optional<string> loadedMap;
    sf::RenderTexture screen;
    Encounter encounter;
    std::map<int, sf::Clock> animClocks;
    bool needsDraw;

public:
    MapScene(std::shared_ptr<Game> game, std::shared_ptr<AssetLoader> assets, std::shared_ptr<TiledLoader> tiled): game{std::move(game)}, assets{std::move(assets)}, tiled{std::move(tiled)}, needsDraw{false}{}

    void loadEncounter(const Scenario::Encounter& e);
    void makeImage(int width, int height);

    bool draw();

    const sf::RenderTexture& getScreen() const {
        return screen;
    }

    void toggleDebugTerrain();
    void onKeyPress(const sf::Event &event);

private:
    bool draw(sf::RenderTexture& img);
    void drawLayer(sf::RenderTexture& img, TiledMap& map, TiledMap::Layer& l);
    void drawEncounter(sf::RenderTexture &img, TiledMap &map, const Encounter& encounter);
    inline void drawTile(sf::RenderTexture &img, TiledMap &map, int tileID, int x, int y);
};