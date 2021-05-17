#include "game.hpp"
#include "asset_loader.hpp"
#include "tiled.hpp"
#include "map_scene.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    auto game = make_shared<Game>();
    auto assets = make_shared<AssetLoader>();
    auto tiled = make_shared<TiledLoader>();
    MapScene scene(game, assets, tiled);

    game->load();

    int screenw = game->config.get_or("width", 300);
    int screenh = game->config.get_or("height", 300);

    //InitWindow(screenw, screenh, game->config.get<string>("title").c_str());
    sf::RenderWindow window(sf::VideoMode(screenw, screenh), game->config.get<string>("title"));
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::View view = window.getDefaultView();
    view.setSize(screenw, -screenh);
    view.setCenter(screenw/2, screenh/2);
    window.setView(view);

    ImGui::SFML::Init(window);
    float SCALE = 2.0f;

    scene.makeImage(screenw/2, screenh/2);
    scene.loadMap(game->config.get<string>("firstMap"));

    sf::Sprite screen;
    //Texture2D tex = LoadTextureFromImage(*scene.getScreen());

    //SetTextureFilter(tex, FILTER_POINT);
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
//        while (int k = GetKeyPressed()) {
//            scene.onKeyPress(k);
//        }
        //ImGui::ShowDemoWindow();


        if (scene.draw()) {
            cerr << "time to draw" << endl;
            screen.setTexture(scene.getScreen().getTexture());
            screen.setScale(2.0, 2.0);
            //screen.setRotation(180.0);
            //window.clear(sf::Color(0,0,0,255));
        }
        window.draw(screen);

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::GetIO().FontGlobalScale = SCALE;

        ImGui::Begin("Sample window"); // begin window
        if(ImGui::Button("Toggle Terrain")) {
            scene.onKeyPress('t');
        }
        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
//        BeginDrawing();
//        DrawTextureEx(tex, Vector2{0, 0}, 0.0, 2.0, WHITE);
//        EndDrawing();
    }
    ImGui::SFML::Shutdown();

    return 0;
}