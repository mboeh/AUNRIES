#pragma once

#include <map>
#include <utility>
#include "game.hpp"
#include <SFML/Graphics.hpp>

class AssetLoader {
    std::map<std::string, std::shared_ptr<sf::Texture>> images;

public:
    const std::shared_ptr<sf::Texture> loadImage(std::string rawpath);

    static std::string resolvePath(std::string rawpath);

    //AssetLoader(const AssetLoader&) = delete;
};