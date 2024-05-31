#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <memory>

#include "Input/Keyboard.hpp"

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

    sf::RenderWindow m_window                = { sf::VideoMode(640, 480), "" };
    std::unique_ptr<SceneManager> m_sceneMgr = { nullptr };
    Keyboard m_keyboard                      = {};
};
