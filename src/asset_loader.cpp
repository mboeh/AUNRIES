#include "asset_loader.hpp"

const sf::Texture& AssetLoader::loadImage(std::string rawpath) {
    auto path = resolvePath(std::move(rawpath));
    auto i = images.find(path);
    if (i != images.end()) {
        return i->second;
    }
    std::cerr << "loading asset from " << path << std::endl;
    images[path].loadFromFile(path);
    return images[path];
}

std::string AssetLoader::resolvePath(std::string rawpath) {
    std::size_t pos = rawpath.find("assets/");
    if (pos == std::string::npos) {
        return rawpath;
    } else {
        return rawpath.substr(pos);
    }
}