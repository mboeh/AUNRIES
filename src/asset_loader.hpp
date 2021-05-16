#pragma once

#include <map>
#include <utility>
#include <raylib.h>
#include "game.hpp"

class AssetLoader {
    std::shared_ptr<Game> game;
    std::map<std::string, Image> images;

public:
    explicit AssetLoader(std::shared_ptr<Game> game) : game{std::move(game)} {}

    Image loadImage(std::string rawpath) {
        auto path = resolvePath(std::move(rawpath));
        auto i = images.find(path);
        if (i != images.end()) {
            return i->second;
        }
        std::cerr << "loading asset from " << path << std::endl;
        images[path] = LoadImage(path.c_str());
        return images[path];
    }

    static std::string resolvePath(std::string rawpath) {
        std::size_t pos = rawpath.find("assets/");
        if (pos == std::string::npos) {
            return rawpath;
        } else {
            return rawpath.substr(pos);
        }
    }
};