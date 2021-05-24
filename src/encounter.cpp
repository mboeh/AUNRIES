//
// Created by Matthew Boeh on 5/21/21.
//

#include "encounter.hpp"

void Encounter::deploy(const TiledMap::Layer &l) {
    std::cerr << "deploying  " << l.name << " with " << l.objects.size() << " objects" << std::endl;
    for(auto &obj : l.objects) {
        pieces.emplace_back(Piece {
            .id = obj.id,
            .name = obj.name,
            .x = (int)(obj.x) / 24, // FIXME
            .y = (int)(obj.y - 0.01) / 24, // GAHH FIXME
            .tileID = obj.tileID,
        });
    }
}

void Encounter::reset() {
    pieces.clear();
}