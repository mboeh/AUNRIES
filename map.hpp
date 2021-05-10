#include <string>

using namespace std;

class Terrain
{
public:
  string name;
  bool passable;
  string tile;

  Terrain(string name, bool passable, string tile) : name{name}, passable{passable}, tile{tile} {}
};

class Tile
{
  Codex<Terrain>::ID terrain;

public:
  Tile() : terrain{Codex<Terrain>::none()} {}
};

class Map
{
public:
  const string name;
  const int width;
  const int height;
  vector<Tile> tiles;

  Map(string name, int width, int height) : name{name}, width{width}, height{height}
  {
    tiles.resize(width * height, Tile());
  }

  const Tile &get(int x, int y)
  {
    return tiles[x * y];
  }
};