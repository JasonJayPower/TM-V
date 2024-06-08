#include "TestScene.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Asset/Types.hpp"
#include "Input/Keyboard.hpp"
#include "Scene/Types.hpp"

#include "Manager/ContextManager.hpp"
#include "Manager/AssetManager.hpp"

TestScene::TestScene(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

void TestScene::input(const Keyboard& keyboard) {
    //if (keyboard.checkKey(Keyboard::Key::Escape, KeyState::Press)) {
    //    requestSceneChange({ SceneAction::RemoveAll });
    //}
    m_player->handleInput(keyboard);
}

void TestScene::update() {
    m_player->update();

    m_camera->update(m_player->getCenter());
}

void TestScene::render(sf::RenderWindow& window) {

    window.setView(m_camera->getView());
    m_player->draw(window);
    m_level->draw(window);
    // Reset View for GUI stuff
    // window.setView(window.getDefaultView());
}

void TestScene::onEnter() {
    std::cout << "TestScene -> On Enter \n";
}

void TestScene::onExit() {
    
    std::cout << "TestScene -> On Exit \n";
}

void TestScene::onCreate() {
    auto texMgr = getContextMgr()->textureMgr;

    m_player = std::make_unique<Player>(texMgr->get(TexID::TextureB));

    m_level = std::make_unique<Level>(texMgr->get(TexID::TextureA));

    m_camera = std::make_unique<Camera>(sf::Vector2u{ 400, 224 }, sf::Vector2u{ 400, 272 });

    std::cout << "TestScene -> On Create \n";
}

void TestScene::onDestroy() {
    std::cout << "TestScene -> On Destroy \n";
}
