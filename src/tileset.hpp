#pragma once

#include "sol/sol.hpp"
#include <sstream>
#include <string>
#include <raylib.h>

using namespace std;

class TilesetDef {
public:
    const string name;
    const string path;
    const int grid_w, grid_h;
    const int off_w, off_h;

    explicit TilesetDef(const sol::table &tbl) : name{tbl["name"]}, path{tbl["path"]}, grid_w{tbl["grid"][1]},
                                                 grid_h{tbl["grid"][2]}, off_w{tbl["offset"][1]},
                                                 off_h{tbl["offset"][2]} {}

    [[nodiscard]] Rectangle tileRect(int x, int y) const;

    [[nodiscard]] Rectangle tileRect(const string &ref) const;
};
