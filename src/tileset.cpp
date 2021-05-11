#include "tileset.hpp"

Rectangle TilesetDef::tileRect(int x, int y) const {
    return Rectangle{
            static_cast<float>((x * grid_w) + off_w),
            static_cast<float>((y * grid_h) + off_h),
            static_cast<float>(grid_w),
            static_cast<float>(grid_h),
    };
}

Rectangle TilesetDef::tileRect(const string &ref) const {
    std::istringstream parse(ref);
    int x, y;
    parse >> x >> std::ws >> y;
    cerr << "parsed " << ref << " as " << x << "," << y << endl;
    return tileRect(x, y);
}
