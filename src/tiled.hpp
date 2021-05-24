#pragma once

#include <map>
#include "sol/sol.hpp"
#include <SFML/Graphics.hpp>

class TiledSet {
public:
    struct Animation {
        struct Frame {
            int tileID, duration;
        };
        std::vector<Frame> frames;

        explicit Animation(const sol::table &tbl) {
            for(int i = 1; i <= tbl.size(); i++) {
                frames.emplace_back(Frame{
                   .tileID = tbl[i]["tileid"],
                   .duration = tbl[i]["duration"],
                });
            }
        }
    };

    class Tile {
    public:
        int id;
        std::string type;
        std::optional<Animation> animation;

        Tile(int id): id{id} {};
        explicit Tile(const sol::table &tbl);
    };

    std::string name;
    int tilewidth, tileheight;
    int gridwidth, gridheight;
    std::string image;
    int imagewidth, imageheight;
    int tilecount;
    int columns;
    std::vector<Tile> tiles;

    explicit TiledSet(const sol::table &tbl);

    Tile getTile(int tileID) const {
        for(auto &t : tiles) {
            if (t.id == tileID) {
                return t;
            }
        }
        return Tile(tileID);
    }
    sf::Rect<int> rect(int tileId) const;
};

class TiledMap {
public:

    class Tileset {
    public:
        std::string name;
        int firstgid;

        explicit Tileset(const sol::table &tbl);
    };

    class Object {
    public:
        int id;
        std::string name;
        std::string type;
        int tileID;
        double x, y;

        explicit Object(const sol::table &tbl);
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
        bool visible;
        float opacity;
        int width, height;
        std::vector<int> data;
        std::vector<Layer> layers;
        std::vector<Object> objects;

        explicit Layer(const sol::table &tbl);
    };

    int width, height, tilewidth, tileheight;
    std::vector<Tileset> tilesets;
    std::vector<Layer> layers;

    explicit TiledMap(const sol::table &tbl);
    TiledMap(const TiledMap&) = delete;


    inline sf::Rect<int> rect(int dataIdx) const {
        return sf::Rect{
                tileX(dataIdx) * tilewidth,
                tileY(dataIdx) * tileheight,
                tilewidth,
                tileheight
        };
    }

    inline sf::Rect<int> rect(int x, int y) {
        return sf::Rect{
                x * tilewidth,
                y * tileheight,
                tilewidth,
                tileheight
        };
    }

    inline int tileX(int dataIdx) const {
        return dataIdx % width;
    }

    inline int tileY(int dataIdx) const {
        return dataIdx / width;
    }

    const Layer* getLayer(const std::string& name);
};

class TiledLoader {
    std::map<std::string, TiledSet> tilesets;
    std::map<std::string, TiledMap> tilemaps;

public:
    TiledSet& loadTileset(std::string name);
    TiledMap& loadTilemap(std::string name);
};