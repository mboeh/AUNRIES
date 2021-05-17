#pragma once

#include <map>
#include "sol/sol.hpp"
#include <SFML/Graphics.hpp>

class TiledSet {
    class Tile {
    public:
        int id;
        std::string type;

        explicit Tile(const sol::table &tbl);
    };
public:
    std::string name;
    int tilewidth, tileheight;
    int gridwidth, gridheight;
    std::string image;
    int imagewidth, imageheight;
    int tilecount;
    int columns;
    std::vector<Tile> tiles;

    explicit TiledSet(const sol::table &tbl);

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

    sf::Rect<int> rect(int dataIdx) const;
};

class TiledLoader {
    std::map<std::string, TiledSet> tilesets;
    std::map<std::string, TiledMap> tilemaps;

public:
    TiledSet& loadTileset(std::string name);
    TiledMap& loadTilemap(std::string name);
};