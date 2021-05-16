#pragma once

#include <map>
#include "sol/sol.hpp"

class TiledSet {
    class Tile {
    public:
        int id;
        std::string type;

        explicit Tile(const sol::table &tbl) {
            id = tbl["id"];
            type = tbl["type"];
        }
    };
public:
    std::string name;
    int tilewidth, tileheight;
    int gridwidth, gridheight;
    std::string image;
    int imagewidth, imageheight;
    int tilecount;
    std::vector<Tile> tiles;

    explicit TiledSet(const sol::table &tbl) {
        name = tbl["name"];
        tilewidth = tbl["tilewidth"];
        tileheight = tbl["tileheight"];
        gridwidth = tbl["grid"]["width"];
        gridheight = tbl["grid"]["height"];
        image = tbl["image"];
        imagewidth = tbl["imagewidth"];
        imageheight = tbl["imageheight"];
        tilecount = tbl["tilecount"];

        sol::table tls = tbl["tiles"];
        if (tls.size() > 0) {
            tiles.reserve(tls.size());
            for(int i = 1; i <= tls.size(); i++) {
                tiles.emplace_back(static_cast<sol::table>(tls[i]));
            }
        }
    }
};

class TiledMap {
    class Tileset {
    public:
        std::string name;
        int firstgid;

        explicit Tileset(const sol::table &tbl) {
            name = tbl["name"];
            firstgid = tbl["firstgid"];
        }
    };

    class Object {
    public:
        int id;
        std::string name;
        std::string type;
        double x, y;

        explicit Object(const sol::table &tbl) {
            id = tbl["id"];
            name = tbl["name"];
            type = tbl["type"];
            x = tbl["x"];
            y = tbl["y"];
        }
    };

    enum class LayerType {
        TILELAYER,
        OBJECTLAYER,
        GROUP,
        UNKNOWN,
    };

    class Layer {
    public:
        int id;
        std::string name;
        LayerType type;
        int width, height;
        std::vector<int> data;
        std::vector<Layer> layers;
        std::vector<Object> objects;

        explicit Layer(const sol::table &tbl) {
            id = tbl["id"];
            name = tbl["name"];
            width = tbl.get_or("width", 0);
            height = tbl.get_or("height", 0);
            std::string t = tbl["type"];
            if (t == "tilelayer") {
                type = LayerType::TILELAYER;
                sol::table d = tbl["data"];
                if (d.size() > 0) {
                    data.reserve(d.size());
                    for(int i = 1; i <= d.size(); i++) {
                        data[i-1] = d[i];
                    }
                }
            } else if (t == "objectlayer") {
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
    };

public:
    int width, height, tilewidth, tileheight;
    std::vector<Tileset> tilesets;
    std::vector<Layer> layers;

    explicit TiledMap(const sol::table &tbl) {
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
};

class MapLoader {
    std::map<std::string, TiledSet> loadedTilesets;
    std::map<std::string, TiledMap> loadedTilemaps;

public:
    TiledSet& loadTileset(std::string name);
    TiledMap& loadTilemap(std::string name);
};