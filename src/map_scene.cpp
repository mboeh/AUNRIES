#include "map_scene.hpp"

void MapScene::loadEncounter(const Scenario::Encounter &e) {
    loadedMap = e.map;
    auto &map = tiled->loadTilemap(e.map);
    auto layer = map.getLayer(e.deploy);
    assert(layer);
    encounter.reset();
    encounter.deploy(*layer);
    needsDraw = true;
}

bool MapScene::draw() {
    return draw(screen);
}

bool MapScene::draw(sf::RenderTexture &img) {
    if (!loadedMap) return false;
    // FIXME need to translate to a FPS approach based on
    // animClock
    //if (!needsDraw) return false;

    sf::Clock drawStart;
    auto &map = tiled->loadTilemap(loadedMap.value());
    for(auto i = map.layers.begin(); i < map.layers.end(); i++) {
        drawLayer(img, map, *i);
    }
    drawEncounter(img, map, encounter);
    needsDraw = false;
    //cerr << "redrew map in " << drawStart.getElapsedTime().asSeconds() << "s" << endl;
    return true;
}

void MapScene::drawLayer(sf::RenderTexture &img, TiledMap &map, TiledMap::Layer &l) {
    if (!l.visible) return;
    if (l.type == TiledMap::LayerType::GROUP) {
        for (auto i = l.layers.begin(); i < l.layers.end(); i++) {
            drawLayer(img, map, *i);
        }
    } else if (l.type == TiledMap::LayerType::TILELAYER) {
        for(int idx = 0; idx < l.data.size(); idx++) {
            int t = l.data[idx];
            if (!t) continue;
            drawTile(img, map, t, map.tileX(idx), map.tileY(idx));
        }
    }
}


void MapScene::drawEncounter(sf::RenderTexture &img, TiledMap &map, const Encounter& encounter) {
    for(auto &piece: encounter.pieces) {
        drawTile(img, map, piece.tileID, piece.x, piece.y);
    }
}

inline void MapScene::drawTile(sf::RenderTexture &img, TiledMap &map, int tileID, int x, int y) {
    auto it = std::find_if(map.tilesets.begin(), map.tilesets.end(), [&](auto &ts) {
        auto tsx = tiled->loadTileset(ts.name);
        return ts.firstgid <= tileID && ts.firstgid + tsx.tilecount > tileID;
    });
    if (it != map.tilesets.end()) {
        auto ts = tiled->loadTileset(it->name);
        auto tsi = assets->loadImage(ts.image);
        tileID -= it->firstgid;
        auto tile = ts.getTile(tileID);
        if (tile.animation.has_value()) {
            // this is dog shit FIXME
            auto& anim = tile.animation.value();
            auto& clock = animClocks[tileID];
            int f = int(clock.getElapsedTime().asMilliseconds()) % (anim.frames[0].duration * anim.frames.size());
            f /= anim.frames[0].duration;
            tileID = tile.animation.value().frames[f].tileID;
        }
        auto trect = ts.rect(tileID);
        auto drect = map.rect(x, y);
        // Clip to screen boundary
        if (drect.left + drect.width > img.getSize().x) {
            drect.width = img.getSize().x - drect.left;
            if (drect.width <= 0) return;
        }
        if (drect.top + drect.height > img.getSize().y) {
            drect.height = img.getSize().y - drect.top;
            if (drect.height <= 0) return;
        }
        sf::Sprite tSp(*tsi, trect);
        tSp.setPosition(drect.left, drect.top);
        img.draw(tSp);
    } else {
        // TODO: need to handle flipped tiles
        // https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#tile-flipping
        //cerr << "bad tile? " << t << endl;
    }
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