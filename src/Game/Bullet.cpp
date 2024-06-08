#include "Bullet.hpp"

#include "Game/Level.hpp"

Bullet::Bullet(const sf::Texture& tex, sf::Vector2f pos, sf::Vector2f vel)
    : m_sprite{ tex }
    , m_vel   { vel } {

    m_sprite.setPosition(pos);
    m_sprite.setColor(sf::Color::Black);
    m_sprite.setTextureRect({ 0, 0, 4, 4 });
}

void Bullet::update() {
    m_sprite.move(m_vel.x * Speed, 0.f);

    auto bounds = m_sprite.getGlobalBounds();
    if (Level::handleLevelCollision(bounds, AABB::Axis::Hori)) {
        m_active = false;
    }
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

bool Bullet::getActive() const {
    return m_active;
}
