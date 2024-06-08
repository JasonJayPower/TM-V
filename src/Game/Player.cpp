#include "Player.hpp"

#include "Game/Level.hpp"

Player::Player(const sf::Texture& tex)
    : m_sprite{ tex } 
{

    m_sprite.setPosition(64.f, 32.f);
}

sf::Vector2f Player::getCenter() const {
    const auto bounds = m_sprite.getGlobalBounds();
    return { bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2) };
}

void Player::handleInput(const Keyboard& keyboard) {
    if (keyboard.checkKey(Keyboard::Key::W, KeyState::Press)) {
        const auto pos = m_sprite.getPosition();
        if (m_dir == Direction::Left) {
            // 0 = players left position, -4 for the first update and 4 texture width puts it a players left position.
            m_bullets.emplace_back(Bullet{ *m_sprite.getTexture(), { pos.x + 0, pos.y + 8 }, { -1, 0.f } });
        } else {
            // pos.x + 4 + 4 for the first update, puts it a players left + width position.
            m_bullets.emplace_back(Bullet{ *m_sprite.getTexture(), { pos.x + 4, pos.y + 8 }, { 1, 0.f } });
        }
    } 

    // Press Left and Right Keys to move horizontally
    if (keyboard.checkKey(Keyboard::Key::Left, KeyState::Hold)) {
        m_dir   = Direction::Left;
        m_pos.x = -1.5f;
    } else if (keyboard.checkKey(Keyboard::Key::Right, KeyState::Hold)) {
        m_dir   = Direction::Right;
        m_pos.x = 1.5f;
    }

    // Press Space Key to Jump
    if (keyboard.checkKey(Keyboard::Key::Space, KeyState::Press)) {
        if (m_state == State::OnGround) {
            m_state = State::InAir;
            m_pos.y = -4.f;
        }
    }
    // Press Up Key to Hover
    if (keyboard.checkKey(Keyboard::Key::Up, KeyState::Press)) {
        if (m_state == State::InAir) {
            m_state     = State::Hovering;
            m_hoverTime = MaxHoverTime;
            m_pos.y     = 0.f;
        }
    }
}

void Player::update() {
    auto position = m_sprite.getPosition();
    auto bounds   = m_sprite.getGlobalBounds();

    if (m_pos.x != 0) {
        bounds.left += m_pos.x;
        Level::handleLevelCollision(bounds, AABB::Axis::Hori);
    }

    // Disable Gravity / Collisions on the Y Axis while hovering
    if (m_state != State::Hovering) {
        m_pos.y += Gravity;
        bounds.top += m_pos.y;
        if (Level::handleLevelCollision(bounds, AABB::Axis::Vert)) {
            m_state = State::OnGround;
            m_pos.y = 0.f;
        }
    } else {
        --m_hoverTime;
        if (m_hoverTime < 0) {
            m_state     = State::Falling;
            m_hoverTime = 0;
        }
    }

    // Wrapping around the screen checks
    if (bounds.left < 24.f) {
        bounds.left = 448.f;
    } else if (bounds.left > 456.f) {
        bounds.left = 32.f;
    }
    m_sprite.setPosition(bounds.left, bounds.top);
    m_pos.x = 0.f;


    // Delete Bullets no longer used
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),[](const Bullet& bullet) {
        return !bullet.getActive();
    }), m_bullets.end());

    for (auto& bullet : m_bullets) {
        bullet.update();
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);

    for (auto& bullet : m_bullets) {
        bullet.draw(window);
    }
}
