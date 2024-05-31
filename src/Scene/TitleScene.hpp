#pragma once

#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"

class Keyboard;

namespace sf {
    class RenderWindow;
}

class TitleScene final : public BaseScene
{
  public:
    explicit TitleScene(SceneManager* sceneManager, SceneName name);

    void input(const Keyboard& keyboard) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;
    void onCreate() override;
    void onDestroy() override;

  private:
};
