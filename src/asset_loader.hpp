#pragma once

#include <map>
#include <utility>
#include "game.hpp"
#include <SFML/Graphics.hpp>

class AssetLoader {
    std::map<std::string, sf::Texture> images;

public:
    const sf::Texture& loadImage(std::string rawpath);

    static std::string resolvePath(std::string rawpath);
};