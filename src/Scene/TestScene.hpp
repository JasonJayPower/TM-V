#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"
#include "System/Types.hpp"

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
    enum class Axis { Horizontal, Vertical };

    bool checkForCollision(sf::FloatRect& bounds, Axis axis);

    struct Player {
        sf::Vector2f pos;
        sf::Sprite   spr;
        sf::FloatRect aabb;
    };

    struct Level {
        sf::Sprite spr;
        std::vector<std::vector<u8>> tiles{
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1 }, 
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
            { 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        };
    };

    Player m_player;
    Level m_level;
    sf::Text m_text;
};
