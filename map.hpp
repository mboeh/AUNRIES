#include <string>

using namespace std;

template <typename T>
class Codex
{
  static inline int lastID = 0;
  vector<T> entries;

public:
  class ID
  {
    friend Codex;

    const int id;

    ID(int id) : id{id} {}
  };
  ID add(T item)
  {
    entries.push_back(item);
    return mint();
  }
  static const ID mint()
  {
    return ID(++lastID);
  }
  static const ID none()
  {
    return ID(0);
  }
};

class Terrain
{
public:
  string name;
  bool passable;

  Terrain(string name, bool passable) : name{name}, passable{passable} {}
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