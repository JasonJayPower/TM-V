#pragma once

#include "Scene/Types.hpp"

class Keyboard;
class SceneManager;

namespace sf {
    class RenderWindow;
}  // namespace sf

class BaseScene
{
  public:
    BaseScene(SceneManager* sceneManager, SceneName name);
    virtual ~BaseScene() = default;

    virtual void input(const Keyboard& keyboard)  = 0;
    virtual void update()                         = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void onEnter()                        = 0;
    virtual void onExit()                         = 0;
    virtual void onCreate()                       = 0;
    virtual void onDestroy()                      = 0;

    SceneName getName() const;

  protected:
    void requestSceneChange(SceneRequest request) const;

  private:
    SceneName m_name;
    SceneManager* m_sceneManager;
};
