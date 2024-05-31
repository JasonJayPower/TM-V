#pragma once

#include <memory>
#include <vector>

#include "Scene/BaseScene.hpp"
#include "Scene/Types.hpp"

namespace sf {
    class RenderWindow;
}

class ContextManager;
class Keyboard;

class SceneManager
{
    using ContextMgr = std::unique_ptr<ContextManager>;
    using Scene      = std::unique_ptr<BaseScene>;
    using Scenes     = std::vector<Scene>;

  public:
    SceneManager(std::unique_ptr<ContextManager> contextMgr);
    ~SceneManager();

    void input(const Keyboard& keyboard) const;
    void update() const;
    void render(sf::RenderWindow& window) const;

    void addScene(const SceneName name);

    void processSceneRequests();
    void requestSceneChange(const SceneRequest request);

    bool isSceneStackEmpty() const;

    const ContextManager* getContextMgr() const;

  private:
    void changeScene();
    void removeAllScenes();

    Scene createScene(const SceneName name);

    BaseScene* m_currentScene;
    Scenes m_scenes;
    ContextMgr m_contextMgr;
    SceneRequest m_sceneRequest;
};