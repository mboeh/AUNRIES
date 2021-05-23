#pragma once

#include "tiled.hpp"

class Encounter {
public:
    struct Piece {
        int id;
        std::string name;
        int x, y;
        int tileID;
    };

    std::vector<Piece> pieces;
    void deploy(const TiledMap::Layer& l);
    void reset();
};