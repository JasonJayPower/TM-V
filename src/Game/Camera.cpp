#include "Camera.hpp"

Camera::Camera(const sf::Vector2u& viewSize, const sf::Vector2u& worldSize)
    : m_target      { 0, 0 }
    , m_halfViewSize{ sf::Vector2u(viewSize.x * 0.5f, viewSize.y * 0.5f) }
    , m_worldSize   { worldSize }
    , m_view        { { 32.f, 0.f, f32(viewSize.x), f32(viewSize.y) } } {
}

void Camera::update(const sf::Vector2f& target) {
    m_target = sf::Vector2u(target);

    if (m_target.y < m_halfViewSize.y) {
        m_target.y = m_halfViewSize.y;
    } else if (m_target.y > m_worldSize.y - m_halfViewSize.y) {
        m_target.y = m_worldSize.y - m_halfViewSize.y;
    }

    m_view.setCenter(m_view.getCenter().x, m_target.y);
}

const sf::View& Camera::getView() const {
    return m_view;
}
