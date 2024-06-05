#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Asset/Types.hpp"
#include "Manager/AssetManager.hpp"
#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"

class Keyboard;

namespace sf {
    class RenderWindow;
}

class SceneRS01 final : public BaseScene
{
  public:
    explicit SceneRS01(SceneManager* sceneManager, SceneName name);

    void input(const Keyboard& keyboard) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;
    void onCreate() override;
    void onDestroy() override;

private:
    sf::Sprite m_sprite;
  sf::Text m_text;
};