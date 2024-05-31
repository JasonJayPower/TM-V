#include "GameScene.hpp"

#include <iostream>

#include "Input/Keyboard.hpp"

GameScene::GameScene(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

void GameScene::input(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::A, KeyState::Press)) {
        requestSceneChange({ SceneAction::ChangeTo, SceneName::Title });
    } else if (keyboard.checkKey(Keyboard::Key::D, KeyState::Press)) {
        requestSceneChange({ SceneAction::RemoveAll });
    }
}

void GameScene::update() {
}

void GameScene::render(sf::RenderWindow& window) {
}

void GameScene::onEnter() {
    std::cout << "GameScene -> On Enter \n";
}
void GameScene::onExit() {
    std::cout << "GameScene -> On Exit \n";
}

void GameScene::onCreate() {
    std::cout << "GameScene -> On Create \n";
}

void GameScene::onDestroy() {
    std::cout << "GameScene -> On Destroy \n";
}
