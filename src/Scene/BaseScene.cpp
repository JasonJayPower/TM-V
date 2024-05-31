#include "BaseScene.hpp"

#include "Manager/SceneManager.hpp"

BaseScene::BaseScene(SceneManager* sceneManager, SceneName name)
    : m_name        { name }
    , m_sceneManager{ sceneManager } {
}

SceneName BaseScene::getName() const {
    return m_name;
}

void BaseScene::requestSceneChange(SceneRequest request) const {
    m_sceneManager->requestSceneChange(request);
}

