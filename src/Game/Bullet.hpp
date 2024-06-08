#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
  public:
    Bullet(const sf::Texture& tex, sf::Vector2f pos, sf::Vector2f vel);
    
    void update();
    void draw(sf::RenderWindow& window);

    bool getActive() const;

  private:
    static constexpr auto Speed = 4;

    bool m_active;
    sf::Vector2f m_vel;
    sf::Sprite m_sprite;
};
