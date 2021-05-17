#include "asset_loader.hpp"

Image AssetLoader::loadImage(std::string rawpath) {
    auto path = resolvePath(std::move(rawpath));
    auto i = images.find(path);
    if (i != images.end()) {
        return i->second;
    }
    std::cerr << "loading asset from " << path << std::endl;
    images[path] = LoadImage(path.c_str());
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