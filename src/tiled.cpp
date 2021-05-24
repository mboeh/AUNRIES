#include "tiled.hpp"
#include <iostream>

TiledSet& TiledLoader::loadTileset(std::string name) {
    if (tilesets.find(name) != tilesets.end()) {
        return tilesets.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    tilesets.try_emplace(name, t);

    return tilesets.at(name);
}

TiledMap& TiledLoader::loadTilemap(std::string name) {
    if (tilemaps.find(name) != tilemaps.end()) {
        return tilemaps.at(name);
    }

    sol::state lua;
    sol::table t = lua.safe_script_file("maps/" + name + ".lua");

    tilemaps.try_emplace(name, t);

    return tilemaps.at(name);
}


TiledMap::TiledMap(const sol::table &tbl) {
    width = tbl["width"];
    height = tbl["height"];
    tilewidth = tbl["tilewidth"];
    tileheight = tbl["tileheight"];

    sol::table tsa = tbl["tilesets"];
    for (int i = 1; i <= tsa.size(); i++) {
        sol::table ts = tsa[i];
        tilesets.emplace_back(Tileset(ts));
    }

    sol::table lra = tbl["layers"];
    for (int i = 1; i <= lra.size(); i++) {
        sol::table lr = lra[i];
        layers.emplace_back(Layer(lr));
    }
}

const TiledMap::Layer* TiledMap::getLayer(const std::string& name) {
    for (auto i = layers.begin(); i < layers.end(); i++) {
        if (i->name == name) {
            return &*i;
        }
    }
    return nullptr;
}


TiledMap::Layer::Layer(const sol::table &tbl) {
    id = tbl["id"];
    name = tbl["name"];
    visible = tbl["visible"];
    opacity = tbl["opacity"];
    width = tbl.get_or("width", 0);
    height = tbl.get_or("height", 0);
    std::string t = tbl["type"];
    if (t == "tilelayer") {
        type = LayerType::TILELAYER;
        sol::table d = tbl["data"];
        if (d.size() > 0) {
            std::cerr << "loading data: " << d.size() << std::endl;
            for(int i = 1; i <= d.size(); i++) {
                data.push_back(d[i]);
            }
            std::cerr << "loaded into " << &data << " size: " << data.size() << "example: " << data[125] << std::endl;
        }
    } else if (t == "objectgroup") {
        type = LayerType::OBJECTLAYER;
        sol::table oba = tbl["objects"];
        for (int i = 1; i <= oba.size(); i++) {
            sol::table ob = oba[i];
            objects.emplace_back(Object(ob));
        }
    } else if (t == "group") {
        type = LayerType::GROUP;
        sol::table lra = tbl["layers"];
        for (int i = 1; i <= lra.size(); i++) {
            sol::table lr = lra[i];
            layers.emplace_back(Layer(lr));
        }
    } else {
        type = LayerType::UNKNOWN;
    }
}

TiledMap::Object::Object(const sol::table &tbl) {
    id = tbl["id"];
    name = tbl["name"];
    type = tbl["type"];
    x = tbl["x"];
    y = tbl["y"];
    tileID = tbl.get_or("gid", -1);
}

TiledMap::Tileset::Tileset(const sol::table &tbl) {
    name = tbl["name"];
    firstgid = tbl["firstgid"];
}

sf::Rect<int> TiledSet::rect(int tileId) const {
    return sf::Rect{
            (tileId%columns)*tilewidth,
            (tileId/columns)*tileheight,
            tilewidth,
            tileheight
    };
}

TiledSet::TiledSet(const sol::table &tbl) {
    name = tbl["name"];
    tilewidth = tbl["tilewidth"];
    tileheight = tbl["tileheight"];
    gridwidth = tbl["grid"]["width"];
    gridheight = tbl["grid"]["height"];
    image = tbl["image"];
    imagewidth = tbl["imagewidth"];
    imageheight = tbl["imageheight"];
    tilecount = tbl["tilecount"];
    columns = tbl["columns"];

    sol::table tls = tbl["tiles"];
    if (tls.size() > 0) {
        tiles.reserve(tls.size());
        for(int i = 1; i <= tls.size(); i++) {
            tiles.emplace_back(static_cast<sol::table>(tls[i]));
        }
    }
}

TiledSet::Tile::Tile(const sol::table &tbl) {
    id = tbl["id"];
    type = tbl.get_or<std::string>("type", "unknown");
    auto anim = tbl.get<sol::optional<sol::table>>("animation");
    if (anim.has_value()) {
        animation = Animation(anim.value());
    }
}