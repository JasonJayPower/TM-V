#include "SceneRS01.hpp"
#include "SceneRS01.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Asset/Types.hpp"
#include "Input/Keyboard.hpp"
#include "Manager/AssetManager.hpp"
#include "Manager/ContextManager.hpp"
#include "Scene/Types.hpp"

SceneRS01::SceneRS01(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

void SceneRS01::input(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::A, KeyState::Press)) {
        requestSceneChange({ SceneAction::ChangeTo, SceneName::Game });
    }
}

void SceneRS01::update() {
}

void SceneRS01::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    window.draw(m_text);
}

void SceneRS01::onEnter() {
    std::cout << "SceneRS01 --> On Enter \n";
}

void SceneRS01::onExit() {
    std::cout << "SceneRS01 --> On Exit \n";
}

void SceneRS01::onCreate() {
    auto texMgr = getContextMgr()->textureMgr;

    m_sprite.setTexture(texMgr->get(TexID::TextureA));
    m_sprite.setColor(sf::Color::Transparent);
    m_sprite.setPosition(100.0f, 100.0f);

    auto fontMgr = getContextMgr()->fontMgr;

    m_text.setFont(fontMgr->get(FontID::FontA));
    m_text.setColor(sf::Color::Green);
    m_text.setString("Texting Font");
    m_text.setCharacterSize(20);
    m_text.setPosition(50, 50);

    std::cout << "TestScene -> OnCreate \n";
}

void SceneRS01::onDestroy() {
    std::cout << "TestScene -> OnDestroy \n";
}
