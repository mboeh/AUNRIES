#pragma once

#include <string>
#include <utility>

using namespace std;

class Terrain {
public:
    string name;
    bool passable;
    string tile;

    Terrain(string name, bool passable, string tile) : name{std::move(name)}, passable{passable},
                                                       tile{std::move(tile)} {}
};

class Tile {

};

class Map {
public:
    const string name;
    const int width;
    const int height;
    vector<Tile> tiles;

    Map(string name, int width, int height) : name{std::move(name)}, width{width}, height{height} {
        tiles.resize(width * height, Tile());
    }

    const Tile &get(int x, int y) {
        return tiles[x * y];
    }
};