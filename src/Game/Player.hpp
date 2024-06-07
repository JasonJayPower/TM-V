#pragma once

#include <SFML/Graphics.hpp>

#include "Collision/Helper.hpp"
#include "Game/Level.hpp"
#include "Input/Keyboard.hpp"
#include "System/Types.hpp"

class Player
{
  public:
    Player(const sf::Texture& tex);

    sf::Vector2f getCenter() const;

    void handleInput(const Keyboard& keyboard);
    void update(const Level& level);
    void draw(sf::RenderWindow& window);

  private:
    enum class State {
        None,
        OnGround,
        InAir,
        Hovering,
    };

    // This is based on framerate 60 FPS, 20 = 1/3 of a second;
    static constexpr auto Gravity = 0.75f;
    static constexpr auto MaxHoverTime = 20;

    f32 handleLevelCollision(const Level& level, sf::FloatRect& pBounds, AABB::Axis axi);

    s32 m_hoverTime = 0;
    State m_state;
    sf::Vector2f m_vel;
    sf::Vector2f m_pos;
    sf::Sprite m_sprite;
};
