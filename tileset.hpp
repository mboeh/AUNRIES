#include "sol/sol.hpp"

class TilesetDef
{
public:
  const string name;
  const string path;
  const int grid_w, grid_h;
  const int off_w, off_h;

  TilesetDef(const sol::table &tbl) : name{tbl["name"]}, path{tbl["path"]}, grid_w{tbl["grid"][1]}, grid_h{tbl["grid"][2]}, off_w{tbl["offset"][1]}, off_h{tbl["offset"][2]} {}

  Rectangle tileRect(int x, int y) const
  {
    return Rectangle{
        static_cast<float>((x * grid_w) + off_w),
        static_cast<float>((y * grid_h) + off_h),
        static_cast<float>(grid_w),
        static_cast<float>(grid_h),
    };
  }
};
