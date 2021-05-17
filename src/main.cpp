#include <raylib.h>

#include "game.hpp"
#include "asset_loader.hpp"
#include "tiled.hpp"
#include "map_scene.hpp"

int main() {
    auto game = make_shared<Game>();
    auto assets = make_shared<AssetLoader>();
    auto tiled = make_shared<TiledLoader>();
    MapScene scene(game, assets, tiled);

    game->load();

    int screenw = game->config.get_or("width", 300);
    int screenh = game->config.get_or("height", 300);

    InitWindow(screenw, screenh, game->config.get<string>("title").c_str());

    scene.makeImage(screenw/2, screenh/2);
    scene.loadMap(game->config.get<string>("firstMap"));
    scene.draw();

    Texture2D tex = LoadTextureFromImage(*scene.getScreen());

    SetTextureFilter(tex, FILTER_POINT);

    while (!WindowShouldClose()) {
        while (int k = GetKeyPressed()) {
            scene.onKeyPress(k);
        }
        if (scene.draw()) {
            UnloadTexture(tex);
            tex = LoadTextureFromImage(*scene.getScreen());
            SetTextureFilter(tex, FILTER_POINT);
        }
        BeginDrawing();
        DrawTextureEx(tex, Vector2{0, 0}, 0.0, 2.0, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}