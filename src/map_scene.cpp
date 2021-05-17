#include "map_scene.hpp"

void MapScene::loadMap(std::string name) {
    loadedMap = name;
    tiled->loadTilemap(name);
    needsDraw = true;
}

bool MapScene::draw() {
    if (!screen) return false;

    return draw(*screen);
}

bool MapScene::draw(Image &img) {
    if (!loadedMap) return false;
    if (!needsDraw) return false;

    auto map = tiled->loadTilemap(loadedMap.value());
    for(auto i = map.layers.begin(); i < map.layers.end(); i++) {
        drawLayer(img, map, *i);
    }
    needsDraw = false;
    return true;
}

void MapScene::drawLayer(Image &img, TiledMap &map, TiledMap::Layer &l) {
    cerr << l.name << "(" << l.visible << ")" << endl;
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
                auto trect = ts.rect(tileId);
                auto drect = map.rect(idx);
                // Clip to screen boundary
                if (drect.x + drect.width > img.width) {
                    drect.width = img.width - drect.x;
                    if (drect.width <= 0) continue;
                }
                if (drect.y + drect.height > img.height) {
                    drect.height = img.height - drect.y;
                    if (drect.height <= 0) continue;
                }
                ImageDraw(&img, tsi, trect, drect, WHITE);
            } else {
                // TODO: need to handle flipped tiles
                // https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tile-flipping
                cerr << "bad tile? " << t << endl;
            }
        }
    }
}

void MapScene::makeImage(int width, int height) {
    screen = GenImageColor(width, height, BLACK);
}

void MapScene::onKeyPress(int code) {
    switch (code) {
        case 't':
            if(!loadedMap) return;
            cerr << "got T keypress" << endl;
            {
                auto map = tiled->loadTilemap(loadedMap.value());
                for (auto i = map.layers.begin(); i < map.layers.end(); i++) {
                    if (i->name == "$terrain") {
                        i->visible = !i->visible;
                        needsDraw = true;
                    }
                }
            }
            break;
        default:
            cerr << "Unhandled keypress: " << code << endl;
    }
}