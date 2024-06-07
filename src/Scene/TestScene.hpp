#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <memory>

#include "Game/Camera.hpp"
#include "Game/Level.hpp"
#include "Game/Player.hpp"
#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"
class Keyboard;

namespace sf {
    class RenderWindow;
}

class TestScene final : public BaseScene
{
  public:
    explicit TestScene(SceneManager* sceneManager, SceneName name);

    void input(const Keyboard& keyboard) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;
    void onCreate() override;
    void onDestroy() override;

  private:
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Level> m_level;
};
