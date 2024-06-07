#include "Player.hpp"

Player::Player(const sf::Texture& tex)
    : m_sprite{ tex } {
    m_sprite.setPosition(32.f, 32.f);
}

sf::Vector2f Player::getCenter() const {
    const auto bounds = m_sprite.getGlobalBounds();
    return { bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2) };
}

void Player::handleInput(const Keyboard& keyboard) {
    // Press Left and Right Keys to move horizontally
    if (keyboard.checkKey(Keyboard::Key::Left, KeyState::Hold)) {
        m_pos.x = -1.5f;
    } else if (keyboard.checkKey(Keyboard::Key::Right, KeyState::Hold)) {
        m_pos.x = 1.5f;
    }

    // Hold Up Key to Hover, you have 20 frames (1/3 of a second)
    if (keyboard.checkKey(Keyboard::Key::Up, KeyState::Hold)) {
        // Can only use Hover when jumping and not falling
        if (m_state == State::InAir && m_pos.y < 0.f) {
            m_state     = State::Hovering;
            m_hoverTime = MaxHoverTime;
            m_pos.y     = 0.f;
        } else if (m_state == State::Hovering) {
            --m_hoverTime;
            if (m_hoverTime < 0) {
                m_state     = State::InAir;
                m_hoverTime = 0;
            }
        }
    } else if (keyboard.checkKey(Keyboard::Key::Up, KeyState::Release)) {
        m_state = State::InAir;
    }

    // Press Space Key to Jump
    if (keyboard.checkKey(Keyboard::Key::Space, KeyState::Press)) {
        if (m_state == State::OnGround) {
            m_state = State::InAir;
            m_pos.y = -4.f;
        }
    }
}

void Player::update(const Level& level) {
    auto position = m_sprite.getPosition();
    auto bounds   = m_sprite.getGlobalBounds();

    if (m_pos.x != 0) {
        bounds.left += m_pos.x;
        handleLevelCollision(level, bounds, AABB::Axis::Hori);
    }

    // Disable Gravity / Collisions on the Y Axis while hovering
    if (m_state != State::Hovering) {
        m_state = State::InAir;
        m_pos.y += Gravity;
        bounds.top += m_pos.y;
        handleLevelCollision(level, bounds, AABB::Axis::Vert);
    }

    // Wrapping around the screen checks
    if (bounds.left < 8.f) {
        bounds.left = 432.f;
    } else if (bounds.left > 440.f) {
        bounds.left = 16.f;
    }
    m_sprite.setPosition(bounds.left, bounds.top);
    m_pos.x = 0.f;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

f32 Player::handleLevelCollision(const Level& level, sf::FloatRect& pBounds, AABB::Axis axis) {
    auto tBounds = sf::FloatRect{ 0.f, 0.f, Tile::Size, Tile::Size };

    const auto leftTile   = static_cast<int>((pBounds.left / Tile::Size));
    const auto rightTile  = static_cast<int>((pBounds.left + pBounds.width) / Tile::Size);
    const auto topTile    = static_cast<int>((pBounds.top / Tile::Size));
    const auto bottomTile = static_cast<int>((pBounds.top + pBounds.height) / Tile::Size);

    for (auto row = topTile; row <= bottomTile; row++) {
        for (auto col = leftTile; col <= rightTile; col++) {
            if (level.getTile(row, col).getType() == Tile::Block) {
                tBounds.left = static_cast<float>(col * Tile::Size);
                tBounds.top  = static_cast<float>(row * Tile::Size);
                if (pBounds.intersects(tBounds)) {
                    if (axis == AABB::Axis::Hori) {
                        pBounds.left = AABB::resolveHorizontal(pBounds, tBounds);
                    } else {
                        pBounds.top = AABB::resolveVertical(pBounds, tBounds);
                        m_state     = State::OnGround;
                        m_pos.y     = 0.f;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
