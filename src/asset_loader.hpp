#pragma once

#include <map>
#include <utility>
#include <raylib.h>
#include "game.hpp"

class AssetLoader {
    std::map<std::string, Image> images;

public:
    Image loadImage(std::string rawpath);

    static std::string resolvePath(std::string rawpath);
};