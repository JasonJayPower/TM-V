#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>

#include "Asset/Types.hpp"
#include "Input/Keyboard.hpp"
#include "Manager/AssetManager.hpp"

namespace sf {
    class Font;
    class Texture;
}  // namespace sf

class SceneManager;

class App
{
  public:
    App();
    ~App();

    void setup();
    void run();

  private:
    void processEvents(sf::Event& e);
    void update();
    void render();
    void lateUpdate();

    sf::RenderWindow m_window = { sf::VideoMode(640, 480), "" };
    Keyboard m_keyboard       = {};

    AssetManager<sf::Font, FontID> m_fontMgr;
    AssetManager<sf::Texture, TexID> m_textureMgr;
    std::unique_ptr<SceneManager> m_sceneMgr;
};
