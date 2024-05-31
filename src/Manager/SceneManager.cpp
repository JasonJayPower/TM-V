#include "SceneManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Input/Keyboard.hpp"
#include "Scene/GameScene.hpp"
#include "Scene/TestScene.hpp"
#include "Scene/TitleScene.hpp"
#include "Utils/EnumUtils.hpp"

SceneManager::SceneManager()
    : m_currentScene{ nullptr }
    , m_scenes      { Scenes(to_underlying(SceneName::Count) - 1) }
    , m_sceneRequest{} {
}

SceneManager::~SceneManager() = default;

void SceneManager::input(const Keyboard& keyboard) const {
    m_currentScene->input(keyboard);
}

void SceneManager::update() const {
    m_currentScene->update();
}

void SceneManager::render(sf::RenderWindow& window) const {
    m_currentScene->render(window);
}

void SceneManager::processSceneRequests() {
    if (m_sceneRequest.action != SceneAction::None) {
        switch (m_sceneRequest.action) {
            case SceneAction::ChangeTo: {
                changeScene();
            } break;
            case SceneAction::RemoveAll: {
                removeAllScenes();
            } break;
            default: break;
        }
        m_sceneRequest = {};
    }
}

void SceneManager::requestSceneChange(const SceneRequest request) {
    m_sceneRequest = request;
}

bool SceneManager::isSceneStackEmpty() const {
    return m_scenes.empty();
}

void SceneManager::addScene(const SceneName name) {
    const auto index = to_underlying(name);
    if (name != SceneName::None && m_scenes[index] == nullptr) {
        auto scene = createScene(name);
        if (scene != nullptr) {
            m_scenes[index] = std::move(scene);
            if (m_currentScene) {
                m_currentScene->onExit();
            }
            m_currentScene = m_scenes[index].get();
            m_currentScene->onCreate();
            m_currentScene->onEnter();
        }
    }
}

void SceneManager::changeScene() {
    const auto index = to_underlying(m_sceneRequest.name);
    if (m_sceneRequest.name != SceneName::None && m_scenes[index]) {
        // Exit current Scene
        m_currentScene->onExit();
        m_currentScene = m_scenes[index].get();
        // Enter current Scene
        m_currentScene->onEnter();
    }
}

void SceneManager::removeAllScenes() {
    m_currentScene = nullptr;
    m_scenes.clear();
}

std::unique_ptr<BaseScene> SceneManager::createScene(const SceneName name) {
    switch (name) {
        case SceneName::Title: return std::make_unique<TitleScene>(this, name);
        case SceneName::Game:  return std::make_unique<GameScene>(this, name);
        case SceneName::Test:  return std::make_unique<TestScene>(this, name);
        default: return nullptr;
    }
}
