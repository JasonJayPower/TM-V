#pragma once

#include <SFML/Graphics.hpp>

#include "Collision/Helper.hpp"
#include "Input/Keyboard.hpp"
#include "System/Types.hpp"

// Move out of Player
#include <vector>

#include "Game/Bullet.hpp"

class Player
{
  public:
    Player(const sf::Texture& tex);

    sf::Vector2f getCenter() const;

    void handleInput(const Keyboard& keyboard);
    void update();
    void draw(sf::RenderWindow& window);

  private:
    enum class State {
        None,
        OnGround,
        InAir,
        Falling,
        Hovering,
    };

    enum class Direction { Left, Right };

    // This is based on framerate 60 FPS, 20 = 1/3 of a second;
    static constexpr auto Gravity      = 0.75f;
    static constexpr auto MaxHoverTime = 20;

    s32 m_hoverTime = 0;
    State m_state   = State::OnGround;
    Direction m_dir = Direction::Right;
    sf::Vector2f m_vel;
    sf::Vector2f m_pos;
    sf::Sprite m_sprite;

    std::vector<Bullet> m_bullets;
};
