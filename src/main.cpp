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

    bool showDebugUI = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Hyphen) {
                    showDebugUI = !showDebugUI;
                } else {
                    scene.onKeyPress(event);
                }
            }
        }

        if (scene.draw()) {
            screen.setTexture(scene.getScreen().getTexture());
            screen.setScale(2.0, 2.0);
        }

        window.draw(screen);

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::GetIO().FontGlobalScale = SCALE;

        if(showDebugUI) {
            ImGui::Begin("Sample window"); // begin window
            if (ImGui::Button("Toggle Terrain")) {
                scene.toggleDebugTerrain();
            }
            if (ImGui::Button("Hide Debug")) {
                showDebugUI = false;
            }
            ImGui::End();
        }
        ImGui::SFML::Render(window);

        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}