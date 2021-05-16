#pragma once

#include <map>
#include <utility>
#include "game.hpp"

class AssetLoader {
    std::shared_ptr<Game> game;
    std::map<string, Image> images;
    std::map<string, std::map<string, Image>> tiles;

public:
    explicit AssetLoader(std::shared_ptr<Game> game) : game{std::move(game)} {}
};