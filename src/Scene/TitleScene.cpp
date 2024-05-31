#include "TitleScene.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "Input/Keyboard.hpp"
#include "Scene/Types.hpp"

TitleScene::TitleScene(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

TitleScene::~TitleScene() {
}

void TitleScene::input(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::A, KeyState::Press)) {
        requestSceneChange({ SceneAction::ChangeTo, SceneName::Game });
    }
}

void TitleScene::update() {
}

void TitleScene::render(sf::RenderWindow& window) {
}

void TitleScene::onEnter() {
    std::cout << "TitleScene -> On Enter \n";
}

void TitleScene::onExit() {
    std::cout << "TitleScene -> On Exit \n";
}

void TitleScene::onCreate() {
    std::cout << "TitleScene -> On Create \n";
}

void TitleScene::onDestroy() {
    std::cout << "TitleScene -> On Destroy \n";
}
