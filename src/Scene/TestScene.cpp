#include "TestScene.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Asset/Types.hpp"
#include "Collision/Helper.hpp"
#include "Input/Keyboard.hpp"
#include "Manager/AssetManager.hpp"
#include "Manager/ContextManager.hpp"
#include "Scene/Types.hpp"

TestScene::TestScene(SceneManager* sceneManager, SceneName name)
    : BaseScene{ sceneManager, name } {
}

void TestScene::input(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::Escape, KeyState::Press)) {
        requestSceneChange({ SceneAction::RemoveAll });
    }

    if (keyboard.checkKey(Keyboard::Key::W, KeyState::Hold)) {
        m_player.pos.y -= 2.f;
    } else if (keyboard.checkKey(Keyboard::Key::S, KeyState::Hold)) {
        m_player.pos.y += 2.f;
    }

    if (keyboard.checkKey(Keyboard::Key::A, KeyState::Hold)) {
        m_player.pos.x -= 2.f;
    } else if (keyboard.checkKey(Keyboard::Key::D, KeyState::Hold)) {
        m_player.pos.x += 2.f;
    }
}

void TestScene::update() {
    // Handle tile collisions in 2x parts, Horizontal first, then Vertical.
    if (m_player.pos.x != 0.f) {
        m_player.aabb.left += m_player.pos.x;
        checkForCollision(m_player.aabb, Axis::Horizontal);
        m_player.spr.setPosition(m_player.aabb.left, m_player.aabb.top);
    }

    if (m_player.pos.y != 0.f) {
        m_player.aabb.top += m_player.pos.y;
        checkForCollision(m_player.aabb, Axis::Vertical);
        m_player.spr.setPosition(m_player.aabb.left, m_player.aabb.top);
    }
    m_player.pos = {};
}

void TestScene::render(sf::RenderWindow& window) {
    window.draw(m_player.spr);
    for (u32 row = 0; row < m_level.tiles.size(); ++row) {
        for (u32 col = 0; col < m_level.tiles[row].size(); ++col) {
            if (m_level.tiles[row][col] != 0) {
                m_level.spr.setPosition(col * 32.f, row * 32.f);
                window.draw(m_level.spr);
            }
        }
    }
}

void TestScene::onEnter() {
    std::cout << "TestScene -> On Enter \n";
}

void TestScene::onExit() {
    std::cout << "TestScene -> On Exit \n";
}

void TestScene::onCreate() {
    auto texMgr = getContextMgr()->textureMgr;

    m_player.spr.setTexture(texMgr->get(TexID::TextureA));
    m_player.spr.setPosition(32.f, 64.f);
    m_player.spr.setTextureRect({ 32, 0, 32, 32 });
    m_player.aabb = { 32.f, 64.f, 32.f, 32.f };

    m_level.spr.setTexture(texMgr->get(TexID::TextureA));
    m_level.spr.setTextureRect({ 0, 0, 32, 32 });

    auto fontMgr = getContextMgr()->fontMgr;

    m_text.setFont(fontMgr->get(FontID::FontA));
    m_text.setColor(sf::Color::Red);
    m_text.setString("Testing Font");
    m_text.setCharacterSize(20);
    m_text.setPosition(200, 200);

    std::cout << "TestScene -> On Create \n";
}

void TestScene::onDestroy() {
    std::cout << "TestScene -> On Destroy \n";
}

bool TestScene::checkForCollision(sf::FloatRect& bounds, Axis axis) {
    sf::FloatRect tileBounds{ 0.f, 0.f, 32.f, 32.f };

    const auto leftTile   = static_cast<int>((bounds.left / 32.f));
    const auto rightTile  = static_cast<int>((bounds.left + bounds.width) / 32.f);
    const auto topTile    = static_cast<int>((bounds.top / 32.f));
    const auto bottomTile = static_cast<int>((bounds.top + bounds.height) / 32.f);

    for (auto row = topTile; row <= bottomTile; row++) {
        for (auto col = leftTile; col <= rightTile; col++) {
            if (m_level.tiles[row][col] == 1) {
                tileBounds.left = static_cast<float>(col * 32.f);
                tileBounds.top  = static_cast<float>(row * 32.f);
                if (bounds.intersects(tileBounds)) {
                    axis == Axis::Horizontal ? bounds.left = AABB::resolveHorizontal(bounds, tileBounds)
                                             : bounds.top  = AABB::resolveVertical(bounds, tileBounds);
                    return true;
                }
            }
        }
    }
    return false;
}