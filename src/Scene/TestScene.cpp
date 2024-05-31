#include "TestScene.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Asset/Types.hpp"
#include "Input/Keyboard.hpp"
#include "Manager/AssetManager.hpp"
#include "Manager/ContextManager.hpp"
#include "Scene/Types.hpp"

TestScene::TestScene(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

void TestScene::input(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::A, KeyState::Press)) {
        requestSceneChange({ SceneAction::RemoveAll });
    }
}

void TestScene::update() {
}

void TestScene::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    window.draw(m_text);
}

void TestScene::onEnter() {
    std::cout << "TestScene -> On Enter \n";
}

void TestScene::onExit() {
    std::cout << "TestScene -> On Exit \n";
}

void TestScene::onCreate() {
    auto texMgr = getContextMgr()->textureMgr;

    m_sprite.setTexture(texMgr->get(TexID::TextureA));
    m_sprite.setPosition(100.f, 100.f);


    auto fontMgr = getContextMgr()->fontMgr;

    m_text.setFont(fontMgr->get(FontID::FontA));
    m_text.setColor(sf::Color::Red);
    m_text.setString("Testing Font");
    m_text.setCharacterSize(20);
    m_text.setPosition(50, 50);

    std::cout << "TestScene -> On Create \n";
}

void TestScene::onDestroy() {
    std::cout << "TestScene -> On Destroy \n";
}
