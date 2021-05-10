#include <map>

class AssetLoader
{
  std::shared_ptr<Game> game;
  std::map<string, Image> tilesets;
  std::map<string, std::map<string, Image>> tiles;

public:
  AssetLoader(std::shared_ptr<Game> game) : game{game} {}

  void preload()
  {
    for (const TilesetDef &def : game->tilesets.entries)
    {
      loadTileset(def);
    }
  }

  void loadTileset(const TilesetDef &def)
  {
    if (tilesets.find(def.name) != tilesets.end())
    {
      return;
    }
    tilesets[def.name] = LoadImage(def.path.c_str());
  }

  void loadTileset(const string tileset)
  {
    const TilesetDef &ts = game->tilesets.findByName(tileset);
    loadTileset(ts);
  }

  Image &loadTile(const string tileset, const string name)
  {
    const TilesetDef &tsd = game->tilesets.findByName(tileset);
    loadTileset(tsd);
    auto &ts = tiles[tileset];
    auto i = ts.find(name);
    if (i != ts.end())
    {
      return get<1>(*i);
    }
    ts[name] = ImageFromImage(tilesets[tileset], tsd.tileRect(name));
    return ts[name];
  }
};