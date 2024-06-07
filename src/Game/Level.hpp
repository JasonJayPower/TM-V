#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <array>

#include "Game/Tile.hpp"
#include "System/Types.hpp"

namespace sf {
    class RenderWindow;
}

class Level
{
    using Array2D = std::array<std::array<Tile, 29>, 18>;

  public:
    Level(const sf::Texture& texture);

    void loadLevel();

    Tile getTile(u64 row, u64 col) const;

    void draw(sf::RenderWindow& window);

  private:
    Array2D m_tiles;
    sf::Sprite m_sprite;
};