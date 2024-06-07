#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "System/Types.hpp"

class Camera
{
  public:
    Camera(const sf::Vector2u& viewSize, const sf::Vector2u& worldSize);

    void update(const sf::Vector2f& target);

    const sf::View& getView() const;

  private:
    sf::Vector2u m_target;
    sf::Vector2u m_worldSize;
    sf::Vector2u m_halfViewSize;
    sf::View m_view;
};
