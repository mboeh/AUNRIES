#include "asset_loader.hpp"

const std::shared_ptr<sf::Texture> AssetLoader::loadImage(std::string rawpath) {
    auto path = resolvePath(std::move(rawpath));

    if (!images[path]) {
        std::cerr << "loading asset from " << path << std::endl;
        auto tex = make_shared<sf::Texture>();
        tex->loadFromFile(path);
        images[path] = std::move(tex);
    }

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