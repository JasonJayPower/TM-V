#pragma once

#include <SFML/Graphics.hpp>

#include "Game/Level.hpp"
#include "Input/Keyboard.hpp"
#include "System/Types.hpp"
#include "Collision/Helper.hpp"

class Player
{
  public:
    Player(const sf::Texture& tex);

    sf::Vector2f getCenter() const;

    void handleInput(const Keyboard& keyboard);
    void update(const Level& level);
    void draw(sf::RenderWindow& window);

  private:
    f32 handleLevelCollision(const Level& level, sf::FloatRect& pBounds, AABB::Axis axi);

    sf::Vector2f m_pos;
    sf::Sprite m_sprite;
};
