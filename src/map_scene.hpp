#pragma once

#include <raylib.h>
#include "asset_loader.hpp"
#include "tiled.hpp"

class MapScene {
    std::shared_ptr<AssetLoader> assets;
    std::shared_ptr<TiledLoader> tiled;
    std::optional<string> loadedMap;
    std::optional<Image> screen;
    bool needsDraw;

public:
    MapScene(std::shared_ptr<AssetLoader> assets, std::shared_ptr<TiledLoader> tiled): assets{std::move(assets)}, tiled{std::move(tiled)}{}

    void loadMap(std::string name) {
        loadedMap = name;
        tiled->loadTilemap(name);
        needsDraw = true;
    }

    bool draw() {
        if (!screen) return false;

        draw(*screen);
    }

    std::optional<Image> getScreen() {
        return screen;
    }

    bool draw(Image& img) {
        if (!loadedMap) return false;
        if (!needsDraw) return false;

        auto map = tiled->loadTilemap(loadedMap.value());
        for(auto i = map.layers.begin(); i < map.layers.end(); i++) {
            drawLayer(img, map, *i);
        }
        needsDraw = false;
        return true;
    }

    void drawLayer(Image& img, TiledMap& map, TiledMap::Layer& l) {
        cerr << l.name << endl;
        if (!l.visible) return;
        if (l.type == TiledMap::LayerType::GROUP) {
            for (auto i = l.layers.begin(); i < l.layers.end(); i++) {
                drawLayer(img, map, *i);
            }
        } else if (l.type == TiledMap::LayerType::TILELAYER) {
            cerr << "drawing tiles from:" << &l.data << " size: " << l.data.size() << endl;
            for(int idx = 0; idx < l.data.size(); idx++) {
                int t = l.data[idx];
                if (!t) continue;
                auto it = std::find_if(map.tilesets.begin(), map.tilesets.end(), [&](auto &ts) {
                    auto tsx = tiled->loadTileset(ts.name);
                    return ts.firstgid <= t && ts.firstgid + tsx.tilecount > t;
                });
                if (it != map.tilesets.end()) {
                    auto ts = tiled->loadTileset(it->name);
                    auto tsi = assets->loadImage(ts.image);
                    int tileId = t - it->firstgid;
                    auto trect = Rectangle{
                            (float)((tileId%ts.columns)*ts.tilewidth),
                            (float)((tileId/ts.columns)*ts.tileheight),
                            (float)ts.tilewidth,
                            (float)ts.tileheight
                    };
                    auto drect = Rectangle{
                            (float)((idx % map.width)*map.tilewidth),
                            (float)((idx/map.width)*map.tileheight),
                            (float)ts.tilewidth,
                            (float)ts.tileheight
                    };
                    // Clip to screen boundary
                    if (drect.x + drect.width > img.width) {
                        drect.width = img.width - drect.x;
                        if (drect.width <= 0) continue;
                    }
                    if (drect.y + drect.height > img.height) {
                        drect.height = img.height - drect.y;
                        if (drect.height <= 0) continue;
                    }
                    //cerr << "drawing " << ts.name << "(" << tileId << ", " << tsi.width << "x" << tsi.height << ") " << trect.x << "," << trect.y << "@" << trect.width << "x" << trect.height << " -> " << drect.x << "," << drect.y << "@" << drect.width << "x" << drect.height << endl;
                    ImageDraw(&img, tsi, trect, drect, WHITE);
                } else {
                    // TODO: need to handle flipped tiles
                    // https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tile-flipping
                    cerr << "bad tile? " << t << " or is it " << ~t << endl;
                }
            }
        }
    }

    void makeImage(int width, int height) {
        screen = GenImageColor(width, height, BLACK);
    }
};