#pragma once

#include <memory>
#include <vector>

#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"

namespace sf {
    class RenderWindow;
}
class Keyboard;

class SceneManager
{
    using Scene  = std::unique_ptr<BaseScene>;
    using Scenes = std::vector<Scene>;

  public:
     SceneManager();
    ~SceneManager();

    void input(const Keyboard& keyboard) const;
    void update() const;
    void render(sf::RenderWindow& window) const;

    void addScene(const SceneName name);

    void processSceneRequests();
    void requestSceneChange(const SceneRequest request);

    bool isSceneStackEmpty() const;

  private:
    void changeScene();
    void removeAllScenes();

    Scene createScene(const SceneName name);

    BaseScene* m_currentScene;
    Scenes m_scenes;
    SceneRequest m_sceneRequest;
};