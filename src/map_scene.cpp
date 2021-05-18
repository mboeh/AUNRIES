#include "map_scene.hpp"

void MapScene::loadEncounter(const Scenario::Encounter &e) {
    loadedMap = e.map;
    tiled->loadTilemap(e.map);
    needsDraw = true;
}

bool MapScene::draw() {
    return draw(screen);
}

bool MapScene::draw(sf::RenderTexture &img) {
    if (!loadedMap) return false;
    if (!needsDraw) return false;

    sf::Clock drawStart;
    auto &map = tiled->loadTilemap(loadedMap.value());
    for(auto i = map.layers.begin(); i < map.layers.end(); i++) {
        drawLayer(img, map, *i);
    }
    needsDraw = false;
    cerr << "redrew map in " << drawStart.getElapsedTime().asSeconds() << "s" << endl;
    return true;
}

void MapScene::drawLayer(sf::RenderTexture &img, TiledMap &map, TiledMap::Layer &l) {
    if (!l.visible) return;
    sf::Clock drawStart;
    int draws = 0;
    if (l.type == TiledMap::LayerType::GROUP) {
        for (auto i = l.layers.begin(); i < l.layers.end(); i++) {
            drawLayer(img, map, *i);
        }
    } else if (l.type == TiledMap::LayerType::TILELAYER) {
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
                if (drect.left + drect.width > img.getSize().x) {
                    drect.width = img.getSize().x - drect.left;
                    if (drect.width <= 0) continue;
                }
                if (drect.top + drect.height > img.getSize().y) {
                    drect.height = img.getSize().y - drect.top;
                    if (drect.height <= 0) continue;
                }
                sf::Sprite tSp(*tsi, trect);
                tSp.setPosition(drect.left, drect.top);
                draws++;
                img.draw(tSp);
            } else {
                // TODO: need to handle flipped tiles
                // https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tile-flipping
                //cerr << "bad tile? " << t << endl;
            }
        }
    }
    cerr << "drew " << l.name << " (" << draws << " sprites) in " << drawStart.getElapsedTime().asSeconds() << "s" << endl;
}

void MapScene::makeImage(int width, int height) {
    screen.create(width, height);
}

void MapScene::onKeyPress(const sf::Event& event) {
    switch (event.key.code) {
        case sf::Keyboard::T:
            toggleDebugTerrain();
            break;
        default:
            cerr << "Unhandled keypress: " << event.key.code << endl;
    }
}

void MapScene::toggleDebugTerrain() {
    if(!loadedMap) return;

    auto &map = tiled->loadTilemap(loadedMap.value());
    for (auto i = map.layers.begin(); i < map.layers.end(); i++) {
        if (i->name == "$terrain") {
            i->visible = !i->visible;
            needsDraw = true;
        }
    }
}